#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#include "ode/World.h"
#include "ode/Car.h"
#include "ode/Timer.h"
#include "genetic_algorithms/GeneticAlgorithm.h"
#include "ode/Track.h"
#include "ode/TrackCollection.h"
#include <iostream>
#include <fstream>

#define DESVIO					1
#define EVAL_TIME				10
#define	GA_WORLDS_MUTATION		0.3
#define	GA_WORLDS_CROSSOVER		0.5
#define	GA_WORLDS_POPULATION	20
#define	GA_WORLDS_GENES			10
#define	GA_WORLDS_ELITISM		0.5
#define	GA_CARS_MUTATION		0.3
#define	GA_CARS_CROSSOVER		0.7
#define	GA_CARS_POPULATION		200
#define	GA_CARS_GENES			25
#define	GA_CARS_ELITISM			0.5
#define CARS_PER_WORLD			GA_CARS_POPULATION / GA_WORLDS_POPULATION

World world(9.8);
World w(9.8);
GeneticAlgorithm gaWorlds = GeneticAlgorithm(GA_WORLDS_MUTATION, GA_WORLDS_CROSSOVER, GA_WORLDS_POPULATION, GA_WORLDS_GENES);
GeneticAlgorithm gaCars = GeneticAlgorithm(GA_CARS_MUTATION, GA_CARS_CROSSOVER, GA_CARS_POPULATION, GA_CARS_GENES);
WorldChromossome* dnaWorlds = new WorldChromossome[GA_WORLDS_POPULATION];
CarChromossome* dnaCars = new CarChromossome[GA_CARS_POPULATION];
CarChromossome* prevDnaCars = new CarChromossome[GA_CARS_POPULATION];
WorldChromossome* prevDnaWorlds = new WorldChromossome[GA_WORLDS_POPULATION];
Car** cars = new Car*[CARS_PER_WORLD];
Timer timer = Timer();
double speed = 0;
double direction = 0;
int currentWorld = 0;
bool carControl = false;
Car* bestCar = NULL;
bool test = false;

void WorldSize()
{
	printf("%d\n", world.GetObjects().size());
}
void move(Car &car)
{
	car.Accelerate(100000000);
}

double fitness(Car &car)
{
	return car.Geometry()->GetPosition().y;
}

bool broken(Car &car, double original_x)
{
	if ( abs(car.Geometry()->GetPosition().x - original_x) > DESVIO )
	{
		return true;
	}

	if (car.Geometry()->GetPosition().z < 0 || car.Geometry()->GetPosition().z > 10)
	{
		return true;
	}

	return false;
}

static void info(Car &car)
{
	printf("Distancia: %.2f\n", fitness(car));
	//printf("Velocidade: %.2f\n", car.WheelVelocity());
	printf("Velocidade: %.2f\n", car.Velocity());
}

int StartI()
{
	return currentWorld * CARS_PER_WORLD;
}

int EndI()
{
	return currentWorld * CARS_PER_WORLD + CARS_PER_WORLD;
}

void info()
{
	for (int i = 0; i < CARS_PER_WORLD; i++)
	{
		if (cars[i] != NULL)
		{
			printf("%.2f\n", fitness(*cars[i]));
		}
	}
}
int CarI(int i)
{
	return currentWorld * CARS_PER_WORLD + i;
}

double X(int i)
{
	return i * 10;
}


void WorldRemove(int i)
{
	for (int j = 0; j < 4; j++)
	{
		world.RemoveObject(&(cars[i]->GetWheels()[j]));
	}
	world.RemoveObject(cars[i]);
	world.RemoveSpace(cars[i]->GetSpace());
}

void Destroy()
{
	for (int i = 0; i < CARS_PER_WORLD; i++)
	{
		if (cars[i] != NULL)
		{
			WorldRemove(i);
			cars[i]->~Car();
		}
	}
}

void Build()
{
	for (int i = 0; i < CARS_PER_WORLD; i++)
	{
		cars[i] = new Car(world, dnaCars[CarI(i)], X(i));
		move(*cars[i]);
	}
	world.SetParams(dnaWorlds[currentWorld]);
}
void NextTest()
{
	double totalFitness = 0;

	for (int i = StartI(); i < EndI(); i++)
	{
		if (cars[i - StartI()] != NULL)
		{
			dnaCars[i].SetFitness(fitness(*cars[i - StartI()]));
		}
		totalFitness += dnaCars[i].GetFitness();
	}
	dnaWorlds[currentWorld].SetFitness(totalFitness);
	currentWorld++;
	Destroy();
	Build();
}

void RemoveBrokenCars()
{
	for (int i = 0; i < gaCars.PopulationSize(); i++)
	{
		if (gaCars[i].GetFitness() == 0)
		{
			gaCars.RemoveChromossome(i);
			i--;
		}
	}

	bool random = (gaCars.PopulationSize() == 0 ? true : false);

	while (gaCars.PopulationSize() < GA_CARS_POPULATION)
	{
		if (random)
		{
			gaCars.AddChromossome(CarChromossome());
		}
		else
		{
			gaCars.AddChromossome(gaCars.Select());
		}
	}
}

int BestCar()
{
	int best = 0;

	for (int i = 1; i < GA_CARS_POPULATION; i++)
	{
		if (prevDnaCars[i].GetFitness() > prevDnaCars[best].GetFitness())
		{
			best = i;
		}
	}

	return best;
}

int BestWorld(int bestCar)
{
	return (int)floor((double)(bestCar / CARS_PER_WORLD));
}

double AverageCarFitness()
{
	double average = 0;

	for (int i = 0; i < GA_CARS_POPULATION; i++)
	{
		average += prevDnaCars[i].GetFitness();
	}

	return average / GA_CARS_POPULATION;
}

double AverageWorldFitness()
{
	double average = 0;

	for (int i = 0; i < GA_WORLDS_POPULATION; i++)
	{
		average += prevDnaWorlds[i].GetFitness();
	}

	return average / GA_WORLDS_POPULATION;
}

double BestWorldFitness()
{
	double best = 0;

	for (int i = 0; i < GA_WORLDS_POPULATION; i++)
	{
		if (prevDnaWorlds[i].GetFitness() > best)
		{
			best = prevDnaWorlds[i].GetFitness();
		}
	}

	return best;
}

void MakeTestCar()
{
	int bestCarIndex;

	Destroy();
	bestCarIndex = BestCar();
	world.SetParams(prevDnaWorlds[BestWorld(bestCarIndex)]);
	bestCar = new Car(world, prevDnaCars[bestCarIndex], 0);
	carControl = true;
	world.GetCamera()->Attach(*bestCar);
	world.SetDraw(true);
	printf("Media fitness mundo:\t%.2f\n", AverageWorldFitness());
	printf("Melhor fitness mundo:\t%.2f\n", BestWorldFitness());
	printf("Fitness mundo actual:\t%.2f\n", prevDnaWorlds[BestWorld(bestCarIndex)].GetFitness());
	printf("Media fitness carros:\t%.2f\n", AverageCarFitness());
	printf("Melhor fitness carros:\t%.2f\n", prevDnaCars[bestCarIndex].GetFitness());
}

void Remake()
{
	for (int j = 0; j < 4; j++)
	{
		world.RemoveObject(&(bestCar->GetWheels()[j]));
	}
	world.RemoveObject(bestCar);
	world.RemoveSpace(bestCar->GetSpace());
	bestCar->~Car();
	carControl = false;
	//world.SetDraw(false);

	for (int i = 0; i < GA_WORLDS_POPULATION; i++)
	{
		dnaWorlds[i] = prevDnaWorlds[i];
	}

	for (int i = 0; i < GA_CARS_POPULATION; i++)
	{
		dnaCars[i] = prevDnaCars[i];
	}
	currentWorld = 0;
	Build();
	timer.Restart();
}

void simInfo()
{
	printf("Geracao:\t%d\n", gaWorlds.GetGenerationCount());
	printf("Media fitness mundo:\t%.2f\n", AverageWorldFitness());
	printf("Melhor fitness mundo:\t%.2f\n", BestWorldFitness());
	printf("Fitness mundo actual:\t%.2f\n", prevDnaWorlds[BestWorld(BestCar())].GetFitness());
	printf("Media fitness carros:\t%.2f\n", AverageCarFitness());
	printf("Melhor fitness carros:\t%.2f\n", prevDnaCars[BestCar()].GetFitness());
}

void NewGeneration()
{
	double totalFitness = 0;

	for (int i = StartI(); i < EndI(); i++)
	{
		if (cars[i - StartI()] != NULL)
		{
			dnaCars[i].SetFitness(fitness(*cars[i - StartI()]));
		}
		totalFitness += dnaCars[i].GetFitness();
	}
	dnaWorlds[currentWorld].SetFitness(totalFitness);
	currentWorld++;
	Destroy();

	for (int i = 0; i < GA_WORLDS_POPULATION; i++)
	{
		prevDnaWorlds[i] = WorldChromossome(dnaWorlds[i]);
	}

	for (int i = 0; i < GA_CARS_POPULATION; i++)
	{
		prevDnaCars[i] = CarChromossome(dnaCars[i]);
	}
	gaWorlds.Replace(dnaWorlds, GA_WORLDS_POPULATION);
	gaWorlds.Epoch();
	gaCars.Replace(dnaCars, GA_CARS_POPULATION);
	RemoveBrokenCars();
	gaCars.Epoch();
	currentWorld = 0;
	Build();
	simInfo();

	std::ofstream ofile;
	ofile.open("best.txt", std::ios::out | std::ios::app);
	int bestCarIndex = BestCar();
	ofile << prevDnaCars[bestCarIndex];
	ofile << prevDnaWorlds[BestWorld(bestCarIndex)];
	ofile.close();
}

static void command(int c)
{
	switch (tolower(c))
	{
		case 'a':
			if (carControl)
			{
				if (speed < 100)
				{
					speed += 10;
				}
			}
			break;

		case 'z':
			if (carControl)
			{
				if (speed > -40)
				{
					speed -= 4;
				}
			}
			break;

		case '.':
			if (carControl)
			{
				if (direction < 1)
				{
					direction += 0.2;
				}
			}
			break;

		case ',':
			if (carControl)
			{
				if (direction > -1)
				{
					direction -= 0.2;
				}
			}
			break;
		
		case ' ':
			if (carControl)
			{
				speed = 0;
				direction = 0;
			}
			break;

		case 'f':
			if (!test)
			{
				world.GetCamera()->Free();
			}
			else
			{
				w.GetCamera()->Free();
			}
			break;

		case 'c':
			if (carControl)
			{
				if (!test)
				{
					world.GetCamera()->Attach(*bestCar);
				}
				else
				{
					w.GetCamera()->Attach(*bestCar);
				}
			}
			break;

		case 't':
			if (!carControl)
			{
				MakeTestCar();
			}
			break;

		case 'x':
			if (carControl)
			{
				Remake();
			}
			break;

		case 'r':
			if (carControl)
			{
				if (test)
				{
					w.Reset();
				}
				else
				{
					world.Reset();
				}
				speed = 0;
				direction = 0;
			}
			break;

		case 'd':
			world.SetDraw(!world.GetDraw());
			break;

		case 'i':
			if (carControl)
			{
				info(*bestCar);
			}
			else
			{
				simInfo();
				info();
			}
			break;

		case 'h':
			printf("a z\tacelerar/travar\n");
			printf(", .\tvirar esquerda/direita\n");
			printf(" \tvelocidade e direccao = 0\n");
			printf("f\tliberta camara\n");
			printf("c\tprende camara a carro\n");
			printf("d\tdesenha mundo\n");
			printf("r\treset ao mundo\n");
			printf("t\tconstroi melhor carro para teste\n");
			printf("x\tretoma testes\n");
			printf("i\tinformacao detalhada sobre a simulacao\n");
			break;
		//case 'n':
		//	if (carControl)
		//	{
		//		for (int j = 0; j < 4; j++)
		//		{
		//			w.RemoveObject(&(bestCar->GetWheels()[j]));
		//		}
		//		w.RemoveObject(bestCar);
		//		w.RemoveSpace(bestCar->GetSpace());
		//		bestCar->~Car();
		//		bestCar = new Car(w, CarChromossome(), 0);
		//		direction = 0;
		//		speed = 100000000;
		//	}
		//	break;
	}
}

static void loop(int pause)
{
	bool stop = true;

	if (!pause)
	{
		if (carControl)
		{
			bestCar->Accelerate(speed);
			bestCar->Steer(direction);
		}
		else
		{
			for (int i = 0; i < CARS_PER_WORLD; i++)
			{
				if ( cars[i] != NULL && broken(*cars[i], X(i)) )
				{
					if (cars[i]->Geometry()->GetPosition().z >= 0 && cars[i]->Geometry()->GetPosition().z < 10)
					{
						dnaCars[i].SetFitness(fitness(*cars[i]));
					}
					WorldRemove(i);
					cars[i]->~Car();
					cars[i] = NULL;
				}
				else if (cars[i] != NULL)
				{
					stop = false;
				}
			}

			if ( stop || (timer.GetTime() > EVAL_TIME * 1000) )
			{
				if (currentWorld < GA_WORLDS_POPULATION - 1)
				{
					NextTest();
				}
				else
				{
					NewGeneration();
				}
				timer.Restart();
			}
		}
	}
}

void l(int p)
{
	bestCar->Accelerate(speed);
	bestCar->Steer(direction);

//	Wheel* wheels = bestCar->GetWheels();
//	double amt = 0;
//	for (int i = 0; i < 4; i++)
//	{
////		printf("%.2f\n", wheels[i].Geometry()->GetPosition().z);
////		printf("%.2f\n", wheels[i].Geometry()->Height());
//				Vector3 anchor2 = wheels[i].Joint.Anchor2;
//				Vector3 anchor1 = wheels[i].Joint.Anchor;
//				Vector3 axis = wheels[i].Joint.Axis2;
//				
//				displacement = Vector3.Dot(anchor1-anchor2,axis);
//				
//				if(displacement> 0){
//					amt = displacement * swayForce;
//					if(amt> swayForceLimit)
//						amt = swayForceLimit;
//					wheels[i].Body.AddForce(-axis *amt);
//					wheels[i^1].Body.AddForce(axis *amt);
//				}
//
//		//if (wheels[i].Geometry()->GetPosition().z > wheels[i].Geometry()->Height() * 0.5)
//		//{
//		//	dBodyAddForce( wheels[i].ID(), 0 , 0, -10);
//		//}
//	}
}
int main2()
{
	//gaWorlds.SetMaxPerturbation(0.3);
	//gaWorlds.SetSelection(new RoulletteWheelSelection());
	//gaWorlds.SetDoElitism(true);
	//gaWorlds.SetElitism(new StandardElitism((int) (GA_WORLDS_ELITISM * GA_WORLDS_POPULATION)));
	//gaWorlds.SetCrossover(new SinglePointCrossover(GA_WORLDS_CROSSOVER));

	//gaCars.SetMaxPerturbation(0.3);
	//gaCars.SetSelection(new RoulletteWheelSelection());
	//gaCars.SetDoElitism(true);
	//gaCars.SetElitism(new StandardElitism((int) (GA_CARS_ELITISM * GA_CARS_POPULATION)));
	//gaCars.SetCrossover(new TwoPointCrossover(GA_CARS_CROSSOVER));

	//world.SetInputResolver(command);
	//world.SetLoopFunction(loop);
	//world.SetDraw(true);
	//Build();
	//timer.Start();
	//world.Start();





	/**(double gravity, double angularDampening, double linearDampening
	, double aerodynamic, double mu, double mu2, double slip1, double slip2, double soft_erp, double soft_cfm)*/
		
		// gravity, angularDampening,	linearDampening	aerodynamic	mu				mu2
	w.SetParams(9.8,	0.02,			0.01,			0.01,	(double)dInfinity, (double)dInfinity, 
		// slip1,	slip2,	soft_erp, soft_cfm)
		0.15,		0.15,	1,			0.02);

	bestCar = new Car(w, CarChromossome(		// 0.5 0.8 0.4 0.4 0 0.7 3
		//mass,	width,	height,		length, off_mass, off_width	off_height, off_length
		0.2,	1,		0.2,		1.5,		0.3,	0.8,		0.15,		1.2
		//off_x, off_y,		off_z,	wheelMass wheelRadius, wheelWidth, wheel_x, wheel_y, wheel_z, serp
		, 0,		0,		-3,		0.05,	0.225,		0.325,		0.9,	 0.6,	-0.7,		0.2
		//scfm,		stop_erp, stop_cfm, cfm,	mforce,	  mforce2, fudgefactor)
		, 0.01,		0.2,		0.01,	0,		1,			0.4,		0.2), 0);

	test = true;
	//(double mass, double width, double height, double length, double off_mass, double off_width
	//, double off_height, double off_length, double off_x, double off_y, double off_z, double wheelMass
	//, double wheelRadius, double wheelWidth, double wheel_x, double wheel_y, double wheel_z, double serp
	//, double scfm, double stop_erp, double stop_cfm, double cfm, double mforce, double mforce2, double fudgefactor)

	Track t(XYZ(0, 0, 0));
	t.Random(10);
	t.Make(w);
	w.SetInputResolver(command);
	w.SetLoopFunction(l);
	w.GetCamera()->Free();
	w.GetCamera()->Attach(*bestCar);
	w.GetCamera()->SetAttachType(Camera::AttachType::Normal);
	w.SetTimeDependent(true);
	carControl = true;
	w.Start();
	 
	return 0;
}
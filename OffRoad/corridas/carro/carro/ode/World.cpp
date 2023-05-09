#include "World.h"
#include <stdlib.h>
#include <time.h>

/// Defini��o de vari�vel est�tica auxiliar que serve para chamar os m�todos do �ltimo World criado.
World * World::handler;
const double World::STEP_T = 5;			// o tempo que dura cada passo na simula��o (em ms)
const double World::STEP_SIZE = 0.05;	// o tamanho do step que d� quando a simula��o n�o est� dependente do tempo



// Para GA
void World::SetParams(double gravity, double angularDampening, double linearDampening, double aerodynamic
					  , double mu, double mu2, double slip1, double slip2, double soft_erp, double soft_cfm)
{
	this->gravity = (dReal) -gravity;
	dWorldSetGravity(this->world, 0, 0, this->gravity);
	this->doDampening = true;
	this->doAerodynamics = true;
	this->angularDampening = angularDampening;
	this->linearDampening = linearDampening;
	this->aerodynamic = aerodynamic;
	this->mu = mu;
	this->mu2 = mu2;
	this->slip1 = slip1;
	this->slip2 = slip2;
	this->soft_erp = soft_erp;
	this->soft_cfm = soft_cfm;
}

void World::SetParams(WorldChromossome &c)
{
	SetParams(c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9]);
}



/// Cria novo mundo com gravidade gravity.
World::World(double gravity)
{
	this->started = false;
	this->camera = Camera(*this);
	this->world = dWorldCreate();
	AddSpace(*(new Space()));
	this->contacts = dJointGroupCreate(0);
	this->gravity = (dReal) -gravity;
	dWorldSetGravity(this->world, 0, 0, this->gravity);
	dWorldSetQuickStepNumIterations(this->world, 10);
	dWorldSetAutoDisableTime(this->world, 0);
	dWorldSetAutoDisableLinearThreshold(this->world, (dReal)0.01);
	dWorldSetAutoDisableAngularThreshold(this->world, (dReal)0.01);
	dWorldSetContactSurfaceLayer(this->world, (dReal)0.001);
	dWorldSetAutoDisableSteps(this->world, 10);
	dWorldSetAutoDisableFlag(this->world, 0);
	this->ground = dCreatePlane(WorldSpace()->ID(), 0, 0, 1, 0);
	handler = this;
	this->command = NULL;
	this->timeDependent = true;
	this->doDampening = false;
	this->doAerodynamics = false;
	this->angularDampening = 0.01;
	this->linearDampening = 0.01;
	this->aerodynamic = 0.03;
	this->stepSize = STEP_SIZE;
	this->draw = true;


	this->mu = dInfinity;
	this->mu2 = dInfinity;
	this->slip1 = (dReal)0.15;
	this->slip2 = (dReal)0.15;
	this->soft_erp = (dReal)1;
	this->soft_cfm = (dReal)0.02;
}



/// Destr�i os espa�os e o mundo que criou.
World::~World()
{
	dJointGroupEmpty(this->contacts);
	dJointGroupDestroy(this->contacts);
	
	for(int i = (int)this->spaces.size() - 1; i >= 0; i--)
	{
		this->spaces[i]->~Space();
	}

	for (int i = 0; i < (int)this->rays.size(); i++)
	{
		this->rays[i]->~Ray();
	}
	dWorldDestroy(this->world);
	dCloseODE();
}



/// Altera a gravidade do mundo para gravity.
void World::SetGravity(double gravity)
{
	this->gravity = (dReal) -gravity;
	dWorldSetGravity(this->world, 0, 0, this->gravity);
}




/// Inicia a simula��o do mundo.
void World::Start()
{
	dsFunctions fn;
	char *params[3];
	int param_count = 3;

	params[1] = new char[15];
	strcpy_s(params[1], 15, "-notex");
	params[2] = new char[15];
	strcpy_s(params[2], 15, "-noshadows");
	fn.version = DS_VERSION;
	fn.start = 0;
	fn.step = &(World::LoopAux);
	fn.command = this->command;
	fn.stop = 0;
	fn.path_to_textures = "../../drawstuff/textures";
	this->started = true;
	dsSimulationLoop(param_count, params, 800, 600, &fn);
}




/// M�todo auxiliar para chamar o m�todo Reset() do �ltimo objecto World criado.
void World::ResetAux()
{
	World::handler->Reset();
}



/// M�todo auxiliar para chamar o m�todo Loop(pause) do �ltimo objecto World criado.
void World::LoopAux(int pause)
{
	World::handler->Loop(pause);
}



/// M�todo auxiliar para chamar o m�todo NearCallback(data, o1, o2) do �ltimo objecto World criado.
void World::NearCallbackAux(void *data, dGeomID o1, dGeomID o2)
{
	World::handler->NearCallback(data, o1, o2);
}



/// Ciclo principal que chama a fun��o de controlo de colis�es, avan�a no estado do mundo e desenha � medida que o faz.
void World::Loop(int pause)
{
	std::vector< Geometry* > geoms;
	std::vector< Object* > objs;
	double simulation_step, delta_t;
	int nr_of_steps = 0;

	if (pause)
	{
		return;
	}
	this->loop(pause);
	Prepare();

	if (this->timeDependent)
	{
		simulation_step = 0.001 * World::STEP_T;
		delta_t = dsElapsedTime();
		nr_of_steps = (int) ceilf((float) (delta_t / simulation_step));

		for (int i = 0; (i < nr_of_steps) && (!pause); i++)
		{
			Step(pause, simulation_step);
		}
	}
	else
	{
		Step(pause, this->stepSize);
	}
	RaysScan();

	if (this->draw)
	{
		this->Draw();
		this->GetCamera()->Refresh();
	}
}



/// Avan�a uma itera��o do mundo.
void World::Step(int pause, double step)
{
	dSpaceCollide(WorldSpace()->ID(), 0, &NearCallbackAux);
	dWorldQuickStep(this->world, (dReal) step);
	dJointGroupEmpty(this->contacts);
}



/// Efectua o scan dos rays.
void World::RaysScan()
{
	for (int i = 0; i < (int)this->rays.size(); i++)
	{
		if (this->rays[i]->IsEnabled())
		{
			this->rays[i]->Scan(*this);
		}
	}
}



/// Aplica for�as de dampening (tanto angular como linear) em obj.
void World::Dampening(Object &obj)
{
	const dReal* angularVelocity = dBodyGetAngularVel(obj.ID());
	const dReal* linearVelocity = dBodyGetLinearVel(obj.ID());

	dBodyAddTorque(obj.ID(), (dReal)(-angularVelocity[0] * this->angularDampening)
						, (dReal)(-angularVelocity[1] * this->angularDampening)
						, (dReal)(-angularVelocity[2] * this->angularDampening));
	obj.ApplyForce(-linearVelocity[0] * this->linearDampening
					, -linearVelocity[1] * this->linearDampening
					, -linearVelocity[2] * this->linearDampening);
}



/// Aplica for�as aerodin�micas em obj.
void World::Aerodynamics(Object &obj)
{
	const dReal* cv;
//	float v;
	
	cv = dBodyGetLinearVel(obj.ID());

	//obj.ApplyForce(-this->aerodynamic * sqrt(cv[0])
	//	, -this->aerodynamic * sqrt(cv[1])
	//	, -this->aerodynamic * sqrt(cv[2]));
	//v = cv[0]*cv[0] + cv[1]*cv[1] + cv[2]*cv[2];

	//if (cv[0] != 0)
	//{
	//	obj.ApplyForce(-abs(this->aerodynamic * v), 0, 0);
	//}

	//if (cv[1] != 0)
	//{
	//	obj.ApplyForce(0, -abs(this->aerodynamic * v), 0);
	//}

	//if (cv[2] != 0)
	//{
	//	obj.ApplyForce(0, 0, -abs(this->aerodynamic * v));
	//}
}
		


/// Controla as colis�es do mundo (n�o faz colis�es entre objectos do mesmo espa�o)
void World::NearCallback(void *data, dGeomID o1, dGeomID o2)
{
	dBodyID b1, b2;

	assert(o1);
	assert(o2);

	if( dGeomIsSpace(o1) || dGeomIsSpace(o2) )
	{
		dSpaceCollide2(o1, o2, data, &NearCallbackAux);
		return;
	}
	b1 = dGeomGetBody(o1);
	b2 = dGeomGetBody(o2);

	if ( (!b1 && !b2)	// se s�o ambos geometrias
				|| (b1 && !b2 && !dBodyIsEnabled(b1))	// b1 desactivado e colide s� com geometria
				|| (b2 && !b1 && !dBodyIsEnabled(b2))	// b2 desactivado e colide s� com geometria
				|| (b1 && b2 && !dBodyIsEnabled(b1) && !dBodyIsEnabled(b2))	// ambos desactivados
				|| (b1 && b2 && dAreConnectedExcluding(b1, b2, dJointTypeContact)) )	// se est�o juntos por uma junta
	{
		return;
	}
    Collide(o1, o2);
}



/// Colide as duas geometrias (cria pontos de contacto e actualiza objectos).
void World::Collide(dGeomID o1, dGeomID o2)
{
	Object *obj1, *obj2;
	Geometry* geom;
	dContact contacts[World::CONTACTS];
	int n;

	n = dCollide(o1, o2, World::CONTACTS, &(contacts[0].geom), sizeof(dContact));

	if (n > 0)
	{
		obj1 = GetObject(o1);
		obj2 = GetObject(o2);

		if( (obj1 != NULL) || (obj2 != NULL) )
		{
			for(int i = 0; i < n; i++) 
			{
				CreateContact(&contacts[i], obj1, obj2);
			}

			if( (o1 != this->ground) && (o2 != this->ground) )
			{
				if(obj1 != NULL)
				{
					obj1->Geometry()->AddTouchedGeometry(o2);
				}
				else
				{
					if ( (geom = GetGeometry(o1)) != NULL )
					{
						geom->AddTouchedGeometry(o2);
					}
				}

				if(obj2 != NULL)
				{
					obj2->Geometry()->AddTouchedGeometry(o1);
				}
				else
				{
					if ( (geom = GetGeometry(o2)) != NULL )
					{
						geom->AddTouchedGeometry(o1);
					}
				}
			}
		}
	}
}



/// Cria um ponto de contacto entre os dois objectos e devolve esse ponto.
void World::CreateContact(dContact *contact, Object *obj1, Object *obj2)
{
	dJointID c;

	contact->surface.mode = dContactSoftERP | dContactSoftCFM | dContactApprox1 | dContactSlip1 | dContactSlip2
			| dContactMu2;

	if( ((obj1 != NULL) && (obj1->GetBounce())) || ((obj2 != NULL) && (obj2->GetBounce())) )
	{
		contact->surface.mode |= dContactBounce;
		contact->surface.bounce = (dReal)1;
		contact->surface.bounce_vel = 0;	// velocidade m�nima necess�ria para bounce
	}

	//if (typeid(*obj1).name() == "class Wheel")
	//{
	//	Wheel* w = (Wheel*)obj1;
	//	contact->surface.slip2 = (dReal)0.15 * w->;
	//	contact->fdir1 = {0, 1, 0};
	//}
	//contact->surface.mu = dInfinity;
	//contact->surface.mu2 = dInfinity;
	//contact->surface.slip1 = (dReal)0.15;
	//contact->surface.slip2 = (dReal)0.15;
	//contact->surface.soft_erp = (dReal)1;
	//contact->surface.soft_cfm = (dReal)0.02;
	contact->surface.mu = (dReal)this->mu;
	contact->surface.mu2 = (dReal)this->mu2;
	contact->surface.slip1 = (dReal)this->slip1;
	contact->surface.slip2 = (dReal)this->slip2;
	contact->surface.soft_erp = (dReal)this->soft_erp;
	contact->surface.soft_cfm = (dReal)this->soft_cfm;

	c = dJointCreateContact(this->world, this->contacts, contact);
	dJointAttach(c, dGeomGetBody(contact->geom.g1), dGeomGetBody(contact->geom.g2));
}



/// Devolve o objecto correspondente a geometry ou NULL se n�o encontrar
Object * World::GetObject(dGeomID geometry)
{
	Object *tmp;

	for (int i = 0; i < (int)this->spaces.size(); i++)
	{
		tmp = this->spaces[i]->GetObject(geometry);

		if (tmp != NULL)
		{
			return tmp;
		}
	}

	return NULL;
}



/// Devolve a geometria correspondente a geometry ou NULL se n�o encontrar
Geometry * World::GetGeometry(dGeomID geometry)
{
	Geometry *tmp;

	for (int i = 0; i < (int)this->spaces.size(); i++)
	{
		tmp = this->spaces[i]->GetGeometry(geometry);

		if (tmp != NULL)
		{
			return tmp;
		}
	}

	return NULL;
}



/// Desenha os objectos que pertencem ao mundo
void World::Draw()
{
	for(unsigned int i = 0; i < this->spaces.size(); i++)
	{
		this->spaces[i]->Draw();
	}
}



/// Coloca os objectos e geometrias do mundo nas suas posi��es iniciais.
void World::Reset()
{
	for(unsigned int i = 0; i < this->spaces.size(); i++)
	{
		this->spaces[i]->Reset();
	}
}



/// Adiciona um espa�o ao mundo.
void World::AddSpace(Space &space)
{
	this->spaces.push_back(&space);
}



/// Atribui uma fun��o para controlar as ac��es relacionadas com o input.
void World::SetInputResolver(void (*command)(int cmd))
{
	this->command = command;
}



/// Devolve a c�mera.
Camera* World::GetCamera()
{
	return &(this->camera);
}



/// Devolve o espa�o "default" do mundo.
Space * World::WorldSpace()
{
	return this->spaces[0];
}



/// Devolve os objectos contidos no mundo.
std::vector< Object * > World::GetObjects()
{
	std::vector< Object * > objects;

	for(unsigned int i = 0; i < this->spaces.size(); i++)
	{
		this->spaces[i]->GetObjects(objects);
	}

	return objects;
}



/// Devolve as geometrias contidas no mundo.
std::vector< Geometry * > World::GetGeometries()
{
	std::vector< Geometry * > geometries;

	for(unsigned int i = 0; i < this->spaces.size(); i++)
	{
		this->spaces[i]->GetGeometries(geometries);
	}

	return geometries;
}



/// Estabelece uma fun��o para correr cada vez que o loop principal terminar.
void World::SetLoopFunction(void (*loop)(int))
{
	this->loop = loop;
}



/// Adiciona um ray ao mundo.
void World::AddRay(Ray *ray)
{
	this->rays.push_back(ray);
}



/// Prepara os objectos e geometrias nos espa�os para mais um ciclo.
void World::Prepare()
{
	std::vector< Object * > objects;

	for (int j = 0; j < (int) this->spaces.size(); j++)
	{
		objects.clear();
		this->spaces[j]->GetObjects(objects);

		for (int k = 0; k < (int) objects.size(); k++)
		{
			if (this->doDampening)
			{
				Dampening(*(objects[k]));
			}

			if (this->doAerodynamics)
			{
				Aerodynamics(*(objects[k]));
			}
		}
	}

	for(unsigned int i = 0; i < this->spaces.size(); i++)
	{
		this->spaces[i]->Prepare();
	}
}



/// Devolve os objectos contidos no mundo excepto os que pertencem a space.
std::vector< Object * > World::GetObjectsExcept(dSpaceID space)
{
	std::vector< Object * > objects;

	for(unsigned int i = 0; i < this->spaces.size(); i++)
	{
		if(this->spaces[i]->ID() != space)
		{
			this->spaces[i]->GetObjects(objects);
		}
	}

	return objects;
}



/// Devolve as geometrias contidas no mundo excepto as que pertencem a space.
std::vector< Geometry * > World::GetGeometriesExcept(dSpaceID space)
{
	std::vector< Geometry * > geometries;

	for(unsigned int i = 0; i < this->spaces.size(); i++)
	{
		if(this->spaces[i]->ID() != space)
		{
			this->spaces[i]->GetGeometries(geometries);
		}
	}

	return geometries;
}



/// Devolve a identifica��o do mundo.
dWorldID World::ID()
{
	return this->world;
}



/// Se value for true a simula��o passa a ser dependente do tempo. Isto quer dizer
/// que a simula��o demorar� o mesmo tempo em qualquer PC que corra.
void World::SetTimeDependent(bool value)
{
	this->timeDependent = value;
}



/// Indica se a simula��o � dependente do tempo ou n�o.
bool World::GetTimeDependent()
{
	return this->timeDependent;
}



/// Activa ou desactiva as for�as de dampening.
void World::SetDoDampening(bool value)
{
	this->doDampening = value;
}



/// Indica se as for�as de dampening est�o activadas.
bool World::GetDoDampening()
{
	return this->doDampening;
}



/// Activa ou desactiva as for�as aerodin�micas.
void World::SetDoAerodynamics(bool value)
{
	this->doAerodynamics = value;
}



/// Indica se estamos a criar aerodin�mica.
bool World::GetDoAerodynamics()
{
	return this->doAerodynamics;
}



/// Estabelece o valor de angular dampening.
void World::SetAngularDampening(double value)
{
	this->angularDampening = value;
}



/// Devolve o valor de angular dampening.
double World::GetAngularDampening()
{
	return this->angularDampening;
}



/// Estabelece o valor de linear dampening.
void World::SetLinearDampening(double value)
{
	this->linearDampening = value;
}



/// Devolve o valor de linear dampening.
double World::GetLinearDampening()
{
	return this->linearDampening;
}



/// Estabelece o valor da for�a aerodin�mica a aplicar.
void World::SetAerodynamic(double value)
{
	this->aerodynamic = value;
}



/// Devolve o valor da for�a aerodin�mica.
double World::GetAerodynamic()
{
	return this->aerodynamic;
}



/// Indica se o mundo j� come�ou.
bool World::Started()
{
	return this->started;
}



/// Apaga um objecto do mundo.
bool World::RemoveObject(Object* object)
{
	for (int i = 0; i < (int) this->spaces.size(); i++)
	{
		if (this->spaces[i]->RemoveObject(object))
		{
			return true;
		}
	}

	return false;
}



/// Retira um espa�o do mundo e apaga-o.
bool World::RemoveSpace(Space *space)
{
	for (int i = (int)this->spaces.size() - 1; i >= 0; i--)
	{
		if (this->spaces[i]->ID() == space->ID())
		{
			this->spaces.erase(this->spaces.begin() + i);
			space->~Space();

			return true;
		}
	}

	return false;
}



/// Apaga um ray se este existir e devolve um booleano indicando se o removeu.
bool World::RemoveRay(Ray *ray)
{
	for (int i = 0; i < (int) this->rays.size(); i++)
	{
		if (this->rays[i]->ID() == ray->ID())
		{
			this->rays.erase(this->rays.begin() + i);
			ray->~Ray();

			return true;
		}
	}

	return false;
}



/// Estabelece o stepSize usado na simula��o quando esta n�o � dependente do tempo.
void World::SetStepSize(double value)
{
	if (value > 0)
	{
		this->stepSize = value;
	}
}



/// Devolve o stepSize usado na simula��o quando esta n�o � dependente do tempo.
double World::GetStepSize() const
{
	return this->stepSize;
}



void World::SetDraw(bool draw)
{
	this->draw = draw;
}



bool World::GetDraw() const
{
	return this->draw;
}
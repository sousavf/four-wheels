#include <ode/ode.h>
#include "FixedJoint.h"
#include "Car.h"

const double Car::COMOFFSET = -1;

Car::Car(World &world, CarChromossome &c, double x)
		:Chassis(world, c[0], c[1], c[2], c[3])
{
	Init(world, c[0], c[1], c[2], c[3]
	, c[11], c[12], c[13], XYZ(c[14], c[15], c[16])
	, c[4], c[5], c[6], c[7], XYZ(c[8], c[9], c[10])
	, c[17], c[18], c[19], c[20], c[21], c[22], c[23], c[24]
	, XYZ(x, 0, 0));
}

/// Para algoritmo genético
Car::Car(World &world, double mass, double width, double height, double length
			, double wheelMass, double wheelRadius, double wheelWidth, XYZ wheelPosOff
			, double offMass, double offWidth, double offHeight, double offLength, XYZ offPos
			, double S_ERP, double S_CFM, double Stop_ERP, double Stop_CFM, double CFM, double M_Force
			, double M_Force2, double FudgeFactor
			, XYZ position)
					:Chassis(world, mass, width, height, length)
{
	Init(world, mass, width, height, length, wheelMass, wheelRadius, wheelWidth, wheelPosOff
			, offMass, offWidth, offHeight, offLength, offPos, S_ERP, S_CFM, Stop_ERP, Stop_CFM
			, CFM, M_Force, M_Force2, FudgeFactor, position);
}



void Car::Init(World &world, double mass, double width, double height, double length
			, double wheelMass, double wheelRadius, double wheelWidth, XYZ wheelPosOff
			, double offMass, double offWidth, double offHeight, double offLength, XYZ offPos
			, double S_ERP, double S_CFM, double Stop_ERP, double Stop_CFM, double CFM, double M_Force
			, double M_Force2, double FudgeFactor
			, XYZ position)
{
	Space* carSpace = new Space(*world.WorldSpace());
	FixedJoint* j = new FixedJoint(world);
	XYZ chassisPosition, wheelsPosition[WHEELS_COUNT], axis;
	double x, y;

	// cria o centro de massa COMOFFSET unidades abaixo do chassis
	chassisPosition.SetXYZ(position.x, position.y, wheelRadius * 2);
	this->geometry->SetPosition(chassisPosition);
	this->chassisOffset = new Box(world, offMass, offWidth, offHeight, offLength, false);
	this->chassisOffset->Geometry()->SetPosition(XYZ(chassisPosition.x  + 0.5 * width * offPos.x
			, chassisPosition.y + 0.5 * length * offPos.y
			, chassisPosition.z + 0.5 * height * offPos.z));
	j->Attach(*this, *(this->chassisOffset));
	j->SetFixed();
	this->chassisOffset->Geometry()->SetColor(Geometry::Color::Blue);
	carSpace->AddObject(*this->chassisOffset);
	//this->chassisOffset->Geometry()->RemoveFromSpace();

	// adiciona o carro ao espaço
	carSpace->AddObject(*this);

	// cria as rodas
	this->wheels = new Wheel[WHEELS_COUNT];

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].Init(world, wheelMass, wheelRadius, wheelWidth);
		x = ((i == FRONT_LEFT || i == REAR_LEFT) ? -1 : 1);
		x *= wheelPosOff.x;
		y = ((i == FRONT_LEFT || i == FRONT_RIGHT) ? 1 : - 1);
		y *= wheelPosOff.y;
		wheelsPosition[i].x = chassisPosition.x + x * 0.5 * width;
		wheelsPosition[i].y = chassisPosition.y + y * 0.5 * length;
		wheelsPosition[i].z = chassisPosition.z - 0.5 * height + wheelPosOff.z * wheelRadius;
		this->wheels[i].Geometry()->SetPosition(wheelsPosition[i]);
		this->wheels[i].Geometry()->SetRotation(XYZ(0, 90, 0));
	}

	// cria joints
	this->joints = new Hinge2Joint*[WHEELS_COUNT];

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->joints[i] = new Hinge2Joint(world);
		this->joints[i]->Attach(this->body, this->wheels[i].ID());
		this->joints[i]->SetAnchor(wheelsPosition[i]);
		axis.SetXYZ(0, 0, 1);
		this->joints[i]->SetAxis1(axis);
		axis.SetXYZ(1, 0, 0);
		this->joints[i]->SetAxis2(axis);
		this->joints[i]->SetParameter(Joint::SuspensionERP, S_ERP);
		this->joints[i]->SetParameter(Joint::SuspensionCFM, S_CFM);
		this->joints[i]->SetParameter(Joint::StopERP, Stop_ERP);
		this->joints[i]->SetParameter(Joint::StopCFM, Stop_CFM);
		this->joints[i]->SetParameter(Joint::Bouncyness, 0);
		this->joints[i]->SetParameter(Joint::CFM, CFM);

		if ( (i == FRONT_LEFT) || (i == FRONT_RIGHT) )
		{
			this->joints[i]->SetParameter(Joint::MaximumForce, M_Force);
			this->joints[i]->SetParameter(Joint::MaximumForce2, M_Force2);
			this->joints[i]->SetParameter(Joint::FudgeFactor, FudgeFactor);
			this->joints[i]->SetParameter(Joint::LowStop, -1);
			this->joints[i]->SetParameter(Joint::HighStop, 1);
			this->joints[i]->SetParameter(Joint::LowStop, -1);
			this->joints[i]->SetParameter(Joint::HighStop, 1);
		}
		else
		{
			this->joints[i]->SetParameter(Joint::LowStop, 0.0);
			this->joints[i]->SetParameter(Joint::HighStop, 0.0);
			this->joints[i]->SetParameter(Joint::LowStop, 0.0);
			this->joints[i]->SetParameter(Joint::HighStop, 0.0);
		}
		carSpace->AddObject(this->wheels[i]);
	}
	world.AddSpace(*carSpace);
	this->space = carSpace;
	this->averageSpeed = 0;
	this->averageDirection = 0;
}


/// Cria um novo carro em world com mass, width, height, length e 4 rodas com wheelMass,
/// wheelRadius e wheelWidth, na posição (x, y).
Car::Car(World &world, double mass, double width, double height, double length
			, double wheelMass, double wheelRadius, double wheelWidth, XYZ position)
					:Chassis(world, mass, width, height, length)
{
	Init(world, mass, width, height, length, wheelMass, wheelRadius, wheelWidth, position);
}



/// Cria um novo carro em world com mass, width, height, length e 4 rodas com wheelMass,
/// wheelRadius e wheelWidth.
Car::Car(World &world, double mass, double width, double height, double length
			, double wheelMass, double wheelRadius, double wheelWidth)
					:Chassis(world, mass, width, height, length)
{
	Init(world, mass, width, height, length, wheelMass, wheelRadius, wheelWidth, XYZ(0, 0, 0));
}



/// Cria um novo carro em world com mass, width, height, length e 4 rodas com wheelMass,
/// wheelRadius e wheelWidth.
void Car::Init(World &world, double mass, double width, double height, double length
					, double wheelMass, double wheelRadius, double wheelWidth, XYZ position)
{
	Space* carSpace = new Space(*world.WorldSpace());
	FixedJoint* j = new FixedJoint(world);
	XYZ chassisPosition, wheelsPosition[WHEELS_COUNT], axis;
	double x, y;

	// cria o centro de massa COMOFFSET unidades abaixo do chassis
	chassisPosition.SetXYZ(position.x, position.y, wheelRadius * 2);
	this->geometry->SetPosition(chassisPosition);
	this->chassisOffset = new Box(world, mass , width, height, length, false);
	this->chassisOffset->Geometry()->SetPosition(XYZ(chassisPosition.x, chassisPosition.y
			, chassisPosition.z - height + COMOFFSET));
	j->Attach(*this, *(this->chassisOffset));
	j->SetFixed();
	this->chassisOffset->Geometry()->RemoveFromSpace();

	// adiciona o carro ao espaço
	carSpace->AddObject(*this);

	// cria as rodas
	this->wheels = new Wheel[WHEELS_COUNT];

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].Init(world, wheelMass, wheelRadius, wheelWidth);
		x = (i == FRONT_LEFT || i == REAR_LEFT) ? -1 : 1;
		y = (i == FRONT_LEFT || i == FRONT_RIGHT) ? 1 : - 1;
		wheelsPosition[i].x = chassisPosition.x + x * 0.5 * width;
		wheelsPosition[i].y = chassisPosition.y + y * 0.5 * length;
		wheelsPosition[i].z = chassisPosition.z - 0.5 * height;
		this->wheels[i].Geometry()->SetPosition(wheelsPosition[i]);
		this->wheels[i].Geometry()->SetRotation(XYZ(0, 90, 0));
	}

	// cria joints
	this->joints = new Hinge2Joint*[WHEELS_COUNT];

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->joints[i] = new Hinge2Joint(world);
		this->joints[i]->Attach(this->body, this->wheels[i].ID());
		this->joints[i]->SetAnchor(wheelsPosition[i]);
		axis.SetXYZ(0, 0, 1);
		this->joints[i]->SetAxis1(axis);
		axis.SetXYZ(1, 0, 0);
		this->joints[i]->SetAxis2(axis);
		this->joints[i]->SetParameter(Joint::MotorParameter::SuspensionERP, 0.2);
		this->joints[i]->SetParameter(Joint::MotorParameter::SuspensionCFM, 0.01);
		this->joints[i]->SetParameter(Joint::MotorParameter::StopERP, 0.2);
		this->joints[i]->SetParameter(Joint::MotorParameter::StopCFM, 0.01);
		this->joints[i]->SetParameter(Joint::MotorParameter::Bouncyness, 0);
		this->joints[i]->SetParameter(Joint::MotorParameter::CFM, 0);

		if ( (i == FRONT_LEFT) || (i == FRONT_RIGHT) )
		{
			this->joints[i]->SetParameter(Joint::MotorParameter::MaximumForce, 1);
			this->joints[i]->SetParameter(Joint::MotorParameter::MaximumForce2, 0.4);
			this->joints[i]->SetParameter(Joint::MotorParameter::FudgeFactor, 0.2);
			this->joints[i]->SetParameter(Joint::MotorParameter::LowStop, -1);
			this->joints[i]->SetParameter(Joint::MotorParameter::HighStop, 1);
			this->joints[i]->SetParameter(Joint::MotorParameter::LowStop, -1);
			this->joints[i]->SetParameter(Joint::MotorParameter::HighStop, 1);
		}
		else
		{
			this->joints[i]->SetParameter(Joint::MotorParameter::LowStop, 0.0);
			this->joints[i]->SetParameter(Joint::MotorParameter::HighStop, 0.0);
			this->joints[i]->SetParameter(Joint::MotorParameter::LowStop, 0.0);
			this->joints[i]->SetParameter(Joint::MotorParameter::HighStop, 0.0);
		}
		carSpace->AddObject(this->wheels[i]);
	}
	world.AddSpace(*carSpace);
	this->space = carSpace;
	this->averageSpeed = 0;
	this->averageDirection = 0;
	SetCategory(2);
	SetCollide(1);
}



/// Destrói o carro.
Car::~Car()
{
	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].~Wheel();
		this->joints[i]->~Hinge2Joint();
	}
	this->chassisOffset->~Box();
}



/// Devolve as rodas.
Wheel* Car::GetWheels()
{
	return this->wheels;
}



/// Devolve as joints.
Hinge2Joint** Car::GetJoints()
{
	return this->joints;
}



/// Roda as rodas da frente do carro na quantidade determinada.
void Car::Steer(double value)
{
	for (int i = FRONT_LEFT; i <= FRONT_RIGHT; i++)
	{
		this->joints[i]->SetParameter(Joint::MotorParameter::Velocity
									, value - this->joints[i]->GetAngle1());
	}
	this->averageDirection = (this->averageDirection + value) * 0.5;
}



/// Aplica uma velocidade específica às rodas do carro.
void Car::Accelerate(double value)
{
	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		if ( (i == FRONT_LEFT) || (i == FRONT_RIGHT) )
		{
			this->joints[i]->SetParameter(Joint::MotorParameter::Velocity2, value);
		}
		else
		{
			this->joints[i]->SetParameter(Joint::MotorParameter::Velocity2, -value);
		}
	}
	this->averageSpeed = (this->averageSpeed + value) * 0.5;
}



/// Coloca o carro no estado inicial.
void Car::Reset()
{
	Object::Reset();
	this->chassisOffset->Reset();

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].Reset();
	}
}



/// Devolve True se este objecto tocou em geometry na última iteração do mundo.
bool Car::Touched(::Geometry &geometry) const
{
	if (Object::Touched(geometry))
	{
		return true;
	}

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		if (this->wheels[i].Touched(geometry))
		{
			return true;
		}
	}

	return false;
}



/// Devolve True se este objecto tocou em object na última iteração do mundo.
bool Car::Touched(Object& object) const
{
	return Touched(*(object.Geometry()));
}



/// Indica se o carro tocou em alguma coisa.
bool Car::WasTouched() const
{
	if (Object::WasTouched())
	{
		return true;
	}

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		if (this->wheels[i].WasTouched())
		{
			return true;
		}
	}

	return false;
}



/// Devolve o espaço que o carro ocupa.
Space* Car::GetSpace() const
{
	return this->space;
}



/// Devolve a velocidade a que as rodas estão a rodar.
double Car::WheelVelocity() const
{
	return this->joints[FRONT_LEFT]->GetParameter(Joint::Velocity2);
}



/// Devolve a direcção em que as rodas se encontram.
double Car::WheelDirection() const
{
	return this->joints[FRONT_LEFT]->GetAngle1();
}



/// Devolve a velocidade média das rodas.
double Car::AverageWheelVelocity() const
{
	return this->averageSpeed;
}



/// Define a categoria do carro (e de todas as geometrias do carro).
void Car::SetCategory(long bits)
{
	Geometry()->SetCategory(bits);
	this->chassisOffset->Geometry()->SetCategory(bits);
	
	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].Geometry()->SetCategory(bits);
	}
}



/// Define com o que colide.
void Car::SetCollide(long bits)
{
	Geometry()->SetCollide(bits);
	this->chassisOffset->Geometry()->SetCollide(bits);
	
	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].Geometry()->SetCollide(bits);
	}
}



/// Define a transparência do carro e das rodas.
void Car::SetTransparency(Geometry::Transparency value)
{
	Geometry()->SetTransparency(value);

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].Geometry()->SetTransparency(value);
	}
}



/// Define se o carro se encontra activo ou inactivo.
void Car::SetEnable(bool value)
{
	Object::SetEnable(value);
	this->chassisOffset->SetEnable(value);
	
	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].SetEnable(value);
	}
}



/// Coloca o carro na posição determinada
void Car::SetPosition(XYZ position)
{
	Geometry()->SetPosition(position);
	this->chassisOffset->Geometry()->SetPosition(position);

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].Geometry()->SetPosition(position);
	}
}



/// Devolve a direcção média do carro
double Car::AverageWheelDirection() const
{
	return this->averageDirection;
}




double Car::Velocity()
{
	const dReal* v = dBodyGetLinearVel(this->ID());

	return sqrt( v[0]*v[0] + v[1]*v[1] );
}
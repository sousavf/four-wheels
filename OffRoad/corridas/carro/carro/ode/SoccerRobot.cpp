#include "SoccerRobot.h"
#include "World.h"

const double SoccerRobot::SHOOT_TIME = 100;

/// Cria um jogador nas coordenadas origem com os valores por defeito.
SoccerRobot::SoccerRobot(World &world):leg(world, 0.25, 0.4, 0.8)
{
	Init(world, 2, 1.0, 1.6, 0.25, 0.4, 0.8, 0.5, 0.35, 0.35, XYZ(0, 0, 0));
}



/// Cria um jogador numa posição específica com os valores por defeito.
SoccerRobot::SoccerRobot(World &world, XYZ position):leg(world, 0.25, 0.4, 0.8)
{
	Init(world, 2, 0.8, 1.6, 0.25, 0.4, 0.8, 0.5, 0.35, 0.35, position);
}



/// Cria um novo jogador com massa, raio e altura do corpo definidos e os restantes parâmetros em proporção.
SoccerRobot::SoccerRobot(World &world, double bodyMass, double bodyRadius, double bodyHeight)
					:leg(world, bodyMass * 0.5, bodyRadius * 0.5, bodyHeight * 0.5)
{
	Init(world, bodyMass, bodyRadius, bodyHeight, bodyMass * 0.5, bodyRadius * 0.5
		, bodyHeight * 0.5, bodyMass * 0.25, bodyRadius * 0.3, bodyRadius * 0.25, XYZ(0, 0, 0));
}



/// Cria um novo jogador com massa, raio e altura do corpo e posição definidos e os restantes parâmetros
/// em proporção.
SoccerRobot::SoccerRobot(World &world, double bodyMass, double bodyRadius, double bodyHeight, XYZ position)
					:leg(world, bodyMass * 0.5, bodyRadius * 0.5, bodyHeight * 0.5)
{
	Init(world, bodyMass, bodyRadius, bodyHeight, bodyMass * 0.5, bodyRadius * 0.5
		, bodyHeight * 0.5, bodyMass * 0.25, bodyRadius * 0.3, bodyRadius * 0.25, position);
}



/// Cria um jogador com os parâmetros do corpo e das rodas definidos.
SoccerRobot::SoccerRobot(World &world, double bodyMass, double bodyRadius, double bodyHeight
		, double wheelMass, double wheelRadius, double wheelWidth)
			:leg(world, bodyMass * 0.5, bodyRadius * 0.5, bodyHeight * 0.5)
{
	Init(world, bodyMass, bodyRadius, bodyHeight, bodyMass * 0.5, bodyRadius * 0.5
		, bodyHeight * 0.5, wheelMass, wheelRadius, wheelWidth, XYZ(0, 0, 0));
}



/// Cria um jogador com os parâmetros do corpo, das rodas e posição definidos.
SoccerRobot::SoccerRobot(World &world, double bodyMass, double bodyRadius, double bodyHeight
		, double wheelMass, double wheelRadius, double wheelWidth, XYZ position)
			:leg(world, bodyMass * 0.5, bodyRadius * 0.5, bodyHeight * 0.5)
{
	Init(world, bodyMass, bodyRadius, bodyHeight, bodyMass * 0.5, bodyRadius * 0.5
		, bodyHeight * 0.5, wheelMass, wheelRadius, wheelWidth, position);
}



/// Cria um jogador com os parâmetros do corpo, perna e rodas definidos.
SoccerRobot::SoccerRobot(World &world, double bodyMass, double bodyRadius, double bodyHeight
		, double legMass, double legRadius, double legLength
		, double wheelMass, double wheelRadius, double wheelWidth)
			:leg(world, legMass, legRadius, legLength)
{
	Init(world, bodyMass, bodyRadius, bodyHeight, legMass, legRadius, legLength, wheelMass
		, wheelRadius, wheelWidth, XYZ(0, 0, 0));
}



/// Cria um jogador com todos os parâmetros definidos.
SoccerRobot::SoccerRobot(World &world, double bodyMass, double bodyRadius, double bodyHeight
		, double legMass, double legRadius, double legLength
		, double wheelMass, double wheelRadius, double wheelWidth, XYZ position)
			:leg(world, legMass, legRadius, legLength)
{
	Init(world, bodyMass, bodyRadius, bodyHeight, legMass, legRadius, legLength, wheelMass
		, wheelRadius, wheelWidth, position);
}



/// Cria um jogador com todos os parâmetros definidos.
void SoccerRobot::Init(World &world, double bodyMass, double bodyRadius, double bodyHeight
		, double legMass, double legRadius, double legLength
		, double wheelMass, double wheelRadius, double wheelWidth, XYZ position)
{
	dMass m;
	XYZ wheelsPosition[WHEELS_COUNT], axis;
	FixedJoint* j = new FixedJoint(world);
	int x, y;

	// corpo
	Object::Init(world, bodyMass);
	this->mass = bodyMass;
	dMassSetBoxTotal(&m, (dReal) bodyMass, (dReal) bodyRadius * 2, (dReal) bodyRadius * 2, (dReal) bodyHeight);
	dBodySetMass(this->body, &m);
	this->geometry = new BoxGeometry(*(world.WorldSpace()), bodyRadius * 2, bodyHeight, bodyRadius * 2,
									Geometry::Gray);
	dGeomSetBody(this->geometry->ID(), this->body);
	this->space = new Space(*world.WorldSpace());
	this->legJoint = new SliderJoint(world);


	// posições relativas
	Geometry()->SetPosition(XYZ(position.x, position.y, position.z + wheelRadius * 0.2 + bodyHeight * 0.5));
	this->leg.Geometry()->SetPosition(XYZ(position.x, position.y + bodyRadius - legLength * 0.5
								, position.z + wheelRadius * 0.25 + bodyHeight * 0.25));
	this->leg.Geometry()->SetRotation(XYZ(90, 0, 0));

	
	// wheels
	wheels = new Wheel[WHEELS_COUNT];
	
	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		wheels[i].Init(world, wheelMass, wheelRadius, wheelWidth);
		x = (i % 2 == 0) ? -1 : 1;
		y = (i < 2) ? 1 : -1;
		wheelsPosition[i].x = position.x + x * bodyRadius - x * wheelWidth * 0.5;
		wheelsPosition[i].y = position.y + y * bodyRadius - y * wheelRadius;
		wheelsPosition[i].z = wheelRadius;
		wheels[i].Geometry()->SetRotation(XYZ(0, 90, 0));
		wheels[i].Geometry()->SetPosition(wheelsPosition[i]);
	}


	// joints
	joints = new Hinge2Joint*[WHEELS_COUNT];

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		joints[i] = new Hinge2Joint(world);
		joints[i]->Attach(this->body, wheels[i].ID());
		joints[i]->SetAnchor(wheelsPosition[i]);
		axis.SetXYZ(0, 0, 1);
		joints[i]->SetAxis1(axis);
		axis.SetXYZ(1, 0, 0);
		joints[i]->SetAxis2(axis);
		joints[i]->SetParameter(Joint::SuspensionERP, 0.2);
		joints[i]->SetParameter(Joint::SuspensionCFM, 0.01);
		joints[i]->SetParameter(Joint::StopERP, 0.2);
		joints[i]->SetParameter(Joint::StopCFM, 0.01);
		joints[i]->SetParameter(Joint::Bouncyness, 0);
		joints[i]->SetParameter(Joint::CFM, 0);
		joints[i]->SetParameter(Joint::MaximumForce, 1);
		joints[i]->SetParameter(Joint::MaximumForce2, 2);
		joints[i]->SetParameter(Joint::FudgeFactor, 0.2);
		joints[i]->SetParameter(Joint::LowStop, 0.0);
		joints[i]->SetParameter(Joint::HighStop, 0.0);
		joints[i]->SetParameter(Joint::LowStop, 0.0);
		joints[i]->SetParameter(Joint::HighStop, 0.0);
		space->AddObject(wheels[i]);
	}
	legJoint->Attach(*this, this->leg);
	legJoint->SetAxis(XYZ(0, -1, 0));
	legJoint->SetParameter(Joint::HighStop, 0.5);
	legJoint->SetParameter(Joint::LowStop, 0);
	legJoint->SetParameter(Joint::HighStop, 0.5);
	legJoint->SetParameter(Joint::LowStop, 0);
	legJoint->SetParameter(Joint::Bouncyness, 0);
	legJoint->SetParameter(Joint::CFM, 1);
	legJoint->SetParameter(Joint::StopCFM, 0);
	legJoint->SetParameter(Joint::StopERP, 0);
	legJoint->SetParameter(Joint::MaximumForce, 100);
	space->AddObject(*this);
	space->AddObject(this->leg);
	world.AddSpace(*space);

	this->shootingStrength = 100;
	this->shootingRecall = 100;
	this->controlType = SoccerRobot::JointVelocity;
}



/// Destrói o jogador
SoccerRobot::~SoccerRobot()
{
	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].~Wheel();
		this->joints[i]->~Hinge2Joint();
	}
	this->leg.~Cylinder();
	this->legJoint->~SliderJoint();
	this->shootTimer.~Timer();
	delete this->joints;
}



/// Devolve as rodas do jogador.
Wheel* SoccerRobot::GetWheels()
{
	return this->wheels;
}



/// Devolve as juntas do jogador.
Hinge2Joint** SoccerRobot::GetJoints()
{
	return this->joints;
}



/// Acelera as rodas do lado esquerdo.
void SoccerRobot::AccelerateLeft(double value)
{
	switch(this->controlType)
	{
		case SoccerRobot::JointTorque:
			for (int i = 0; i < WHEELS_COUNT; i++)
			{
				if (i % 2 == 0)
				{
					dJointAddHinge2Torques(this->joints[i]->ID(), 0, (dReal)value);
				}
			}
			break;

		default:
		case SoccerRobot::JointVelocity:
			for (int i = 0; i < WHEELS_COUNT; i++)
			{
				if (i % 2 == 0)
				{
					this->joints[i]->SetParameter(Joint::Velocity2, value);
				}
			}
			break;
	}
}



/// Acelera as rodas do lado direito.
void SoccerRobot::AccelerateRight(double value)
{
	switch(this->controlType)
	{
		case SoccerRobot::JointTorque:
			for (int i = 0; i < WHEELS_COUNT; i++)
			{
				if (i % 2 != 0)
				{
					dJointAddHinge2Torques(this->joints[i]->ID(), 0, (dReal)value);
				}
			}
			break;

		default:
		case SoccerRobot::JointVelocity:
			for (int i = 0; i < WHEELS_COUNT; i++)
			{
				if (i % 2 != 0)
				{
					this->joints[i]->SetParameter(Joint::Velocity2, value);
				}
			}
			break;
	}
}



/// Coloca a velocidade e a direcção das rodas a 0.
void SoccerRobot::Stop()
{
	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->joints[i]->SetParameter(Joint::Velocity2, 0);
		this->joints[i]->SetParameter(Joint::Velocity, 0);
	}
}



/// Remata com a força definida.
void SoccerRobot::Shoot()
{
	if (this->shootTimer.IsStopped())
	{
		switch(this->controlType)
		{
			case SoccerRobot::JointTorque:
				dJointAddSliderForce(this->legJoint->ID(), (dReal) this->shootingStrength);
				break;

			default:
			case SoccerRobot::JointVelocity:
				this->legJoint->SetParameter(Joint::Velocity, this->shootingStrength);
				break;
		}
		this->shootTimer.Start();
	}
}



/// Coloca a perna na posição inicial.
void SoccerRobot::Recall()
{
	this->legJoint->SetParameter(Joint::Velocity, -0.25);
}



/// Define a força do remate se value > 0.
void SoccerRobot::SetShootingStrength(double value)
{
	if (value > 0)
	{
		this->shootingStrength = value;
	}
}



/// Define a força do recall a seguir a rematar se value > 0.
void SoccerRobot::SetShootingRecall(double value)
{
	if (value > 0)
	{
		this->shootingRecall = -value;
	}
}



/// Indica a força do remate.
double SoccerRobot::GetShootingStrength() const
{
	return this->shootingStrength;
}



/// Indica a força do recall.
double SoccerRobot::GetShootingRecall() const
{
	return this->shootingRecall;
}



/// Coloca o jogador com os parâmetros iniciais.
void SoccerRobot::Reset()
{
	Stop();
	Object::Reset();
	this->leg.Reset();

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].Reset();
	}
}



/// Indica se o jogador tocou em geometry.
bool SoccerRobot::Touched(::Geometry &geometry) const
{
	if (Object::Touched(geometry) || this->leg.Touched(geometry))
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



/// Indica se o jogador tocou em object.
bool SoccerRobot::Touched(Object& object) const
{
	return Touched(*(object.Geometry()));
}



/// Indica se o jogador foi tocado.
bool SoccerRobot::WasTouched() const
{
	if (Object::WasTouched() || this->leg.WasTouched())
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



/// Devolve o espaço do jogador.
Space* SoccerRobot::GetSpace() const
{
	return this->space;
}



/// Indica a velocidade das rodas do lado esquerdo.
double SoccerRobot::LeftWheelsVelocity() const
{
	double sum = 0;

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		if (i % 2 == 0)
		{
			sum += this->joints[i]->GetParameter(Joint::Velocity2);
		}
	}

	return ( sum / (WHEELS_COUNT * 0.5) );
}



/// Indica a velocidade das rodas do lado direito.
double SoccerRobot::RightWheelsVelocity() const
{
	double sum = 0;

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		if (i % 2 != 0)
		{
			sum += this->joints[i]->GetParameter(Joint::Velocity2);
		}
	}

	return ( sum / (WHEELS_COUNT * 0.5) );
}



/// Define a categoria do jogador.
void SoccerRobot::SetCategory(long bits)
{
	Geometry()->SetCategory(bits);
	this->leg.Geometry()->SetCategory(bits);

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].Geometry()->SetCategory(bits);
	}
}



/// Define com que é que o jogador colide.
void SoccerRobot::SetCollide(long bits)
{
	Geometry()->SetCollide(bits);
	this->leg.Geometry()->SetCollide(bits);

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].Geometry()->SetCollide(bits);
	}
}



/// Define a transparência do jogador.
void SoccerRobot::SetTransparency(Geometry::Transparency value)
{
	Geometry()->SetTransparency(value);
	this->leg.Geometry()->SetTransparency(value);

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].Geometry()->SetTransparency(value);
	}
}



/// Activa ou desactiva o jogador.
void SoccerRobot::SetEnable(bool value)
{
	Object::SetEnable(value);
	this->leg.SetEnable(value);

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].SetEnable(value);
	}
}



/// Define a posição do jogador.
void SoccerRobot::SetPosition(XYZ position)
{
	Geometry()->SetPosition(position);
	this->leg.Geometry()->SetPosition(position);

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].Geometry()->SetPosition(position);
	}
}



/// Define a posição inicial do jogador.
void SoccerRobot::SetStartPosition(XYZ position)
{
	Geometry()->SetStartPosition(position);
	this->leg.Geometry()->SetStartPosition(position);

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].Geometry()->SetStartPosition(position);
	}
}



/// Define o tipo de controlo que é efectuado.
void SoccerRobot::SetControlType(ControlType type)
{
	this->controlType = type;
}



/// Indica o tipo de controlo que é efectuado.
SoccerRobot::ControlType SoccerRobot::GetControlType() const
{
	return this->controlType;
}



/// Devolve a joint que controla a perna.
SliderJoint* SoccerRobot::GetLegJoint() const
{
	return this->legJoint;
}



/// Actualiza o jogador.
void SoccerRobot::Refresh()
{
	if (this->shootTimer.GetTime() >= SHOOT_TIME)
	{
		this->shootTimer.Reset();
		this->shootTimer.Stop();
	}
	
	if (this->shootTimer.IsStopped())
	{
		Recall();
	}
}



/// Devolve a perna do jogador.
Cylinder& SoccerRobot::GetLeg()
{
	return this->leg;
}



/// Devolve a posição central do objecto.
XYZ SoccerRobot::GetPosition() const
{
	return Geometry()->GetPosition();
}



/// Define a rotação do objecto.
void SoccerRobot::SetRotation(XYZ rotation)
{
	Geometry()->SetRotation(rotation);
	this->leg.Geometry()->SetRotation(rotation);

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].Geometry()->SetRotation(rotation);
	}
}




/// Define a rotação inicial do objecto.
void SoccerRobot::SetStartRotation(XYZ rotation)
{
	Geometry()->SetStartRotation(rotation);
	this->leg.Geometry()->SetStartRotation(rotation);

	for (int i = 0; i < WHEELS_COUNT; i++)
	{
		this->wheels[i].Geometry()->SetStartRotation(rotation);
	}
}
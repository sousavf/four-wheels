#include "ODEHeaders.h"
#include <windows.h>

using namespace ODE;

#pragma warning(disable: 4355)

ODEWorld * ODEWorld::currentWorld = NULL;

/// Cria um novo mundo.
ODEWorld::ODEWorld():space(*this),contacts(*this)
{
	Init(ODEVector3());
}



/// Cria um novo mundo com gravidade gravity.
ODEWorld::ODEWorld(const ODEVector3 &gravity):space(*this),contacts(*this)
{
	Init(gravity);
}



/// Cria um novo grupo com gravidade vertical específica.
ODEWorld::ODEWorld(ODEReal gravityZ):space(*this),contacts(*this)
{
	Init(ODEVector3(0, 0, gravityZ));
}



/// Define os parâmetros iniciais do mundo.
void ODEWorld::Init(const ODEVector3 &gravity)
{
	currentWorld = this;
	this->id = dWorldCreate();
	this->stepTime = 5;
	this->maxContacts = 10;
	this->setGravity(gravity);
	this->setStepIterations(20);
	this->setAutoDisable(true);
	this->setAutoDisableTime(0);
	this->setAutoDisableSteps(10);
	this->setAutoDisableLinearThreshold(0.01f);
	this->setAutoDisableAngularThreshold(0.01f);
	this->setContactSurfaceLayer(0.001f);
	this->setERP(0.8f);
	this->setCFM(0.0001f);
	this->setContactMaxCorrectingVelocity(1.0);
	this->applyDampening = true;
	this->linearDampening = 0.1f;
	this->angularDampening = 0.1f;
}



/// Destrói o mundo.
ODEWorld::~ODEWorld()
{
	dWorldDestroy(this->id);
	dCloseODE();
}



/// Define a gravidade do mundo.
void ODEWorld::setGravity(const ODEVector3 &g)
{
	ODEVector3 g2(g);

	dWorldSetGravity(this->id, (dReal)g2[0], (dReal)g2[1], (dReal)g2[2]);
}



/// Define o ERP global (Error Reducing Parameter). Valores típicos encontram-se
/// entre 0.1 a 0.8.
void ODEWorld::setERP(ODEReal erp)
{
	dWorldSetERP(this->id, erp);
}



/// Define o CFM global (Constraint Force Mixing). Valores típicos encontram-se
/// entre 10^-9 a 1.
void ODEWorld::setCFM(ODEReal cfm)
{
	dWorldSetCFM(this->id, cfm);
}



/// Define se é feito a desactivação de corpos automaticamente.
/// Corpos devem ser desactivos se estão imóveis e não estão a participar
/// na simulação, para poupar cálculos desnecessários.
void ODEWorld::setAutoDisable(bool doAutoDisable)
{
	dWorldSetAutoDisableFlag(this->id, (doAutoDisable ? 1 : 0));
}



/// Se a velocidade de um objecto for menor que linearThreshold então o corpo é desactivado.
void ODEWorld::setAutoDisableLinearThreshold(ODEReal linearThreshold)
{
	dWorldSetAutoDisableLinearThreshold(this->id, (dReal)linearThreshold);
}



/// Se a velocidade angular de um objecto for menor que angularThreshold então o corpo é desactivado.
void ODEWorld::setAutoDisableAngularThreshold(ODEReal angularThreshold)
{
	dWorldSetAutoDisableAngularThreshold(this->id, (dReal)angularThreshold);
}



/// Define o número de passos da simulação que um objecto tem de estar idle para ser desactivado.
void ODEWorld::setAutoDisableSteps(int steps)
{
	dWorldSetAutoDisableSteps(this->id, steps);
}



/// Define o tempo de simulação que um objecto tem de estar idle para ser desactivado.
void ODEWorld::setAutoDisableTime(ODEReal time)
{
	dWorldSetAutoDisableTime(this->id, time);
}



/// Define a profundidade da camada de superfície em torno de todas as geometrias.
/// Pode ajudar a resolver problemas de jittering (corpos a "tremer").
void ODEWorld::setContactSurfaceLayer(ODEReal depth)
{
	dWorldSetContactSurfaceLayer(this->id, (dReal)depth);
}



/// Define o dampening aplicado à velocidade linear. Dampening é uma força que é aplicada
/// no sentido contrário do objecto. Deve ser um valor entre 0 e 1.
void ODEWorld::setLinearDampening(ODEReal damp)
{
	this->linearDampening = damp;
}



/// Define o dampening aplicado à velocidade angular. Dampening é uma força que é aplicada
/// no sentido contrário do objecto. Deve ser um valor entre 0 e 1.
void ODEWorld::setAngularDampening(ODEReal damp)
{
	this->angularDampening = damp;
}



/// Valor em milisegundos que cada passo da simulação deve ocupar.
void ODEWorld::setStepTime(ODEReal miliseconds)
{
	this->stepTime = miliseconds;
}



/// Número máximo de pontos de contacto gerados por cada colisão.
/// Quanto mais elevado, maior a precisão e maior a lentidão. Deve ser entre 1 e 10.
void ODEWorld::setMaxContacts(int max)
{
	this->maxContacts = max;
}



/// Define o número de iterações que o método step faz a cada passo.
/// Quanto maior, maior a exactidão da simulação, mas também fica mais lento.
/// Um valor de 20 é "normal".
void ODEWorld::setStepIterations(int n)
{
	dWorldSetQuickStepNumIterations(this->id, n);
}



/// Define a função que é usada para criar os contactos.
void ODEWorld::setCreateContact(createContactDelegate ccDelegate)
{
	this->createContact = ccDelegate;
}



/// Define a velocidade máxima que os contactos podem gerar.
void ODEWorld::setContactMaxCorrectingVelocity(ODEReal max)
{
	dWorldSetContactMaxCorrectingVel(this->id, (dReal)max);
}



/// Define se aplica forças de dampening automaticamente.
void ODEWorld::setApplyDampening(bool apply)
{
	this->applyDampening = apply;
}



/// Devolve a gravidade do mundo.
const ODEVector3 ODEWorld::getGravity() const
{
	ODEVector3 gravity;
	dVector3 g;

	dWorldGetGravity(this->id, g);
	gravity = g;

	return gravity;
}



/// Devolve o ERP (Error Reducing Parameter) do mundo.
ODEReal ODEWorld::getERP() const
{
	return (ODEReal)dWorldGetERP(this->id);
}



/// Devolve o CFM (Constraint Force Mixing) do mundo.
ODEReal ODEWorld::getCFM() const
{
	return (ODEReal)dWorldGetCFM(this->id);
}



/// Indica se o mundo desactivar corpos automaticamente.
bool ODEWorld::getAutoDisable() const
{
	return (dWorldGetAutoDisableFlag(this->id) == 1);
}



/// Devolve a velocidade linear mínima que um corpo tem de ter para ser desactivado.
ODEReal ODEWorld::getAutoDisableLinearThreshold() const
{
	return (ODEReal)dWorldGetAutoDisableLinearThreshold(this->id);
}



/// Devolve a velocidade angular mínima que um corpo tem de ter para ser desactivado.
ODEReal ODEWorld::getAutoDisableAngularThreshold() const
{
	return (ODEReal)dWorldGetAutoDisableAngularThreshold(this->id);
}



/// Devolve o número de passos que um corpo tem de estar idle para ser desactivado.
int ODEWorld::getAutoDisableSteps() const
{
	return dWorldGetAutoDisableSteps(this->id);
}



/// Devolve o tempo que um corpo tem de estar idle para ser desactivado.
ODEReal ODEWorld::getAutoDisableTime() const
{
	return (ODEReal)dWorldGetAutoDisableTime(this->id);
}



/// Devolve a camada de superfície em torno de todas as geometrias.
ODEReal ODEWorld::getContactSurfaceLayer() const
{
	return (ODEReal)dWorldGetContactSurfaceLayer(this->id);
}



/// Devolve o dampening linear.
ODEReal ODEWorld::getLinearDampening() const
{
	return this->linearDampening;
}



/// Devolve o dampening angular.
ODEReal ODEWorld::getAngularDampening() const
{
	return this->angularDampening;
}



/// Devolve o tempo em milissegundos que é gasto em cada passo da simulação.
ODEReal ODEWorld::getStepTime() const
{
	return this->stepTime;
}



/// Devolve o número máximo de contactos gerados por colisão.
int ODEWorld::getMaxContacts() const
{
	return this->maxContacts;
}



/// Devolve o número de iterações que o método step faz a cada passo.
int ODEWorld::getStepIterations() const
{
	return dWorldGetQuickStepNumIterations(this->id);
}



/// Devolve a identificação do mundo.
dWorldID ODEWorld::getID() const
{
	return this->id;
}



/// Devolve a função usada para criar contactos.
ODEWorld::createContactDelegate ODEWorld::getCreateContact() const
{
	return this->createContact;
}



/// Devolve o espaço default do mundo.
const ODESpace& ODEWorld::getSpace() const
{
	return this->space;
}



/// Devolve o grupo onde são criados os contactos.
const ODEJointGroup& ODEWorld::getContactsGroup()
{
	return this->contacts;
}



/// Devolve a velocidade máxima que os contactos podem gerar.
ODEReal ODEWorld::getContactMaxCorrectingVelocity() const
{
	return (ODEReal)dWorldGetContactMaxCorrectingVel(this->id);
}



/// Indica se aplica dampening.
bool ODEWorld::getApplyDampening() const
{
	return this->applyDampening;
}



/// Efectua um passo da simulação.
void ODEWorld::step()
{
	ODEReal simStep;
	int steps;

	if (this->applyDampening)
	{
		dampening(this->space.getID());
	}
	simStep = (ODEReal)0.001 * this->stepTime;
	steps = (int) ceil(this->elapsedTime() / simStep);

	for (int i = 0; i < steps; i++)
	{
		dSpaceCollide(this->space.getID(), 0, &nearCallback);
		dWorldQuickStep(this->id, (dReal)simStep);
		this->contacts.empty();
	}
}



/// Define se vai existir colisão entre as geometrias e chama o método de colisão.
void ODEWorld::nearCallback(void *data, dGeomID geom1, dGeomID geom2)
{
	dBodyID body1, body2;

	if (dGeomIsSpace(geom1) || dGeomIsSpace(geom2)) // se há um espaço
	{
		dSpaceCollide2(geom1, geom2, data, &nearCallback); // colide os elementos de um espaço com os do outro espaço ou com a outra geometria
		return;
	}
	body1 = dGeomGetBody(geom1);
	body2 = dGeomGetBody(geom2);

	if ( (!body1 && !body2)	// se são ambos geometrias
		|| (body1 && !body2 && !dBodyIsEnabled(body1))	// body1 desactivado e colide só com geometria
		|| (body2 && !body1 && !dBodyIsEnabled(body2))	// body2 desactivado e colide só com geometria
		|| (body1 && body2 && !dBodyIsEnabled(body1) && !dBodyIsEnabled(body2))	// ambos desactivados
		|| (body1 && body2 && dAreConnectedExcluding(body1, body2, dJointTypeContact)) ) // se estão juntos por uma junta
	{
		return;
	}
	currentWorld->collide(geom1, geom2);
}



/// Colide os dois objectos, cria os pontos de contacto entre esses objectos
/// e chamando a função respectiva para criar os parâmetros desses contactos.
void ODEWorld::collide(dGeomID geom1, dGeomID geom2)
{
	ODEContact contact;
	dContact *contacts = new dContact[this->maxContacts];
	dContact dcontact;
	dJointID joint;
	int n;

	n = dCollide(geom1, geom2, this->maxContacts, &contacts[0].geom, sizeof(dContact));

	for (int i = 0; i < n; i++) 
	{
		contact.setContact(contacts[i]);
		contact.cleanSurface();
		if (this->createContact(contact, (ODEGeometry*)dGeomGetData(geom1), (ODEGeometry*)dGeomGetData(geom2)))
		{
			dcontact = contact.getContact();
			joint = dJointCreateContact(this->id, this->contacts.getID(), &dcontact);
			dJointAttach(joint, dGeomGetBody(dcontact.geom.g1), dGeomGetBody(dcontact.geom.g2));
		}
	}
	delete contacts;
}



/// Devolve o tempo que passou desde a última vez que a função foi chamada.
double ODEWorld::elapsedTime() const
{
	static double previousTime = 0; // só é inicializado uma vez, mas guarda sempre o valor (var. static de função)
	double currentTime, difference;

	currentTime = timeGetTime() * 0.001;

	if (!previousTime)
	{
		previousTime = currentTime;
	}
	difference = currentTime - previousTime;
	previousTime = currentTime;

	if (difference > 1)
	{
		difference = 1;
	}
	else if(difference < dEpsilon)
	{
		difference = dEpsilon;
	}

	return difference;
}



/// Aplica dampening a todos os objectos.
void ODEWorld::dampening(dSpaceID space)
{
	dGeomID geom;
	dBodyID body;

	for (int i = 0; i < dSpaceGetNumGeoms(space); i++)
	{
		geom = dSpaceGetGeom(space, i);

		if (dGeomIsSpace(geom))
		{
			dampening((dSpaceID)geom);
		}
		else
		{
			body = dGeomGetBody(geom);

			if (body)
			{
				const dReal* angularVelocity = dBodyGetAngularVel(body);
				const dReal* linearVelocity = dBodyGetLinearVel(body);

				dBodyAddTorque(body, -angularVelocity[0] * this->angularDampening
					, -angularVelocity[1] * this->angularDampening
					, -angularVelocity[2] * this->angularDampening);
				dBodyAddForce(body, -linearVelocity[0] * this->linearDampening
					, -linearVelocity[1] * this->linearDampening
					, -linearVelocity[2] * this->linearDampening);
			}
		}
	}
}
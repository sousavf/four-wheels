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



/// Cria um novo grupo com gravidade vertical espec�fica.
ODEWorld::ODEWorld(ODEReal gravityZ):space(*this),contacts(*this)
{
	Init(ODEVector3(0, 0, gravityZ));
}



/// Define os par�metros iniciais do mundo.
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



/// Destr�i o mundo.
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



/// Define o ERP global (Error Reducing Parameter). Valores t�picos encontram-se
/// entre 0.1 a 0.8.
void ODEWorld::setERP(ODEReal erp)
{
	dWorldSetERP(this->id, erp);
}



/// Define o CFM global (Constraint Force Mixing). Valores t�picos encontram-se
/// entre 10^-9 a 1.
void ODEWorld::setCFM(ODEReal cfm)
{
	dWorldSetCFM(this->id, cfm);
}



/// Define se � feito a desactiva��o de corpos automaticamente.
/// Corpos devem ser desactivos se est�o im�veis e n�o est�o a participar
/// na simula��o, para poupar c�lculos desnecess�rios.
void ODEWorld::setAutoDisable(bool doAutoDisable)
{
	dWorldSetAutoDisableFlag(this->id, (doAutoDisable ? 1 : 0));
}



/// Se a velocidade de um objecto for menor que linearThreshold ent�o o corpo � desactivado.
void ODEWorld::setAutoDisableLinearThreshold(ODEReal linearThreshold)
{
	dWorldSetAutoDisableLinearThreshold(this->id, (dReal)linearThreshold);
}



/// Se a velocidade angular de um objecto for menor que angularThreshold ent�o o corpo � desactivado.
void ODEWorld::setAutoDisableAngularThreshold(ODEReal angularThreshold)
{
	dWorldSetAutoDisableAngularThreshold(this->id, (dReal)angularThreshold);
}



/// Define o n�mero de passos da simula��o que um objecto tem de estar idle para ser desactivado.
void ODEWorld::setAutoDisableSteps(int steps)
{
	dWorldSetAutoDisableSteps(this->id, steps);
}



/// Define o tempo de simula��o que um objecto tem de estar idle para ser desactivado.
void ODEWorld::setAutoDisableTime(ODEReal time)
{
	dWorldSetAutoDisableTime(this->id, time);
}



/// Define a profundidade da camada de superf�cie em torno de todas as geometrias.
/// Pode ajudar a resolver problemas de jittering (corpos a "tremer").
void ODEWorld::setContactSurfaceLayer(ODEReal depth)
{
	dWorldSetContactSurfaceLayer(this->id, (dReal)depth);
}



/// Define o dampening aplicado � velocidade linear. Dampening � uma for�a que � aplicada
/// no sentido contr�rio do objecto. Deve ser um valor entre 0 e 1.
void ODEWorld::setLinearDampening(ODEReal damp)
{
	this->linearDampening = damp;
}



/// Define o dampening aplicado � velocidade angular. Dampening � uma for�a que � aplicada
/// no sentido contr�rio do objecto. Deve ser um valor entre 0 e 1.
void ODEWorld::setAngularDampening(ODEReal damp)
{
	this->angularDampening = damp;
}



/// Valor em milisegundos que cada passo da simula��o deve ocupar.
void ODEWorld::setStepTime(ODEReal miliseconds)
{
	this->stepTime = miliseconds;
}



/// N�mero m�ximo de pontos de contacto gerados por cada colis�o.
/// Quanto mais elevado, maior a precis�o e maior a lentid�o. Deve ser entre 1 e 10.
void ODEWorld::setMaxContacts(int max)
{
	this->maxContacts = max;
}



/// Define o n�mero de itera��es que o m�todo step faz a cada passo.
/// Quanto maior, maior a exactid�o da simula��o, mas tamb�m fica mais lento.
/// Um valor de 20 � "normal".
void ODEWorld::setStepIterations(int n)
{
	dWorldSetQuickStepNumIterations(this->id, n);
}



/// Define a fun��o que � usada para criar os contactos.
void ODEWorld::setCreateContact(createContactDelegate ccDelegate)
{
	this->createContact = ccDelegate;
}



/// Define a velocidade m�xima que os contactos podem gerar.
void ODEWorld::setContactMaxCorrectingVelocity(ODEReal max)
{
	dWorldSetContactMaxCorrectingVel(this->id, (dReal)max);
}



/// Define se aplica for�as de dampening automaticamente.
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



/// Devolve a velocidade linear m�nima que um corpo tem de ter para ser desactivado.
ODEReal ODEWorld::getAutoDisableLinearThreshold() const
{
	return (ODEReal)dWorldGetAutoDisableLinearThreshold(this->id);
}



/// Devolve a velocidade angular m�nima que um corpo tem de ter para ser desactivado.
ODEReal ODEWorld::getAutoDisableAngularThreshold() const
{
	return (ODEReal)dWorldGetAutoDisableAngularThreshold(this->id);
}



/// Devolve o n�mero de passos que um corpo tem de estar idle para ser desactivado.
int ODEWorld::getAutoDisableSteps() const
{
	return dWorldGetAutoDisableSteps(this->id);
}



/// Devolve o tempo que um corpo tem de estar idle para ser desactivado.
ODEReal ODEWorld::getAutoDisableTime() const
{
	return (ODEReal)dWorldGetAutoDisableTime(this->id);
}



/// Devolve a camada de superf�cie em torno de todas as geometrias.
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



/// Devolve o tempo em milissegundos que � gasto em cada passo da simula��o.
ODEReal ODEWorld::getStepTime() const
{
	return this->stepTime;
}



/// Devolve o n�mero m�ximo de contactos gerados por colis�o.
int ODEWorld::getMaxContacts() const
{
	return this->maxContacts;
}



/// Devolve o n�mero de itera��es que o m�todo step faz a cada passo.
int ODEWorld::getStepIterations() const
{
	return dWorldGetQuickStepNumIterations(this->id);
}



/// Devolve a identifica��o do mundo.
dWorldID ODEWorld::getID() const
{
	return this->id;
}



/// Devolve a fun��o usada para criar contactos.
ODEWorld::createContactDelegate ODEWorld::getCreateContact() const
{
	return this->createContact;
}



/// Devolve o espa�o default do mundo.
const ODESpace& ODEWorld::getSpace() const
{
	return this->space;
}



/// Devolve o grupo onde s�o criados os contactos.
const ODEJointGroup& ODEWorld::getContactsGroup()
{
	return this->contacts;
}



/// Devolve a velocidade m�xima que os contactos podem gerar.
ODEReal ODEWorld::getContactMaxCorrectingVelocity() const
{
	return (ODEReal)dWorldGetContactMaxCorrectingVel(this->id);
}



/// Indica se aplica dampening.
bool ODEWorld::getApplyDampening() const
{
	return this->applyDampening;
}



/// Efectua um passo da simula��o.
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



/// Define se vai existir colis�o entre as geometrias e chama o m�todo de colis�o.
void ODEWorld::nearCallback(void *data, dGeomID geom1, dGeomID geom2)
{
	dBodyID body1, body2;

	if (dGeomIsSpace(geom1) || dGeomIsSpace(geom2)) // se h� um espa�o
	{
		dSpaceCollide2(geom1, geom2, data, &nearCallback); // colide os elementos de um espa�o com os do outro espa�o ou com a outra geometria
		return;
	}
	body1 = dGeomGetBody(geom1);
	body2 = dGeomGetBody(geom2);

	if ( (!body1 && !body2)	// se s�o ambos geometrias
		|| (body1 && !body2 && !dBodyIsEnabled(body1))	// body1 desactivado e colide s� com geometria
		|| (body2 && !body1 && !dBodyIsEnabled(body2))	// body2 desactivado e colide s� com geometria
		|| (body1 && body2 && !dBodyIsEnabled(body1) && !dBodyIsEnabled(body2))	// ambos desactivados
		|| (body1 && body2 && dAreConnectedExcluding(body1, body2, dJointTypeContact)) ) // se est�o juntos por uma junta
	{
		return;
	}
	currentWorld->collide(geom1, geom2);
}



/// Colide os dois objectos, cria os pontos de contacto entre esses objectos
/// e chamando a fun��o respectiva para criar os par�metros desses contactos.
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



/// Devolve o tempo que passou desde a �ltima vez que a fun��o foi chamada.
double ODEWorld::elapsedTime() const
{
	static double previousTime = 0; // s� � inicializado uma vez, mas guarda sempre o valor (var. static de fun��o)
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
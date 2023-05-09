#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma nova defini��o de contacto.
ODEContactDefinition::ODEContactDefinition()
{
	Init(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
}



/// Cria uma nova defini��o a partir de outra.
ODEContactDefinition::ODEContactDefinition(const ODEContactDefinition &d)
{
	Init(d.mu, d.mu2, d.bouncyness, d.velocityThreshold, d.erp, d.cfm, d.velocity
		, d.velocity2, d.fds, d.fds2);
}



/// Cria uma nova defini��o de contacto com par�metros espec�ficos.
ODEContactDefinition::ODEContactDefinition(ODEReal mu, ODEReal mu2, ODEReal bouncyness
	, ODEReal velocityThreshold, ODEReal erp, ODEReal cfm, ODEReal velocity
	, ODEReal velocity2, ODEReal fds, ODEReal fds2)
{
	Init(mu, mu2, bouncyness, velocityThreshold, erp, cfm, velocity, velocity2, fds, fds2);
}



/// Inicia a defini��o.
void ODEContactDefinition::Init(ODEReal mu, ODEReal mu2, ODEReal bouncyness
	, ODEReal velocityThreshold, ODEReal erp, ODEReal cfm, ODEReal velocity
	, ODEReal velocity2, ODEReal fds, ODEReal fds2)
{
	this->mu = mu;
	this->mu2 = mu2;
	this->bouncyness = bouncyness;
	this->velocityThreshold = velocityThreshold;
	this->erp = erp;
	this->cfm = cfm;
	this->velocity = velocity;
	this->velocity2 = velocity2;
	this->fds = fds;
	this->fds2 = fds2;
}



/// Destr�i a defini��o de contacto.
ODEContactDefinition::~ODEContactDefinition()
{
}



/// Devolve a vari�vel correspondente � fric��o de colombo.
ODEReal ODEContactDefinition::getMu() const
{
	return this->mu;
}



/// Devolve a vari�vel correspondente � fric��o de colombo na direc�ao 2.
ODEReal ODEContactDefinition::getMu2() const
{
	return this->mu2;
}



/// Devolve a vari�vel correspondente ao n�vel de elasticidade. 
ODEReal ODEContactDefinition::getBouncyness() const
{
	return this->bouncyness;
}



/// Devolve a vari�vel correspondente � velocidade m�nima para se aplicar bouncyness.
ODEReal ODEContactDefinition::getVelocityThreshold() const
{
	return this->velocityThreshold;
}



/// Devolve a vari�vel correspondente ao ERP. 
ODEReal ODEContactDefinition::getERP() const
{
	return this->erp;
}



/// Devolve a vari�vel correspondente ao CFM.
ODEReal ODEContactDefinition::getCFM() const
{
	return this->cfm;
}



/// Devolve a vari�vel correspondente � velocidade do movimento independente. 
ODEReal ODEContactDefinition::getVelocity() const
{
	return this->velocity;
}



/// Devolve a vari�vel correspondente � velocidade do movimento independente na direc��o 2.
ODEReal ODEContactDefinition::getVelocity2() const
{
	return this->velocity2;
}



/// Devolve a vari�vel correspondente ao FDS.
ODEReal ODEContactDefinition::getFDS() const
{
	return this->fds;
}



/// Devolve a vari�vel correspondente ao FDS na direc��o 2.
ODEReal ODEContactDefinition::getFDS2() const
{
	return this->fds2;
}



/// Indica se usa fr ic��o de colombo.
bool ODEContactDefinition::useMu() const
{
	return (this->mu >= 0);
}



/// Indica se usa fric��o de colombo na direc��o 2. 
bool ODEContactDefinition::useMu2() const
{
	return (this->mu2 >= 0);
}



/// Indica se usa elasticidade.
bool ODEContactDefinition::useBouncyness() const
{
	return (this->bouncyness >= 0);
}



/// Indica se � necess�ria velocidade m�nima para efeito de bouncyness.
bool ODEContactDefinition::useVelocityThreshold() const
{
	return (this->velocityThreshold >= 0);
}



/// Indica se usa ERP.
bool ODEContactDefinition::useERP() const
{
	return (this->erp >= 0);
}



/// Indica se usa CFM.
bool ODEContactDefinition::useCFM() const
{
	return (this->cfm >= 0);
}



/// Indica se usa velocidade no movimento independente.
bool ODEContactDefinition::useVelocity() const
{
	return (this->velocity >= 0);
}



/// Indica se usa velocidade no movimento independente na direc��� 2.
bool ODEContactDefinition::useVelocity2() const
{
	return (this->velocity2 >= 0);
}



/// Indica se usa FDS.
bool ODEContactDefinition::useFDS() const
{
	return (this->fds >= 0);
}



/// Indica se usa FDS na direc��o 2.
bool ODEContactDefinition::useFDS2() const
{
	return (this->fds2 >= 0);
}



/// Iguala as defini��es a outras.
ODEContactDefinition& ODEContactDefinition::operator = (const ODEContactDefinition& d)
{
	Init(d.mu, d.mu2, d.bouncyness, d.velocityThreshold, d.erp, d.cfm, d.velocity
		, d.velocity2, d.fds, d.fds2);

	return *this;
}
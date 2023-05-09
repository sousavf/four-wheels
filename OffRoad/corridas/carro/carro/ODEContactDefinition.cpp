#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma nova definição de contacto.
ODEContactDefinition::ODEContactDefinition()
{
	Init(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
}



/// Cria uma nova definição a partir de outra.
ODEContactDefinition::ODEContactDefinition(const ODEContactDefinition &d)
{
	Init(d.mu, d.mu2, d.bouncyness, d.velocityThreshold, d.erp, d.cfm, d.velocity
		, d.velocity2, d.fds, d.fds2);
}



/// Cria uma nova definição de contacto com parâmetros específicos.
ODEContactDefinition::ODEContactDefinition(ODEReal mu, ODEReal mu2, ODEReal bouncyness
	, ODEReal velocityThreshold, ODEReal erp, ODEReal cfm, ODEReal velocity
	, ODEReal velocity2, ODEReal fds, ODEReal fds2)
{
	Init(mu, mu2, bouncyness, velocityThreshold, erp, cfm, velocity, velocity2, fds, fds2);
}



/// Inicia a definição.
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



/// Destrói a definição de contacto.
ODEContactDefinition::~ODEContactDefinition()
{
}



/// Devolve a variável correspondente à fricção de colombo.
ODEReal ODEContactDefinition::getMu() const
{
	return this->mu;
}



/// Devolve a variável correspondente à fricção de colombo na direcçao 2.
ODEReal ODEContactDefinition::getMu2() const
{
	return this->mu2;
}



/// Devolve a variável correspondente ao nível de elasticidade. 
ODEReal ODEContactDefinition::getBouncyness() const
{
	return this->bouncyness;
}



/// Devolve a variável correspondente à velocidade mínima para se aplicar bouncyness.
ODEReal ODEContactDefinition::getVelocityThreshold() const
{
	return this->velocityThreshold;
}



/// Devolve a variável correspondente ao ERP. 
ODEReal ODEContactDefinition::getERP() const
{
	return this->erp;
}



/// Devolve a variável correspondente ao CFM.
ODEReal ODEContactDefinition::getCFM() const
{
	return this->cfm;
}



/// Devolve a variável correspondente à velocidade do movimento independente. 
ODEReal ODEContactDefinition::getVelocity() const
{
	return this->velocity;
}



/// Devolve a variável correspondente à velocidade do movimento independente na direcção 2.
ODEReal ODEContactDefinition::getVelocity2() const
{
	return this->velocity2;
}



/// Devolve a variável correspondente ao FDS.
ODEReal ODEContactDefinition::getFDS() const
{
	return this->fds;
}



/// Devolve a variável correspondente ao FDS na direcção 2.
ODEReal ODEContactDefinition::getFDS2() const
{
	return this->fds2;
}



/// Indica se usa fr icção de colombo.
bool ODEContactDefinition::useMu() const
{
	return (this->mu >= 0);
}



/// Indica se usa fricção de colombo na direcção 2. 
bool ODEContactDefinition::useMu2() const
{
	return (this->mu2 >= 0);
}



/// Indica se usa elasticidade.
bool ODEContactDefinition::useBouncyness() const
{
	return (this->bouncyness >= 0);
}



/// Indica se é necessária velocidade mínima para efeito de bouncyness.
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



/// Indica se usa velocidade no movimento independente na direcçãõ 2.
bool ODEContactDefinition::useVelocity2() const
{
	return (this->velocity2 >= 0);
}



/// Indica se usa FDS.
bool ODEContactDefinition::useFDS() const
{
	return (this->fds >= 0);
}



/// Indica se usa FDS na direcção 2.
bool ODEContactDefinition::useFDS2() const
{
	return (this->fds2 >= 0);
}



/// Iguala as definições a outras.
ODEContactDefinition& ODEContactDefinition::operator = (const ODEContactDefinition& d)
{
	Init(d.mu, d.mu2, d.bouncyness, d.velocityThreshold, d.erp, d.cfm, d.velocity
		, d.velocity2, d.fds, d.fds2);

	return *this;
}
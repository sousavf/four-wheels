#include "WorldChromossome.h"
#include "../ode/Math.h"

		// gravity, angularDampening,	linearDampening	aerodynamic	mu				mu2
	//w.SetParams(10,	0.5,				0.5,			0.5,	(double)dInfinity, (double)dInfinity, 
		// slip1,	slip2,	soft_erp, soft_cfm)
	//	0.5,		0.5,	0.5,		0.5);
const double WorldChromossome::MAX_GRAVIDADE = 15;
const double WorldChromossome::MAX_AERODYNAMIC = 1;
const double WorldChromossome::MAX_ANGULARDAMPENING = 1;
const double WorldChromossome::MAX_LINEARDAMPENING = 1;
const double WorldChromossome::MAX_MU = (double)dInfinity;
const double WorldChromossome::MAX_MU2 = (double)dInfinity;
const double WorldChromossome::MAX_SLIP1 = 2;
const double WorldChromossome::MAX_SLIP2 = 2;
const double WorldChromossome::MAX_SOFT_ERP = 2;
const double WorldChromossome::MAX_SOFT_CFM = 2;

const double WorldChromossome::MIN_GRAVIDADE = 5;
const double WorldChromossome::MIN_AERODYNAMIC = 0;
const double WorldChromossome::MIN_ANGULARDAMPENING = 0;
const double WorldChromossome::MIN_LINEARDAMPENING = 0;
const double WorldChromossome::MIN_MU = 0;
const double WorldChromossome::MIN_MU2 = 0;
const double WorldChromossome::MIN_SLIP1 = 0;
const double WorldChromossome::MIN_SLIP2 = 0;
const double WorldChromossome::MIN_SOFT_ERP = 0;
const double WorldChromossome::MIN_SOFT_CFM = 0;

//const double WorldChromossome::MAX_GRAVIDADE = 20;
//const double WorldChromossome::MAX_AERODYNAMIC = 1;
//const double WorldChromossome::MAX_ANGULARDAMPENING = 1;
//const double WorldChromossome::MAX_LINEARDAMPENING = 1;
//const double WorldChromossome::MAX_MU = (double)dInfinity;
//const double WorldChromossome::MAX_MU2 = (double)dInfinity;
//const double WorldChromossome::MAX_SLIP1 = 5;
//const double WorldChromossome::MAX_SLIP2 = 5;
//const double WorldChromossome::MAX_SOFT_ERP = 5;
//const double WorldChromossome::MAX_SOFT_CFM = 5;

WorldChromossome::WorldChromossome()
{
	Init(Math::RandomDouble(WorldChromossome::MIN_GRAVIDADE, WorldChromossome::MAX_GRAVIDADE)
		, Math::RandomDouble(WorldChromossome::MIN_AERODYNAMIC, WorldChromossome::MAX_ANGULARDAMPENING)
		, Math::RandomDouble(WorldChromossome::MIN_ANGULARDAMPENING, WorldChromossome::MAX_LINEARDAMPENING)
		, Math::RandomDouble(WorldChromossome::MIN_LINEARDAMPENING, WorldChromossome::MAX_AERODYNAMIC)
		, Math::RandomDouble(WorldChromossome::MIN_MU, WorldChromossome::MAX_MU)
		, Math::RandomDouble(WorldChromossome::MIN_MU2, WorldChromossome::MAX_MU2)
		, Math::RandomDouble(WorldChromossome::MIN_SLIP1, WorldChromossome::MAX_SLIP1)
		, Math::RandomDouble(WorldChromossome::MIN_SLIP2, WorldChromossome::MAX_SLIP2)
		, Math::RandomDouble(WorldChromossome::MIN_SOFT_ERP, WorldChromossome::MAX_SOFT_ERP)
		, Math::RandomDouble(WorldChromossome::MIN_SOFT_CFM, WorldChromossome::MAX_SOFT_CFM));
}

WorldChromossome::WorldChromossome(WorldChromossome &chromo)
{
	Init(chromo[0], chromo[1], chromo[2], chromo[3], chromo[4], chromo[5], chromo[6], chromo[7]
		, chromo[8], chromo[9]);
	this->fitness = chromo.fitness;
}

//WorldChromossome::WorldChromossome(double gravity, double angularDampening, double linearDampening
//	, double aerodynamic, double mu, double mu2, double slip1, double slip2, double soft_erp, double soft_cfm)
//{
//	gravity = (gravity < WorldChromossome::MIN_GRAVIDADE ? WorldChromossome::MIN_GRAVIDADE : (gravity > MAX_GRAVIDADE ? MAX_GRAVIDADE : gravity));
//	angularDampening = (angularDampening < WorldChromossome::MIN_AERODYNAMIC ? WorldChromossome::MIN_AERODYNAMIC : (angularDampening > MAX_ANGULARDAMPENING ? MAX_ANGULARDAMPENING : angularDampening));
//	linearDampening = (linearDampening < WorldChromossome::MIN_ANGULARDAMPENING ? WorldChromossome::MIN_ANGULARDAMPENING : (linearDampening > MAX_LINEARDAMPENING ? MAX_LINEARDAMPENING : linearDampening));
//	aerodynamic = (aerodynamic < WorldChromossome::MIN_LINEARDAMPENING ? WorldChromossome::MIN_LINEARDAMPENING : (aerodynamic > MAX_AERODYNAMIC ? MAX_AERODYNAMIC : aerodynamic));
//	mu = (mu < WorldChromossome::MIN_MU ? WorldChromossome::MIN_MU : (mu > MAX_MU ? MAX_MU : mu));
//	mu2 = (mu2 < WorldChromossome::MIN_MU2 ? WorldChromossome::MIN_MU2 : (mu2 > MAX_MU2 ? MAX_MU2 : mu2));
//	slip1 = (slip1 < WorldChromossome::MIN_SLIP1 ? WorldChromossome::MIN_SLIP1 : (slip1 > MAX_SLIP1 ? MAX_SLIP1 : slip1));
//	slip2 = (slip2 < WorldChromossome::MIN_SLIP2 ? WorldChromossome::MIN_SLIP2 : (slip2 > MAX_SLIP2 ? MAX_SLIP2 : slip2));
//	soft_erp = (soft_erp < WorldChromossome::MIN_SOFT_ERP ? WorldChromossome::MIN_SOFT_ERP : (soft_erp > MAX_SOFT_ERP ? MAX_SOFT_ERP : soft_erp));
//	soft_cfm = (soft_cfm < WorldChromossome::MIN_SOFT_CFM ? WorldChromossome::MIN_SOFT_CFM : (soft_cfm > MAX_SOFT_CFM ? MAX_SOFT_CFM : soft_cfm));
//	Init(gravity, angularDampening, linearDampening, aerodynamic, mu, mu2, slip1, slip2, soft_erp, soft_cfm);
//}

WorldChromossome::WorldChromossome(double gravity, double angularDampening, double linearDampening
	, double aerodynamic, double mu, double mu2, double slip1, double slip2, double soft_erp, double soft_cfm)
{
	Init(gravity, angularDampening, linearDampening, aerodynamic, mu, mu2, slip1, slip2, soft_erp, soft_cfm);
}

void WorldChromossome::Init(double gravity, double angularDampening, double linearDampening, double aerodynamic
				, double mu, double mu2, double slip1, double slip2, double soft_erp, double soft_cfm)
{
	this->genes.push_back(gravity);
	this->genes.push_back(angularDampening);
	this->genes.push_back(linearDampening);
	this->genes.push_back(aerodynamic);
	this->genes.push_back(mu);
	this->genes.push_back(mu2);
	this->genes.push_back(slip1);
	this->genes.push_back(slip2);
	this->genes.push_back(soft_erp);
	this->genes.push_back(soft_cfm);
}
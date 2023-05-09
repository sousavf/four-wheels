#include "CarChromossome.h"
#include "../ode/Math.h"

		//mass,	width,	height,		length, off_mass, off_width	off_height, off_length
		//2,		2,		0.5,		5,		3,			2,		0.5,		4
		//off_x, off_y,		off_z,	wheelMass wheelRadius, wheelWidth, wheel_x, wheel_y, wheel_z, serp
		//, 0,		0,		-1.5,	0.4,		0.5,		0.3,		1,		1,			0,		0.5
		//scfm,		stop_erp, stop_cfm, cfm,	mforce,	  mforce2, fudgefactor)
		//, 0.5,		0.5,		0.5,	0.5,		20,			20,		0.5), 0);

const double CarChromossome::MAX_MASS = 3;
const double CarChromossome::MAX_WIDTH = 3;
const double CarChromossome::MAX_HEIGHT = 0.75;
const double CarChromossome::MAX_LENGTH = 7;
const double CarChromossome::MAX_OFF_MASS = 4;
const double CarChromossome::MAX_OFF_WIDTH = 3;
const double CarChromossome::MAX_OFF_HEIGHT = 0.75;
const double CarChromossome::MAX_OFF_LENGTH = 7;
const double CarChromossome::MAX_OFF_X = 0;
const double CarChromossome::MAX_OFF_Y = 0.5;
const double CarChromossome::MAX_OFF_Z = 1;
const double CarChromossome::MAX_WHEEL_MASS = 0.6;
const double CarChromossome::MAX_WHEEL_RADIUS = 0.75;
const double CarChromossome::MAX_WHEEL_WIDTH = 0.5;
const double CarChromossome::MAX_WHEEL_X = 1.25;
const double CarChromossome::MAX_WHEEL_Y = 1;
const double CarChromossome::MAX_WHEEL_Z = 0.25;
const double CarChromossome::MAX_SERP = 1;
const double CarChromossome::MAX_SCFM = 1;
const double CarChromossome::MAX_STOP_ERP = 1;
const double CarChromossome::MAX_STOP_CFM = 1;
const double CarChromossome::MAX_CFM = 1;
const double CarChromossome::MAX_M_FORCE = 20;
const double CarChromossome::MAX_M_FORCE2 = 20;
const double CarChromossome::MAX_FUDGEFACTOR = 1;
const double CarChromossome::MIN_MASS = 1;
const double CarChromossome::MIN_WIDTH = 1;
const double CarChromossome::MIN_HEIGHT = 0.25;
const double CarChromossome::MIN_LENGTH = 3;
const double CarChromossome::MIN_OFF_MASS = 1;
const double CarChromossome::MIN_OFF_WIDTH = 1;
const double CarChromossome::MIN_OFF_HEIGHT = 0.25;
const double CarChromossome::MIN_OFF_LENGTH = 3;
const double CarChromossome::MIN_OFF_X = 0;
const double CarChromossome::MIN_OFF_Y = -0.5;
const double CarChromossome::MIN_OFF_Z = -1;
const double CarChromossome::MIN_WHEEL_MASS = 0.2;
const double CarChromossome::MIN_WHEEL_RADIUS = 0.25;
const double CarChromossome::MIN_WHEEL_WIDTH = 0.1;
const double CarChromossome::MIN_WHEEL_X = 0.75;
const double CarChromossome::MIN_WHEEL_Y = 0.75;
const double CarChromossome::MIN_WHEEL_Z = -0.25;
const double CarChromossome::MIN_SERP = 0;
const double CarChromossome::MIN_SCFM = 0;
const double CarChromossome::MIN_STOP_ERP = 0;
const double CarChromossome::MIN_STOP_CFM = 0;
const double CarChromossome::MIN_CFM = 0;
const double CarChromossome::MIN_M_FORCE = 0;
const double CarChromossome::MIN_M_FORCE2 = 0;
const double CarChromossome::MIN_FUDGEFACTOR = 0;

//const double CarChromossome::MAX_MASS = 5;
//const double CarChromossome::MAX_WIDTH = 3;
//const double CarChromossome::MAX_HEIGHT = 2;
//const double CarChromossome::MAX_LENGTH = 5;
//const double CarChromossome::MAX_OFF_MASS = 5;
//const double CarChromossome::MAX_OFF_WIDTH = 3;
//const double CarChromossome::MAX_OFF_HEIGHT = 2;
//const double CarChromossome::MAX_OFF_LENGTH = 5;
//const double CarChromossome::MAX_OFF_X = 0;
//const double CarChromossome::MAX_OFF_Y = 1;
//const double CarChromossome::MAX_OFF_Z = 1.5;
//const double CarChromossome::MAX_WHEEL_MASS = 1;
//const double CarChromossome::MAX_WHEEL_RADIUS = 1.25;
//const double CarChromossome::MAX_WHEEL_WIDTH = 1.2;
//const double CarChromossome::MAX_WHEEL_X = 1.25;
//const double CarChromossome::MAX_WHEEL_Y = 1;
//const double CarChromossome::MAX_WHEEL_Z = 0.75;
//const double CarChromossome::MAX_SERP = 5;
//const double CarChromossome::MAX_SCFM = 5;
//const double CarChromossome::MAX_STOP_ERP = 5;
//const double CarChromossome::MAX_STOP_CFM = 5;
//const double CarChromossome::MAX_CFM = 5;
//const double CarChromossome::MAX_M_FORCE = 40;
//const double CarChromossome::MAX_M_FORCE2 = 40;
//const double CarChromossome::MAX_FUDGEFACTOR = 1;
//const double CarChromossome::MIN_MASS = 0;
//const double CarChromossome::MIN_WIDTH = 0;
//const double CarChromossome::MIN_HEIGHT = 0;
//const double CarChromossome::MIN_LENGTH = 0;
//const double CarChromossome::MIN_OFF_MASS = 0;
//const double CarChromossome::MIN_OFF_WIDTH = 0;
//const double CarChromossome::MIN_OFF_HEIGHT = 0;
//const double CarChromossome::MIN_OFF_LENGTH = 0;
//const double CarChromossome::MIN_OFF_X = 0;
//const double CarChromossome::MIN_OFF_Y = -1;
//const double CarChromossome::MIN_OFF_Z = -1.5;
//const double CarChromossome::MIN_WHEEL_MASS = 0;
//const double CarChromossome::MIN_WHEEL_RADIUS = 0;
//const double CarChromossome::MIN_WHEEL_WIDTH = 0;
//const double CarChromossome::MIN_WHEEL_X = 0.75;
//const double CarChromossome::MIN_WHEEL_Y = 0.5;
//const double CarChromossome::MIN_WHEEL_Z = -0.75;
//const double CarChromossome::MIN_SERP = 0;
//const double CarChromossome::MIN_SCFM = 0;
//const double CarChromossome::MIN_STOP_ERP = 0;
//const double CarChromossome::MIN_STOP_CFM = 0;
//const double CarChromossome::MIN_CFM = 0;
//const double CarChromossome::MIN_M_FORCE = 0;
//const double CarChromossome::MIN_M_FORCE2 = 0;
//const double CarChromossome::MIN_FUDGEFACTOR = 0;

CarChromossome::CarChromossome()
{
	Init(Math::RandomDouble(CarChromossome::MIN_MASS, CarChromossome::MAX_MASS)
		, Math::RandomDouble(CarChromossome::MIN_WIDTH, CarChromossome::MAX_WIDTH)
		, Math::RandomDouble(CarChromossome::MIN_HEIGHT, CarChromossome::MAX_HEIGHT)
		, Math::RandomDouble(CarChromossome::MIN_LENGTH, CarChromossome::MAX_LENGTH)
		, Math::RandomDouble(CarChromossome::MIN_OFF_MASS, CarChromossome::MAX_OFF_MASS)
		, Math::RandomDouble(CarChromossome::MIN_OFF_WIDTH, CarChromossome::MAX_OFF_WIDTH)
		, Math::RandomDouble(CarChromossome::MIN_OFF_HEIGHT, CarChromossome::MAX_OFF_HEIGHT)
		, Math::RandomDouble(CarChromossome::MIN_OFF_LENGTH, CarChromossome::MAX_OFF_LENGTH)
		, Math::RandomDouble(CarChromossome::MIN_OFF_X, CarChromossome::MAX_OFF_X)
		, Math::RandomDouble(CarChromossome::MIN_OFF_Y, CarChromossome::MAX_OFF_Y)
		, Math::RandomDouble(CarChromossome::MIN_OFF_Z, CarChromossome::MAX_OFF_Z)
		, Math::RandomDouble(CarChromossome::MIN_WHEEL_MASS, CarChromossome::MAX_WHEEL_MASS)
		, Math::RandomDouble(CarChromossome::MIN_WHEEL_RADIUS, CarChromossome::MAX_WHEEL_RADIUS)
		, Math::RandomDouble(CarChromossome::MIN_WHEEL_WIDTH, CarChromossome::MAX_WHEEL_WIDTH)
		, Math::RandomDouble(CarChromossome::MIN_WHEEL_X, CarChromossome::MAX_WHEEL_X)
		, Math::RandomDouble(CarChromossome::MIN_WHEEL_Y, CarChromossome::MAX_WHEEL_Y)
		, Math::RandomDouble(CarChromossome::MIN_WHEEL_Z, CarChromossome::MAX_WHEEL_Z)
		, Math::RandomDouble(CarChromossome::MIN_SERP, CarChromossome::MAX_SERP)
		, Math::RandomDouble(CarChromossome::MIN_SCFM, CarChromossome::MAX_SCFM)
		, Math::RandomDouble(CarChromossome::MIN_STOP_ERP, CarChromossome::MAX_STOP_ERP)
		, Math::RandomDouble(CarChromossome::MIN_STOP_CFM, CarChromossome::MAX_STOP_CFM)
		, Math::RandomDouble(CarChromossome::MIN_CFM, CarChromossome::MAX_CFM)
		, Math::RandomDouble(CarChromossome::MIN_M_FORCE, CarChromossome::MAX_M_FORCE)
		, Math::RandomDouble(CarChromossome::MIN_M_FORCE2, CarChromossome::MAX_M_FORCE2)
		, Math::RandomDouble(CarChromossome::MIN_FUDGEFACTOR, CarChromossome::MAX_FUDGEFACTOR));
}

CarChromossome::CarChromossome(CarChromossome &chromo)
{
	Init(chromo[0], chromo[1], chromo[2], chromo[3], chromo[4], chromo[5], chromo[6], chromo[7]
		, chromo[8], chromo[9], chromo[10], chromo[11], chromo[12], chromo[13], chromo[14], chromo[15]
		, chromo[16], chromo[17], chromo[18], chromo[19], chromo[20], chromo[21], chromo[22]
		, chromo[23], chromo[24]);
	this->fitness = chromo.fitness;
}

//CarChromossome::CarChromossome(double mass, double width, double height, double length, double off_mass, double off_width
//	, double off_height, double off_length, double off_x, double off_y, double off_z, double wheelMass
//	, double wheelRadius, double wheelWidth, double wheel_x, double wheel_y, double wheel_z, double serp
//	, double scfm, double stop_erp, double stop_cfm, double cfm, double mforce, double mforce2, double fudgefactor)
//{
//	mass = (mass < MIN_MASS ? MIN_MASS : (mass > MAX_MASS ? MAX_MASS : mass));
//	width = (width < MIN_WIDTH ? MIN_WIDTH : (width > MAX_WIDTH ? MAX_WIDTH : width));
//	height = (height < MIN_HEIGHT ? MIN_HEIGHT : (height > MAX_HEIGHT ? MAX_HEIGHT : height));
//	length = (length < MIN_LENGTH ? MIN_LENGTH : (length > MAX_LENGTH ? MAX_LENGTH : length));
//	off_mass = (off_mass < MIN_OFF_MASS ? MIN_OFF_MASS : (off_mass > MAX_OFF_MASS ? MAX_OFF_MASS : off_mass));
//	off_width = (off_width < MIN_OFF_WIDTH ? MIN_OFF_WIDTH : (off_width > MAX_OFF_WIDTH ? MAX_OFF_WIDTH : off_width));
//	off_height = (off_height < MIN_OFF_HEIGHT ? MIN_OFF_HEIGHT : (off_height > MAX_OFF_HEIGHT ? MAX_OFF_HEIGHT : off_height));
//	off_length = (off_length < MIN_OFF_LENGTH ? MIN_OFF_LENGTH : (off_length > MAX_OFF_LENGTH ? MAX_OFF_LENGTH : off_length));
//	off_x = (off_x < MIN_OFF_X ? MIN_OFF_X : (off_x > MAX_OFF_X ? MAX_OFF_X : off_x));
//	off_y = (off_y < MIN_OFF_Y ? MIN_OFF_Y : (off_y > MAX_OFF_Y ? MAX_OFF_Y : off_y));
//	off_z = (off_z < MIN_OFF_Z ? MIN_OFF_Z : (off_z > MAX_OFF_Z ? MAX_OFF_Z : off_z));
//	wheelMass = (wheelMass < MIN_WHEEL_MASS ? MIN_WHEEL_MASS : (wheelMass > MAX_WHEEL_MASS ? MAX_WHEEL_MASS : wheelMass));
//	wheelRadius = (wheelRadius < MIN_WHEEL_RADIUS ? MIN_WHEEL_RADIUS : (wheelRadius > MAX_WHEEL_RADIUS ? MAX_WHEEL_RADIUS : wheelRadius));
//	wheelWidth = (wheelWidth < MIN_WHEEL_WIDTH ? MIN_WHEEL_WIDTH : (wheelWidth > MAX_WHEEL_WIDTH ? MAX_WHEEL_WIDTH : wheelWidth));
//	wheel_x = (wheel_x < MIN_WHEEL_X ? MIN_WHEEL_X : (wheel_x > MAX_WHEEL_X ? MAX_WHEEL_X : wheel_x));
//	wheel_y = (wheel_y < MIN_WHEEL_Y ? MIN_WHEEL_Y : (wheel_y > MAX_WHEEL_Y ? MAX_WHEEL_Y : wheel_y));
//	wheel_z = (wheel_z < MIN_WHEEL_Z ? MIN_WHEEL_Z : (wheel_z > MAX_WHEEL_Z ? MAX_WHEEL_Z : wheel_z));
//	serp = (serp < MIN_SERP ? MIN_SERP : (serp > MAX_SERP ? MAX_SERP : serp));
//	scfm = (scfm < MIN_SCFM ? MIN_SCFM : (scfm > MAX_SCFM ? MAX_SCFM : scfm));
//	stop_erp = (stop_erp < MIN_STOP_ERP ? MIN_STOP_ERP : (stop_erp > MAX_STOP_ERP ? MAX_STOP_ERP : stop_erp));
//	stop_cfm = (stop_cfm < MIN_STOP_CFM ? MIN_STOP_CFM : (stop_cfm > MAX_STOP_CFM ? MAX_STOP_CFM : stop_cfm));
//	cfm = (cfm < MIN_CFM ? MIN_CFM : (cfm > MAX_CFM ? MAX_CFM : cfm));
//	mforce = (mforce < MIN_M_FORCE ? MIN_M_FORCE : (mforce > MAX_M_FORCE ? MAX_M_FORCE : mforce));
//	mforce2 = (mforce2 < MIN_M_FORCE2 ? MIN_M_FORCE2 : (mforce2 > MAX_M_FORCE2 ? MAX_M_FORCE2 : mforce2));
//	fudgefactor = (fudgefactor < MIN_FUDGEFACTOR ? MIN_FUDGEFACTOR : (fudgefactor > MAX_FUDGEFACTOR ? MAX_FUDGEFACTOR : fudgefactor));
//	Init(mass, width, height, length, off_mass, off_width, off_height, off_length, off_x, off_y, off_z, wheelMass
//	, wheelRadius, wheelWidth, wheel_x, wheel_y, wheel_z, serp, scfm, stop_erp, stop_cfm, cfm, mforce, mforce2, fudgefactor);
//}

CarChromossome::CarChromossome(double mass, double width, double height, double length, double off_mass, double off_width
	, double off_height, double off_length, double off_x, double off_y, double off_z, double wheelMass
	, double wheelRadius, double wheelWidth, double wheel_x, double wheel_y, double wheel_z, double serp
	, double scfm, double stop_erp, double stop_cfm, double cfm, double mforce, double mforce2, double fudgefactor)
{
	Init(mass, width, height, length, off_mass, off_width, off_height, off_length, off_x, off_y, off_z, wheelMass
	, wheelRadius, wheelWidth, wheel_x, wheel_y, wheel_z, serp, scfm, stop_erp, stop_cfm, cfm, mforce, mforce2, fudgefactor);
}

void CarChromossome::Init(double mass, double width, double height, double length, double off_mass, double off_width
	, double off_height, double off_length, double off_x, double off_y, double off_z, double wheelMass
	, double wheelRadius, double wheelWidth, double wheel_x, double wheel_y, double wheel_z, double serp
	, double scfm, double stop_erp, double stop_cfm, double cfm, double mforce, double mforce2, double fudgefactor)
{
	this->genes.push_back(mass);
	this->genes.push_back(width);
	this->genes.push_back(height);
	this->genes.push_back(length);
	this->genes.push_back(off_mass);
	this->genes.push_back(off_width);
	this->genes.push_back(off_height);
	this->genes.push_back(off_length);
	this->genes.push_back(off_x);
	this->genes.push_back(off_y);
	this->genes.push_back(off_z);
	this->genes.push_back(wheelMass);
	this->genes.push_back(wheelRadius);
	this->genes.push_back(wheelWidth);
	this->genes.push_back(wheel_x);
	this->genes.push_back(wheel_y);
	this->genes.push_back(wheel_z);
	this->genes.push_back(serp);
	this->genes.push_back(scfm);
	this->genes.push_back(stop_erp);
	this->genes.push_back(stop_cfm);
	this->genes.push_back(cfm);
	this->genes.push_back(mforce);
	this->genes.push_back(mforce2);
	this->genes.push_back(fudgefactor);
}

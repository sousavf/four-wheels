#ifndef RACE_H
#define RACE_H

#include "ODEHeaders.h"
#include "LapCounter.h"
#include "Pista.h"
#include "Carro/veiculo.h"
#include "Carro/objecto.h"
#include "ObstacleType.h"
#include "cenario.h"

#include <vector>

using namespace std;
using namespace ODE;

class Race
{
public:
	Race(ODESimulation &world, const char* trackFilename
		, vector< ODECar* > &carsODE, vector< veiculo* > &carsGL
		, vector< ObstacleType > obstacleTypes, int laps);
	Race(ODESimulation &world, const char* trackFilename
		, vector< ODECar* > &carsODE, vector< veiculo* > &carsGL
		, int nObstacles, ObstacleType obstacleType, int laps);
	Race(ODESimulation &world, const char* trackFilename
		, ODECar *carODE, veiculo *carGL, vector< ObstacleType > obstacleTypes, int laps);
	Race(ODESimulation &world, const char* trackFilename
		, ODECar *carODE, veiculo *carGL, int nObstacles, ObstacleType obstacleType, int laps);
	~Race();

	bool start();
	bool hasEnded() const;
	void draw();
	bool drawCar(int index);
	bool drawObstacle(int index);
	vector< LapCounter > & getCounters();
	const LapCounter & getCounter(int index) const;
	const vector< ODECar* > & getCarsODE() const;
	const ODECar & getCarODE(int index) const;
	ODECar & getCarODE(int index);
	veiculo & getCarGL(int index);
	ODEWheel* getWheel(ODEGeometry* geom1, ODEGeometry* geom2);
	int count() const;
	int getLaps() const;
	const ODETrack & getTrackODE() const;

protected:
	static Race *handler;
	static bool createContactHandler(ODEContact& contact, ODEGeometry* geom1
		, ODEGeometry* geom2);

	vector< ODECar* > carsODE;
	vector< veiculo* > carsGL;
	vector< ODESimpleObject* > obstaclesODE;
	vector< objecto* > obstaclesGL;
	vector< LapCounter > counters;
	Pista trackGL;
	ODETrack trackODE;
	ODESimulation *world;
	int laps;
	bool ended;

	cenario * cenary;

	int carTouchedStartLine(ODEGeometry* geom1, ODEGeometry* geom2);
	bool createContact(ODEContact& contact, ODEGeometry* geom1
		, ODEGeometry* geom2);
	void Init(ODESimulation &world, vector< ObstacleType > obstacleTypes, int laps);
	ODESimpleObject * newObstacleODE(ObstacleType type, ODEVector3 &pos);
	objecto * newObstacleGL(ObstacleType type);
};

#endif
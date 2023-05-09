#include "ODETestTrack.h"
#include <drawstuff/drawstuff.h>
#include <vector>
#include <string>

using namespace ODE;
using namespace std;

/// Cria o teste.
ODETestTrack::ODETestTrack():ODETestCar()
{
	ODETrackSegmentDefinition::Surface ground, sidelines;
	vector< vector< ODETrackSegmentDefinition > > segments;

	string name;

	if (ODETrack::Load("Teste.trk", name, ground, sidelines, segments))
	{
		if (ODETrackValidator::isValid(segments))
		{
			track = new ODETrack(world, name, ground, sidelines, segments);
			//track->getStart(0, startPosition, startRotation);
		}
		else
		{
			track = NULL;
		}
	}
	else
	{
		track = NULL;
	}
}



/// Destrói o teste.
ODETestTrack::~ODETestTrack()
{
	this->track->~ODETrack();
}



/// Desenha.
void ODETestTrack::draw()
{
	dVector3 s;

	ODETestCar::draw();

	for (int i = 0; i < this->track->getLength(); i++)
	{
		for (int j = 0; j < this->track->getWidth(); j++)
		{
			if (this->track->getSegment(j, i).getType() != ODETrackSegmentDefinition::Empty)
			{
				for (int k = 0; k < (int)this->track->getSegment(j, i).sidesCount(); k++)
				{
					dsSetColorAlpha(1, 1, 1, 0.5f);
					dGeomBoxGetLengths(this->track->getSegment(j, i).getSide(k).getID(), s);
					dsDrawBox(dGeomGetPosition(this->track->getSegment(j, i).getSide(k).getID())
						, dGeomGetRotation(this->track->getSegment(j, i).getSide(k).getID()), s);

					dsSetColorAlpha(0.25f, 0.25f, 0.25f, 1.0f);
					dGeomBoxGetLengths(this->track->getSegment(j, i).getGround(k + 1).getID(), s);
					dsDrawBox(dGeomGetPosition(this->track->getSegment(j, i).getGround(k + 1).getID())
							, dGeomGetRotation(this->track->getSegment(j, i).getGround(k + 1).getID()), s);
				}
				dsSetColorAlpha(1, 1, 1, 1.0f);
				dGeomBoxGetLengths(this->track->getSegment(j, i).getGround(0).getID(), s);
				dsDrawBox(dGeomGetPosition(this->track->getSegment(j, i).getGround(0).getID())
						, dGeomGetRotation(this->track->getSegment(j, i).getGround(0).getID()), s);
			}
		}
	}
	dsSetColorAlpha(0, 1, 0, 1.0f);
	dGeomBoxGetLengths(this->track->getStartLine().getID(), s);
	dsDrawBox(dGeomGetPosition(this->track->getStartLine().getID())
		, dGeomGetRotation(this->track->getStartLine().getID()), s);
}



/// Inicia o teste.
void ODETestTrack::start()
{
	this->world.setStepTime(2.0f);
	this->track->setStart(0, 1, this->car);
	this->world.addObject(&this->car);
	this->ground.~ODEPlaneGeometry();
	this->counter.start();
}



/// Trata das colisões.
bool ODETestTrack::createContact(ODEContact& contact, ODEGeometry* geom1, ODEGeometry* geom2)
{
	if (this->track->startLineIsAnyOf(geom1, geom2))
	{
		if (this->track->touchedStartLine(this->car, geom1, geom2))
		{
			this->counter.incLaps();
			printf("%d\t%d\n", this->counter.getLaps(), this->counter.getLastTime());
		}

		return false;
	}
	contact.setFrictionMode(ODEContact::BothFrictionPyramids);
	contact.setParameters(geom1->getContactDefinition(), geom2->getContactDefinition());








	ODEWheel::Position p;
	bool found = false;

	if (geom1->hasBody())
	{
		for (int i = 0; i < 4; i++)
		{
			if (geom1->getID() == this->car.getWheelAt((ODEWheel::Position)i).getGeomID())
			{
				p = (ODEWheel::Position)i;
				found = true;
				break;
			}
		}
	}
	else if (geom2->hasBody())
	{
		for (int i = 0; i < 4; i++)
		{
			if (geom1->getID() == this->car.getWheelAt((ODEWheel::Position)i).getGeomID())
			{
				p = (ODEWheel::Position)i;
				found = true;
				break;
			}
		}
	}

	if (found)
	{
		this->car.getWheelAt(p).applyPerpendicularFDS(contact);
	}








	return true;
}
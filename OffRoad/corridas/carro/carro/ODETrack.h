#ifndef ODETRACK_H
#define ODETRACK_H

#include "ODERequirements.h"
#include <vector>
#include <string>

using namespace std;

namespace ODE
{
	/// Representa uma pista.
	class ODETrack
	{
	public:
		ODETrack(ODEWorld &world, const char* filename);
		ODETrack(ODEWorld &world, const string& name
			, ODETrackSegmentDefinition::Surface groundSurface
			, ODETrackSegmentDefinition::Surface sidelinesSurface
			, vector< vector< ODETrackSegmentDefinition > >& segDefinitions);
		~ODETrack();

		bool touchedStartLine(ODECar &car, const ODEGeometry &geom1, const ODEGeometry &geom2);
		bool touchedStartLine(ODECar &car, const ODEGeometry *geom1, const ODEGeometry *geom2);
		bool startLineIsAnyOf(const ODEGeometry &geom1, const ODEGeometry &geom2);
		bool startLineIsAnyOf(const ODEGeometry *geom1, const ODEGeometry *geom2);

		void setStart(int carPosition, int cars, ODECar &car) const;
		const ODEBoxGeometry& getStartLine() const;
		ODETrackSegment& getStartSegment();
		int getWidth() const;
		int getLength() const;
		const ODETrackSegment& getSegment(int x, int y) const;
		const string& getName() const;
		const ODESpace& getSpace() const;
		bool isValid() const;
		ODETrackSegmentDefinition::Surface getGroundSurface() const;
		ODETrackSegmentDefinition::Surface getSidelinesSurface() const;

		static bool Load(const char* filename, string &trackName
			, ODETrackSegmentDefinition::Surface &groundSurface
			, ODETrackSegmentDefinition::Surface &sidelinesSurface
			, vector< vector< ODETrackSegmentDefinition > >& segDefinitions);
		static void Save(const char* filename, const string &trackName
			, ODETrackSegmentDefinition::Surface groundSurface
			, ODETrackSegmentDefinition::Surface sidelinesSurface
			, const vector< vector< ODETrackSegmentDefinition > >& segDefinitions);

	protected:
		vector< vector< ODETrackSegment* > > segments;
		int startX;
		int startY;
		string name;
		ODESpace space;
		ODEWorld *world;
		ODEBoxGeometry *startLine[2];
		bool startLineTouched[2];
		ODETrackSegment *startSegment;
		ODETrackSegmentDefinition::Surface groundSurface;
		ODETrackSegmentDefinition::Surface sidelinesSurface;

		void Init(ODEWorld &world, const string& name
			, ODETrackSegmentDefinition::Surface groundSurface
			, ODETrackSegmentDefinition::Surface sidelinesSurface
			, vector< vector< ODETrackSegmentDefinition > >& segDefinitions);
		static bool areCoincident(const ODETrackSegment &startSegment, ODECar &car);
	};
}

#endif
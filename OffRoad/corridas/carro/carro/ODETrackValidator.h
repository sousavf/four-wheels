#ifndef ODETRACKVALIDATOR_H
#define ODETRACKVALIDATOR_H

#include "ODERequirements.h"

using namespace std;

namespace ODE
{
	/// Contém métodos estáticos para validar conjuntos de segmentos.
	class ODETrackValidator
	{
	public:
		static bool isValid(const vector< vector< ODETrackSegmentDefinition > >& segDefinitions);
		static bool isValid(const ODETrackSegmentDefinition &seg, int x, int y
			, const vector< vector< ODETrackSegmentDefinition > >& segDefinitions);
		static bool openRight(ODETrackSegmentDefinition::Block b);
		static bool openLeft(ODETrackSegmentDefinition::Block b);
		static bool openFront(ODETrackSegmentDefinition::Block b);
		static bool openBack(ODETrackSegmentDefinition::Block b);
		static bool closeRight(ODETrackSegmentDefinition::Block b);
		static bool closeLeft(ODETrackSegmentDefinition::Block b);
		static bool closeFront(ODETrackSegmentDefinition::Block b);
		static bool closeBack(ODETrackSegmentDefinition::Block b);
		static bool straight(ODETrackSegmentDefinition::Block b);
		static bool straightSide(ODETrackSegmentDefinition::Block b);
		static bool curve(ODETrackSegmentDefinition::Block b);
		static bool empty(ODETrackSegmentDefinition::Block b);
		static bool start(ODETrackSegmentDefinition::Block b);
		static bool hasStart(const vector< vector< ODETrackSegmentDefinition > >& segDefinitions);
		static bool hasStart(const vector< vector< ODETrackSegmentDefinition > >& segDefinitions
			, int x, int y);
	};
}

#endif
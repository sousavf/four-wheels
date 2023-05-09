#ifndef ODETRACKSEGMENT_H
#define ODETRACKSEGMENT_H

#include "ODERequirements.h"
#include <vector>

using namespace std;

namespace ODE
{
	/// Representa um segmento de pista.
	class ODETrackSegment
	{
	public:
		ODETrackSegment(ODEWorld &world, const ODESpace &space
			, ODETrackSegmentDefinition &def, const ODEVector3 &position);
		~ODETrackSegment();

		void setPosition(const ODEVector3 &p);
		
		const ODEVector3& getPosition() const;
		const ODEVector3& getSize() const;
		ODEReal getBorderSize() const;
		const ODEBoxGeometry& getGround(int index) const;
		int sidesCount() const;
		const ODEBoxGeometry& getSide(int index) const;
		const ODETrackSegmentDefinition::Block getType() const;
		ODETrackSegmentDefinition::Surface getGroundSurface() const;
		ODETrackSegmentDefinition::Surface getSidelinesSurface() const;
		ODETrackSegmentDefinition getDefinition() const;

	protected:
		vector< ODEBoxGeometry* > sides;
		vector< ODEBoxGeometry* > ground;
		ODETrackSegmentDefinition definition;
		ODEVector3 position;

		ODEBoxGeometry* newSide(ODEWorld &world, const ODESpace &space
			, ODETrackSegmentDefinition::Side side);
		ODEBoxGeometry* newGround(ODEWorld &world, const ODESpace &space
			, ODETrackSegmentDefinition::Side side);
		const ODEVector3 sidelinePosition(ODETrackSegmentDefinition::Side side);
		const ODEVector3 sidelineSize(ODETrackSegmentDefinition::Side side);
		const ODEVector3 groundPosition() const;
		const ODEVector3 groundSize();
		const ODEVector3 sidePosition(ODETrackSegmentDefinition::Side side);
		const ODEVector3 rampPosition(const ODEVector3 &pos, int r) const;
		ODEReal rampAngle(int r) const;
		const ODEQuaternion rampQuaternion(int r) const;
	};
}

#endif
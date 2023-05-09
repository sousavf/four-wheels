#ifndef Car_h
#define Car_h

#include "Box.h"
#include "Wheel.h"
#include "Hinge2Joint.h"
#include "Chassis.h"
#include "..\genetic_algorithms\CarChromossome.h"

class Car : public Chassis
{
	public:
		const static int WHEELS_COUNT = 4;
		const static int FRONT_LEFT = 0;
		const static int FRONT_RIGHT = 1;
		const static int REAR_LEFT = 2;
		const static int REAR_RIGHT = 3;

		Car(World &world, double mass, double width, double height, double length
					, double wheelMass, double wheelRadius, double wheelWidth);
		Car(World &world, double mass, double width, double height, double length
					, double wheelMass, double wheelRadius, double wheelWidth, XYZ position);
		Car(World &world, double mass, double width, double height, double length
			, double wheelMass, double wheelRadius, double wheelWidth, XYZ wheelPosOff
			, double offMass, double offWidth, double offHeight, double offLength, XYZ offPos
			, double S_ERP, double S_CFM, double Stop_ERP, double Stop_CFM, double CFM, double M_Force
			, double M_Force2, double FudgeFactor, XYZ position);
		Car(World &world, CarChromossome &c, double y);
		~Car();

        Wheel* GetWheels();
		Hinge2Joint** GetJoints();

		void Steer(double value);
		void Accelerate(double value);
		void Reset();
		bool Touched(::Geometry& geometry) const;
		bool Touched(Object& object) const;
		bool WasTouched() const;
		Space* GetSpace() const;
		double WheelVelocity() const;
		double WheelDirection() const;
		double AverageWheelVelocity() const;
		double AverageWheelDirection() const;
		double Velocity();
		void SetCategory(long bits);
		void SetCollide(long bits);
		void SetTransparency(Geometry::Transparency value);
		void SetEnable(bool value);
		void SetPosition(XYZ position);

	protected:
		static const double COMOFFSET;			// posição do centro de massa relativo ao chassis

		Wheel* wheels;
		Hinge2Joint** joints;
		Box* chassisOffset;
		Space* space;
		double averageSpeed;
		double averageDirection;

		void Init(World &world, double mass, double width, double height, double length
						, double wheelMass, double wheelRadius, double wheelWidth, XYZ position);

		void Init(World &world, double mass, double width, double height, double length
			, double wheelMass, double wheelRadius, double wheelWidth, XYZ wheelPosOff
			, double offMass, double offWidth, double offHeight, double offLength, XYZ offPos
			, double S_ERP, double S_CFM, double Stop_ERP, double Stop_CFM, double CFM, double M_Force
			, double M_Force2, double FudgeFactor, XYZ position);
};

#endif
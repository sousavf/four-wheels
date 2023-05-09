#ifndef SoccerRobot_h
#define SoccerRobot_h

#include "Object.h"
#include "Cylinder.h"
#include "Box.h"
#include "Wheel.h"
#include "Hinge2Joint.h"
#include "SliderJoint.h"
#include "Space.h"
#include "Timer.h"

class SoccerRobot : public Object
{
	public:
		enum ControlType
		{
			JointVelocity,
			JointTorque
		};

		const static int WHEELS_COUNT = 4;
		const static double SHOOT_TIME;	// tempo até fazer o recall da perna do jogador.

		SoccerRobot(World &world);
		SoccerRobot(World &world, XYZ position);
		SoccerRobot(World &world, double bodyMass, double bodyRadius, double bodyHeight);
		SoccerRobot(World &world, double bodyMass, double bodyRadius, double bodyHeight, XYZ position);
		SoccerRobot(World &world, double bodyMass, double bodyRadius, double bodyHeight,
				double wheelMass, double wheelRadius, double wheelWidth);
		SoccerRobot(World &world, double bodyMass, double bodyRadius, double bodyHeight,
				double wheelMass, double wheelRadius, double wheelWidth, XYZ position);
		SoccerRobot(World &world, double bodyMass, double bodyRadius, double bodyHeight
				, double legMass, double legRadius, double legLength
				, double wheelMass, double wheelRadius, double wheelWidth);
		SoccerRobot(World &world, double bodyMass, double bodyRadius, double bodyHeight
				, double legMass, double legRadius, double legLength
				, double wheelMass, double wheelRadius, double wheelWidth, XYZ position);
		~SoccerRobot();

		void AccelerateLeft(double value);
		void AccelerateRight(double value);
		void Shoot();
		void Recall();
		void Stop();
		void Refresh();
		void Reset();
		bool Touched(::Geometry& geometry) const;
		bool Touched(Object& object) const;
		bool WasTouched() const;
		double LeftWheelsVelocity() const;
		double RightWheelsVelocity() const;

        Wheel* GetWheels();
		Hinge2Joint** GetJoints();
		SliderJoint* GetLegJoint() const;
		Space* GetSpace() const;
		ControlType GetControlType() const;
		Cylinder& GetLeg();
		double GetShootingStrength() const;
		double GetShootingRecall() const;
		XYZ GetPosition() const;
		
		void SetCategory(long bits);
		void SetCollide(long bits);
		void SetTransparency(Geometry::Transparency value);
		void SetEnable(bool value);
		void SetPosition(XYZ position);
		void SetRotation(XYZ rotation);
		void SetStartPosition(XYZ position);
		void SetStartRotation(XYZ rotation);
		void SetControlType(ControlType type);
		void SetShootingStrength(double value);
		void SetShootingRecall(double value);

	protected:
		Wheel* wheels;
		Hinge2Joint** joints;
		Space* space;
		Cylinder leg;
		SliderJoint* legJoint;
		double shootingStrength;
		double shootingRecall;
		ControlType controlType;
		Timer shootTimer;

		void Init(World &world, double bodyMass, double bodyRadius, double bodyHeight
				, double legMass, double legRadius, double legLength
				, double wheelMass, double wheelRadius, double wheelWidth, XYZ position);
};

#endif

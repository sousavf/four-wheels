#include "Joint.h"

/// Cria uma nova joint.
Joint::Joint()
{
	this->joint = NULL;
}



/// Destrói a joint.
Joint::~Joint()
{
	dJointDestroy(this->joint);
}



/// Devolve a identificação da joint.
dJointID Joint::ID() const
{
	return this->joint;
}



/// Junta obj1 com obj2 através da joint.
void Joint::Attach(Object &obj1, Object &obj2)
{
	if (this->joint != NULL)
	{
        dJointAttach(this->joint, obj1.ID(), obj2.ID());
	}
}



/// Junta obj1 com obj2 através da joint.
void Joint::Attach(dBodyID body1, dBodyID body2)
{
	if (this->joint != NULL)
	{
        dJointAttach(this->joint, body1, body2);
	}
}



/// Devolve o valor inteiro correcto para ser usado pelo ODE correspondente a param.
int Joint::GetODEParameter(MotorParameter param)
{
	switch(param)
	{
		case LowStop:
			return dParamLoStop;

		case HighStop:
			return dParamHiStop;

		case Velocity:
			return dParamVel;

		case Velocity2:
			return dParamVel2;

		case MaximumForce:
			return dParamFMax;
		
		case MaximumForce2:
			return dParamFMax2;

		case FudgeFactor:
			return dParamFudgeFactor;

		case Bouncyness:
			return dParamBounce;

		case CFM:
			return dParamCFM;

		case StopERP:
			return dParamStopERP;

		case StopCFM:
			return dParamStopCFM;

		case SuspensionERP:
			return dParamSuspensionERP;

		case SuspensionCFM:
			return dParamSuspensionCFM;
	}

	return 0;
}



/// Desliga a joint dos objectos a que possa estar junta.
void Joint::Detach()
{
	if (this->joint != NULL)
	{
        dJointAttach(this->joint, 0, 0);
	}
}
#ifndef ODEContact_H
#define ODEContact_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa um ponto de contacto. Quando 2 corpos colidem são criados
	/// pontos de contacto com atrito, elasticidade, etc. que depois são resolvidos.
	class ODEContact
	{
	public:
		enum Flag
		{
			AdditionalFriction = dContactMu2,
			FrictionDirection1 = dContactFDir1,
			Bounce = dContactBounce,
			SoftERP = dContactSoftERP,
			SoftCFM = dContactSoftCFM,
			Motion1 = dContactMotion1,
			Motion2 = dContactMotion2,
			Slip1 = dContactSlip1,
			Slip2 = dContactSlip2,
			FrictionPyramid1 = dContactApprox1_1,
			FrictionPyramid2 = dContactApprox1_2,
			BothFrictionPyramids = dContactApprox1
		};

		ODEContact();
		ODEContact(dContact contact);
		~ODEContact();

		void cleanSurface();

		void setFrictionDirection1(const ODEVector3 &v);
		void setCoulombFriction(ODEReal mu, ODEReal mu2 = -1.0);
		void setBouncyness(ODEReal bouncyness, ODEReal velocityThreshold = -1.0);
		void setSoftness(ODEReal erp, ODEReal cfm);
		void setIndependentMotion(ODEReal velocity, ODEReal velocity2 = -1.0);
		void setForceDependentSlip(ODEReal fds, ODEReal fds2 = -1.0);
		void setForceDependentSlip2(ODEReal fds2);
		void setFrictionMode(Flag flag);
		void setContact(dContact contact);
		void setParameters(const ODEContactDefinition &def1
			, const ODEContactDefinition &def2);

		const ODEVector3 getPosition() const;
		const ODEVector3 getNormal() const;
		ODEReal getDepth() const;
		dContact getContact() const;

	protected:
		dContact contact;

		static ODEReal getMin(ODEReal r, ODEReal r2);
	};
}

#endif
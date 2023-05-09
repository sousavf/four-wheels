#ifndef ODECONTACTDEFINITION_H
#define ODECONTACTDEFINITION_H

#include "ODERequirements.h"

namespace ODE
{
	/// Representa as definições de um ponto de contacto.
	/// É usado pelas geometrias para ser mais fácil definir os parâmetros de contacto.
	class ODEContactDefinition
	{
	public:
		ODEContactDefinition();
		ODEContactDefinition(const ODEContactDefinition &definition);
		ODEContactDefinition(ODEReal mu, ODEReal mu2, ODEReal bouncyness, ODEReal velocityThreshold
			, ODEReal erp, ODEReal cfm, ODEReal velocity, ODEReal velocity2, ODEReal fds, ODEReal fds2);
		~ODEContactDefinition();

		ODEReal getMu() const;
		ODEReal getMu2() const;
		ODEReal getBouncyness() const;
		ODEReal getVelocityThreshold() const;
		ODEReal getERP() const;
		ODEReal getCFM() const;
		ODEReal getVelocity() const;
		ODEReal getVelocity2() const;
		ODEReal getFDS() const;
		ODEReal getFDS2() const;

		bool useMu() const;
		bool useMu2() const;
		bool useBouncyness() const;
		bool useVelocityThreshold() const;
		bool useERP() const;
		bool useCFM() const;
		bool useVelocity() const;
		bool useVelocity2() const;
		bool useFDS() const;
		bool useFDS2() const;

		ODEContactDefinition& operator = (const ODEContactDefinition& v);

	protected:
		ODEReal mu;
		ODEReal mu2;
		ODEReal bouncyness;
		ODEReal velocityThreshold;
		ODEReal erp;
		ODEReal cfm;
		ODEReal velocity;
		ODEReal velocity2;
		ODEReal fds;
		ODEReal fds2;

		void Init(ODEReal mu, ODEReal mu2, ODEReal bouncyness, ODEReal velocityThreshold
			, ODEReal erp, ODEReal cfm, ODEReal velocity, ODEReal velocity2, ODEReal fds, ODEReal fds2);
	};
}

#endif
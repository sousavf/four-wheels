#ifndef ODESIMULATION_H
#define ODESIMULATION_H

#include "ODERequirements.h"
#include <vector>

using namespace std;

namespace ODE
{
	/// Representa uma simulação. Para ser mais fácil controlar uma
	/// simulação, fornece métodos que nos permitem guardar um conjunto
	/// de objectos com posições/rotações iniciais e podemos facilmente
	/// fazer um reset a um objecto ou a todos.
	class ODESimulation : public ODEWorld
	{
	public:
		ODESimulation();
		ODESimulation(ODEReal gravityZ);
		~ODESimulation();

		void addObject(ODEObject *object);
		void addObject(ODEObject *object, const ODEVector3 &initialPosition);
		void addObject(ODEObject *object, const ODEVector3 &initialPosition
			, const ODEQuaternion &initialRotation);
		bool removeObject(ODEObject *object);
		bool removeObject(int index);
		ODEObject* getObject(int index) const;
		void reset(ODEObject *object);
		void reset(int index);
		void reset();
		int objectsCount() const;
		int indexOf(ODEObject &object) const;
		bool isValidIndex(int index) const;

	protected:
		vector< ODEObject* > objects;
		vector< ODEVector3 > initialPositions;
		vector< ODEQuaternion > initialRotations;

		void reset(ODEObject *object, int index);
	};
}

#endif
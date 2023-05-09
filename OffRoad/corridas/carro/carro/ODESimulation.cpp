#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma nova simula��o com um mundo sem gravidade.
ODESimulation::ODESimulation()
{
}



/// Cria uma nova simula��o com um mundo com gravidade gravityZ.
ODESimulation::ODESimulation(ODEReal gravityZ):ODEWorld(gravityZ)
{
}



/// Destr�i a simula��o.
ODESimulation::~ODESimulation()
{
	while (!this->objects.empty())
	{
		removeObject(0);
	}
}



/// Adiciona um objecto � simula��o e estabelece a posi��o e rota��o em que est� como a inicial.
void ODESimulation::addObject(ODEObject *object)
{
	addObject(object, object->getPosition(), object->getQuaternion());
}



/// Adiciona um objecto � simula��o e estabelece a rota��o em que est� como a inicial.
void ODESimulation::addObject(ODEObject *object, const ODEVector3 &initialPosition)
{
	addObject(object, initialPosition, object->getQuaternion());
}



/// Adiciona um objecto � simula��o, definindo a sua posi��o e rota��o inicial.
void ODESimulation::addObject(ODEObject *object, const ODEVector3 &initialPosition
	, const ODEQuaternion &initialRotation)
{
	this->objects.push_back(object);
	this->initialPositions.push_back(initialPosition);
	this->initialRotations.push_back(initialRotation);
	object->setPosition(initialPosition);
	object->setQuaternion(initialRotation);
}



/// Retira o objecto da simula��o.
bool ODESimulation::removeObject(ODEObject *object)
{
	return removeObject(indexOf(*object));
}



/// Retira o objecto da simula��o.
bool ODESimulation::removeObject(int index)
{
	if (!isValidIndex(index))
	{
		return false;
	}
	this->objects[index]->~ODEObject();
	this->objects.erase(this->objects.begin() + index);

	return true;
}



/// Devolve o objecto correspondente a index ou NULL se n�o existir.
ODEObject* ODESimulation::getObject(int index) const
{
	if (!isValidIndex(index))
	{
		return NULL;
	}

	return this->objects[index];
}




/// Faz um reset ao objecto , retirando todas as for�as
/// e pondo-o na sua posi��o e rota��o inicial 
void ODESimulation::reset(ODEObject *object)
{
	reset(object, indexOf(*object));
}



/// Faz um reset ao objecto correspondente a index,
/// retirando todas as for�as e pondo-o na sua posi��o e rota��o inicial.
void ODESimulation::reset(int index)
{
	reset(getObject(index), index);
}



/// Faz um reset � simula��o, retirando todas as for�as
/// e pondo os objectos nas suas posi��es e rota��es iniciais.
void ODESimulation::reset()
{
	for (int i = 0; i < objectsCount(); i++)
	{
		reset(this->objects[i], i);
	}
}



/// Faz o reset ao objecto object que tem de corresponder a index.
void ODESimulation::reset(ODEObject *object, int index)
{
	if (isValidIndex(index) && (this->objects[index] == object))
	{
		object->setForce(ODEVector3());
		object->setTorque(ODEVector3());
		object->setAngularVelocity(ODEVector3());
		object->setLinearVelocity(ODEVector3());
		object->setPosition(this->initialPositions[index]);
		object->setQuaternion(this->initialRotations[index]);
	}
}



/// Devolve o n�mero de objectos na simula��o.
int ODESimulation::objectsCount() const
{
	return (int)this->objects.size();
}



/// Devolve o �ndice do objecto object.
int ODESimulation::indexOf(ODEObject &object) const
{
	for (int i = 0; i < objectsCount(); i++)
	{
		if (this->objects[i] == &object)
		{
			return i;
		}
	}

	return -1;
}



/// Indica se o �ndice � v�lido.
bool ODESimulation::isValidIndex(int index) const
{
	return (index >= 0 && index < objectsCount());
}
#include "ODEHeaders.h"

using namespace ODE;

/// Cria uma nova simulação com um mundo sem gravidade.
ODESimulation::ODESimulation()
{
}



/// Cria uma nova simulação com um mundo com gravidade gravityZ.
ODESimulation::ODESimulation(ODEReal gravityZ):ODEWorld(gravityZ)
{
}



/// Destrói a simulação.
ODESimulation::~ODESimulation()
{
	while (!this->objects.empty())
	{
		removeObject(0);
	}
}



/// Adiciona um objecto à simulação e estabelece a posição e rotação em que está como a inicial.
void ODESimulation::addObject(ODEObject *object)
{
	addObject(object, object->getPosition(), object->getQuaternion());
}



/// Adiciona um objecto à simulação e estabelece a rotação em que está como a inicial.
void ODESimulation::addObject(ODEObject *object, const ODEVector3 &initialPosition)
{
	addObject(object, initialPosition, object->getQuaternion());
}



/// Adiciona um objecto à simulação, definindo a sua posição e rotação inicial.
void ODESimulation::addObject(ODEObject *object, const ODEVector3 &initialPosition
	, const ODEQuaternion &initialRotation)
{
	this->objects.push_back(object);
	this->initialPositions.push_back(initialPosition);
	this->initialRotations.push_back(initialRotation);
	object->setPosition(initialPosition);
	object->setQuaternion(initialRotation);
}



/// Retira o objecto da simulação.
bool ODESimulation::removeObject(ODEObject *object)
{
	return removeObject(indexOf(*object));
}



/// Retira o objecto da simulação.
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



/// Devolve o objecto correspondente a index ou NULL se não existir.
ODEObject* ODESimulation::getObject(int index) const
{
	if (!isValidIndex(index))
	{
		return NULL;
	}

	return this->objects[index];
}




/// Faz um reset ao objecto , retirando todas as forças
/// e pondo-o na sua posição e rotação inicial 
void ODESimulation::reset(ODEObject *object)
{
	reset(object, indexOf(*object));
}



/// Faz um reset ao objecto correspondente a index,
/// retirando todas as forças e pondo-o na sua posição e rotação inicial.
void ODESimulation::reset(int index)
{
	reset(getObject(index), index);
}



/// Faz um reset à simulação, retirando todas as forças
/// e pondo os objectos nas suas posições e rotações iniciais.
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



/// Devolve o número de objectos na simulação.
int ODESimulation::objectsCount() const
{
	return (int)this->objects.size();
}



/// Devolve o índice do objecto object.
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



/// Indica se o índice é válido.
bool ODESimulation::isValidIndex(int index) const
{
	return (index >= 0 && index < objectsCount());
}
#include "Space.h"

/// Cria um novo espaço.
Space::Space()
{
	this->space = dHashSpaceCreate(0);
}



/// Cria um novo espaço que pertence a other_space.
Space::Space(Space &other_space)
{
	this->space = dHashSpaceCreate(other_space.space);
}



/// Destrói os objectos associados ao espaço e o espaço.
Space::~Space()
{
	if (this->space != NULL)
	{
		for(int i = 0; i < (int)this->objects.size(); i++)
		{
			this->objects[i]->~Object();
		}
		
		for(int i = 0; i < (int)this->geometries.size(); i++)
		{
			this->geometries[i]->~Geometry();
		}
		dSpaceDestroy(this->space);
		this->space = NULL;
	}
}



/// Adiciona o objecto a este espaço.
void Space::AddObject(Object& object)
{
	dSpaceRemove(dGeomGetSpace(object.Geometry()->ID()), object.Geometry()->ID());
	dSpaceAdd(this->space, object.Geometry()->ID());
	this->objects.push_back(&object);
}



/// Adiciona uma geometria a este espaço.
void Space::AddGeometry(Geometry &geometry)
{
	dSpaceRemove(dGeomGetSpace(geometry.ID()), geometry.ID());
	dSpaceAdd(this->space, geometry.ID());
	this->geometries.push_back(&geometry);
}



/// Desenha os objectos que pertencem ao espaço e estejam activos.
void Space::Draw()
{
	for(unsigned int i = 0; i < this->objects.size(); i++)
	{
		this->objects[i]->Geometry()->Draw();
	}

	for(unsigned int i = 0; i < this->geometries.size(); i++)
	{
		this->geometries[i]->Draw();
	}
}



/// Devolve o objecto correspondente à geometria se o encontrar ou NULL se não encontrar.
Object * Space::GetObject(dGeomID geometry)
{
	for(unsigned int i = 0; i < this->objects.size(); i++)
	{
		if(this->objects[i]->Geometry()->ID() == geometry)
		{
			return this->objects[i];
		}
	}

	return NULL;
}



/// Devolve a geometria correspondente a geometry se a encontrar ou NULL se não encontrar.
Geometry * Space::GetGeometry(dGeomID geometry)
{
	for(int i = 0; i < (int)this->geometries.size(); i++)
	{
		if(this->geometries[i]->ID() == geometry)
		{
			return this->geometries[i];
		}
	}

	return NULL;
}



/// Coloca os objectos e geometrias do espaço nas suas posições iniciais.
void Space::Reset()
{
	for(unsigned int i = 0; i < this->objects.size(); i++)
	{
		this->objects[i]->Reset();
	}

	for(unsigned int i = 0; i < this->geometries.size(); i++)
	{
		this->geometries[i]->Reset();
	}
}



/// Coloca no final de objects os objectos contidos neste espaço.
void Space::GetObjects(std::vector< Object * >& objects)
{
	for(unsigned int i = 0; i < this->objects.size(); i++)
	{
		objects.push_back(this->objects[i]);
	}
}



/// Coloca no final de geometries as geometrias contidos neste espaço.
void Space::GetGeometries(std::vector< Geometry * > &geometries)
{
	for(unsigned int i = 0; i < this->geometries.size(); i++)
	{
		geometries.push_back(this->geometries[i]);
	}
}



/// Prepara os objectos e geometrias do espaço para mais uma iteração do ciclo principal.
void Space::Prepare()
{
	for(unsigned int i = 0; i < this->objects.size(); i++)
	{
		this->objects[i]->Geometry()->previousPosition = this->objects[i]->Geometry()->GetPosition();
		this->objects[i]->Prepare();
	}

	for(unsigned int i = 0; i < this->geometries.size(); i++)
	{
		this->geometries[i]->previousPosition = this->geometries[i]->GetPosition();
		this->geometries[i]->Prepare();
	}
}



/// Devolve a identificação do espaço.
dSpaceID Space::ID() const
{
	return this->space;
}



/// Indica se alguma geometria pertencente ao espaco intersecta geometry.
bool Space::Intersects(Geometry &geometry)
{
	for (int i = 0; i < (int) this->objects.size(); i++)
	{
		if (geometry.Intersects(*(this->objects[i]->Geometry())))
		{
			return true;
		}
	}

	for (int i = 0; i < (int) this->geometries.size(); i++)
	{
		if (geometry.Intersects(*(this->geometries[i])))
		{
			return true;
		}
	}

	return false;
}



/// Apaga o objecto do espaço.
bool Space::RemoveObject(Object* object)
{
	for(int i = 0; i < (int)this->objects.size(); i++)
	{
		if (this->objects[i]->ID() == object->ID())
		{
			this->objects[i]->~Object();
			this->objects.erase(this->objects.begin() + i);

			return true;
		}
	}

	return false;
}



/// Apaga a geometria do espaço
bool Space::RemoveGeometry(Geometry *geometry)
{
	for(int i = 0; i < (int)this->geometries.size(); i++)
	{
		if (this->geometries[i]->ID() == geometry->ID())
		{
			this->geometries.erase(this->geometries.begin() + i);
			this->geometries[i]->~Geometry();

			return true;
		}
	}

	return false;
}

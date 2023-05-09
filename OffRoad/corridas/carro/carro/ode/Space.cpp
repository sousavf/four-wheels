#include "Space.h"

/// Cria um novo espa�o.
Space::Space()
{
	this->space = dHashSpaceCreate(0);
}



/// Cria um novo espa�o que pertence a other_space.
Space::Space(Space &other_space)
{
	this->space = dHashSpaceCreate(other_space.space);
}



/// Destr�i os objectos associados ao espa�o e o espa�o.
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



/// Adiciona o objecto a este espa�o.
void Space::AddObject(Object& object)
{
	dSpaceRemove(dGeomGetSpace(object.Geometry()->ID()), object.Geometry()->ID());
	dSpaceAdd(this->space, object.Geometry()->ID());
	this->objects.push_back(&object);
}



/// Adiciona uma geometria a este espa�o.
void Space::AddGeometry(Geometry &geometry)
{
	dSpaceRemove(dGeomGetSpace(geometry.ID()), geometry.ID());
	dSpaceAdd(this->space, geometry.ID());
	this->geometries.push_back(&geometry);
}



/// Desenha os objectos que pertencem ao espa�o e estejam activos.
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



/// Devolve o objecto correspondente � geometria se o encontrar ou NULL se n�o encontrar.
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



/// Devolve a geometria correspondente a geometry se a encontrar ou NULL se n�o encontrar.
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



/// Coloca os objectos e geometrias do espa�o nas suas posi��es iniciais.
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



/// Coloca no final de objects os objectos contidos neste espa�o.
void Space::GetObjects(std::vector< Object * >& objects)
{
	for(unsigned int i = 0; i < this->objects.size(); i++)
	{
		objects.push_back(this->objects[i]);
	}
}



/// Coloca no final de geometries as geometrias contidos neste espa�o.
void Space::GetGeometries(std::vector< Geometry * > &geometries)
{
	for(unsigned int i = 0; i < this->geometries.size(); i++)
	{
		geometries.push_back(this->geometries[i]);
	}
}



/// Prepara os objectos e geometrias do espa�o para mais uma itera��o do ciclo principal.
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



/// Devolve a identifica��o do espa�o.
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



/// Apaga o objecto do espa�o.
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



/// Apaga a geometria do espa�o
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

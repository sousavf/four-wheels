#include "Ray.h"

/// Cria um novo ray com comprimento length.
Ray::Ray(double length)
{
	Init(length);
}



/// Cria um novo ray associado a object com comprimento length.
Ray::Ray(Object* object, double length)
{
	Init(length);
	Attach(object);
}



/// Cria um novo ray com comprimento length.
void Ray::Init(double length)
{
	this->object = NULL;
	this->length = length;
	SetColor(Geometry::Red);
	SetTransparency(Geometry::AlmostTransparent);
	this->geometry = dCreateRay(0, (dReal) length);
	this->doScan = false;
	this->levelOfScan = 1;
	this->distances = NULL;
	this->onlyFront = false;
	this->enabled = true;
	this->draw = false;
}



/// Destrói o ray.
Ray::~Ray()
{
	delete this->distances;
}

		
		
/// Desenha o ray.
void Ray::Draw()
{
	dVector3 startPos, endPos, direction;
	float color[3];

	GetColors(color);
	dsSetColorAlpha(color[0], color[1], color[2], Alpha());
	dGeomRayGet(this->geometry, startPos, direction);
	endPos[0] = startPos[0] + direction[0] * (dReal)this->length;
	endPos[1] = startPos[1] + direction[1] * (dReal)this->length;
	endPos[2] = startPos[2] + direction[2] * (dReal)this->length;
	endPos[3] = startPos[3] + direction[3] * (dReal)this->length;
	dsDrawLine(startPos, endPos);
}



/// Devolve 0.
double Ray::Width()
{
	return 0;
}



/// Devolve 0.
double Ray::Height()
{
	return 0;
}



/// Devolve o comprimento do ray.
double Ray::Length()
{
	return this->length;
}



/// Aplica uma rotação ao ray.
void Ray::SetRotation(XYZ rotation)
{
	dVector3 origin, direction;

	dGeomRayGet(this->geometry, origin, direction);
	direction[0] = (dReal)cos(Math::ToRadians(rotation.x));
	direction[1] = (dReal)sin(Math::ToRadians(rotation.x));
	direction[2] = 0;
	direction[3] = 0;
	dNormalize3(direction);
	dGeomRaySet(this->geometry, origin[0], origin[1], origin[2], direction[0], direction[1], direction[2]);
}

	
	
/// Actualiza o ray vendo os objectos com que colide.
void Ray::Scan(World &world)
{
	std::vector< dGeomID > geometries;
	double startX = 0;
	int j;

	if (this->object != NULL)
	{
		XYZ objectPosition = this->object->Geometry()->GetPosition();
		objectPosition.z = 0.01;
		SetPosition(objectPosition);
		SetRotation(XYZ(this->object->Geometry()->GetRotation().z + 90, 0, 0));
		startX = this->object->Geometry()->GetRotation().z + 90;
	}
	geometries = AcceptedGeomIDs(world.GetObjects(), world.GetGeometries());
	delete this->distances;

	if (this->doScan)
	{
		this->distances = new double[this->levelOfScan];
		j = 0;

		for (double i = 0; i < 360; i += (360.0 / this->levelOfScan))
		{
			if ( !this->onlyFront || (this->onlyFront && (i <= 90 || i >= 270)) )
			{
				SetRotation(XYZ(startX + i, 0, 0));
				this->distances[j++] = Collide(geometries);

				if (this->draw)
				{
					Draw();
				}
			}
		}
	}
	else
	{
		this->distances = new double[1];
		this->distances[0] = Collide(geometries);

		if (this->draw)
		{
			Draw();
		}
	}
}



/// Colide o ray com todas as geometrias e devolve a distância mais curta.
double Ray::Collide(std::vector< dGeomID > &geoms) const
{
	dContactGeom contact;
	double best;
	
	best = this->length;

	for (int i = 0; i < (int) geoms.size(); i++)
	{
		if (dCollide(this->geometry, geoms[i], 0, &contact, sizeof(dContactGeom)))
		{
			if (contact.depth < this->length)
			{
				best = contact.depth;
			}
		}
	}

	return best;
}



/// Junta os dois vectores num só vector de dGeomID com todas as geometrias não ignoradas.
std::vector< dGeomID > Ray::AcceptedGeomIDs(std::vector< Object * >& objects
							, std::vector< Geometry * >& geometries) const
{
	std::vector< dGeomID > geomIDs;

	for (int i = 0; i < (int) objects.size(); i++)
	{
		if ( objects[i]->GetEnable() && !IgnoredGeometry(objects[i]->Geometry()->ID()) )
		{
			geomIDs.push_back(objects[i]->Geometry()->ID());
		}
	}

	for (int i = 0; i < (int) geometries.size(); i++)
	{
		if (!IgnoredGeometry(geometries[i]->ID()))
		{
			geomIDs.push_back(geometries[i]->ID());
		}
	}

	return geomIDs;
}



/// Devolve o comprimento do ray.
double Ray::GetLength()
{
	return this->length;
}



/// Ignora o objecto quando for determinar as distâncias para os objectos mais próximos.
void Ray::Ignore(Object& object)
{
	this->ignoredGeometries.push_back(object.Geometry()->ID());
}



/// Ignora a geometria quando for determinar as distâncias para os objectos mais próximos.
void Ray::Ignore(Geometry &geometry)
{
	this->ignoredGeometries.push_back(geometry.ID());
}



/// Ignora todos os objectos e geometrias contidos no espaço.
void Ray::Ignore(Space *space)
{
	std::vector< Geometry* > geometries;
	std::vector< Object* > objects;

	space->GetGeometries(geometries);
	space->GetObjects(objects);

	for (int i = 0; i < (int)geometries.size(); i++)
	{
		this->ignoredGeometries.push_back(geometries[i]->ID());
	}

	for (int i = 0; i < (int)objects.size(); i++)
	{
		this->ignoredGeometries.push_back(objects[i]->Geometry()->ID());
	}
}



/// Indica se uma geometria é para ser ignorada.
bool Ray::IgnoredGeometry(dGeomID geometry) const
{
	for(unsigned int i = 0; i < this->ignoredGeometries.size(); i++)
	{
		if(this->ignoredGeometries[i] == geometry)
		{
			return true;
		}
	}

	return false;
}



/// Prende o ray ao objecto de forma que anda em conjunto com este.
void Ray::Attach(Object* object)
{
	this->object = object;
	Ignore(*object);
}



/// Devolve as distâncias para os pontos de contacto com os objectos que esbarrou.
/// As distâncias são relativas ao nível de scan que o ray faz e a 1ª posição
/// do vector corresponde à distância na direcção para onde o ray está voltado.
double* Ray::GetDistances() const
{
	return this->distances;
}



/// Define se o ray faz um scan de 360º sobre si mesmo
void Ray::SetDoScan(bool value)
{
	this->doScan = value;
}



/// Indica se o ray faz um scan de 360º sobre si mesmo
bool Ray::GetDoScan() const
{
	return this->doScan;
}



/// Define o nr. de iteraçãos que o ray faz num total de 360º.
void Ray::SetLevelOfScan(int value)
{
	if (value > 0)
	{
		this->levelOfScan = value;
	}
}



/// Devolve o nr. de iteraçãos que o ray faz num total de 360º.
int Ray::GetLevelOfScan()
{
	return this->levelOfScan;
}



/// Estabelece se desenha o ray ou não.
void Ray::SetDraw(bool value)
{
	this->draw = value;
}



/// Indica se desenha o ray.
bool Ray::GetDraw() const
{
	return this->draw;
}



/// Define se apenas consideramos a parte da frente.
void Ray::SetOnlyFront(bool value)
{
	this->onlyFront = true;
}



/// Indica se estamos a considerar apenas a parte da frente.
bool Ray::GetOnlyFront() const
{
	return this->onlyFront;
}



/// Limpa a lista de geometrias ignoradas.
void Ray::ClearIgnored()
{
	this->ignoredGeometries.clear();
}



/// Define o estado do ray.
void Ray::SetEnable(bool value)
{
	this->enabled = value;
}



/// Indica se o ray está activo.
bool Ray::IsEnabled() const
{
	return this->enabled;
}
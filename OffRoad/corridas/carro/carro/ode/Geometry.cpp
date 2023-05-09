#include "Geometry.h"
#include "Math.h"
#include "Object.h"

/// Cria uma geometria vazia.
Geometry::Geometry()
{
	for(int i = 0; i < 3; i++)
	{
		this->firstTime[i] = true;
	}

	this->startPosition.x = 0;
	this->startPosition.y = 0;
	this->startPosition.z = 0;

	this->startRotation.x = 0;
	this->startRotation.y = 0;
	this->startRotation.z = 0;

	this->startColor = DEFAULT_COLOR;
	this->transparency = Opaque;
	this->touched = false;
}



/// Destrói a geometria.
Geometry::~Geometry()
{
	if (this->geometry != NULL)
	{
		dGeomDestroy(this->geometry);
		this->geometry = NULL;
	}
}



///Define a posição da geometria.
void Geometry::SetPosition(XYZ position)
{
	dReal x, y, z;

	x = (dReal) position.x;
	y = (dReal) position.y;
	z = (dReal) position.z;
	dGeomSetPosition(this->geometry, x, y, z);

	if(firstTime[0])
	{
		this->startPosition = position;
		firstTime[0] = false;
	}
}



/// Devolve as coordenadas onde a geometria se encontra.
XYZ Geometry::GetPosition()
{
	XYZ position_double;
	const dReal *position_real;
	
	position_real = dGeomGetPosition(this->geometry);
	position_double.x = (double) position_real[0];
	position_double.y = (double) position_real[1];
	position_double.z = (double) position_real[2];

	return position_double;
}



/// Define a rotação da geometria.
void Geometry::SetRotation(XYZ rotation)
{
	dMatrix3 R, R1, R2, R3, R4;
	dReal x, y, z;

	x = (dReal) Math::ToRadians(rotation.x);
	y = (dReal) Math::ToRadians(rotation.y);
	z = (dReal) Math::ToRadians(rotation.z);
	dRFromAxisAndAngle(R1, 1, 0, 0, x);
	dRFromAxisAndAngle(R2, 0, 1, 0, y);
	dRFromAxisAndAngle(R3, 0, 0, 1, z);
	dMultiply0 (R4, R2, R3, 3, 3, 3);
	dMultiply0 (R, R4, R1, 3, 3, 3);
	dGeomSetRotation(this->geometry, R);
	
	if(firstTime[1])
	{
		this->startRotation = rotation;
		firstTime[1] = false;
	}
}




/// Devolve a rotação da geometria em termos dos referenciais XYZ.
XYZ Geometry::GetRotation()
{
	dQuaternion q;
	XYZ rotation_double;
	const dReal *rotation_real;
	double x, y, z;

	rotation_real = dGeomGetRotation(this->geometry);
	dRtoQ(rotation_real, q);
	dNormalize4(q);
	x = atan2(2 * (q[2]*q[3] + q[0]*q[1]), (q[0]*q[0] - q[1]*q[1] - q[2]*q[2] + q[3]*q[3]));
	y = asin(-2 * (q[1]*q[3] - q[0]*q[2]));
	z = atan2(2 * (q[1]*q[2] + q[0]*q[3]), (q[0]*q[0] + q[1]*q[1] - q[2]*q[2] - q[3]*q[3]));
	rotation_double.x = Math::ToDegrees(x);
	rotation_double.y = Math::ToDegrees(y);
	rotation_double.z = Math::ToDegrees(z);

	return rotation_double;
}





/// Define a cor da geometria.
void Geometry::SetColor(Color color)
{
	this->color = color;

	if(firstTime[3])
	{
		this->startColor = color;
		firstTime[3] = false;
	}
}




/// Devolve a cor da geometria
Geometry::Color Geometry::GetColor()
{
	return this->color;
}



/// Devolve um vector de floats com os valores RGB (de 0 a 1) relativos às cores.
void Geometry::GetColors(float *rgb)
{
	GetColors(rgb, this->color);
}



/// Color em rgb a correspondência da cor em color.
void Geometry::GetColors(float *rgb, Color color)
{
	switch(color)
	{
		case Black:
			rgb[0] = 0;
			rgb[1] = 0;
			rgb[2] = 0;
			break;

		case Blue:
			rgb[0] = 0;
			rgb[1] = 0;
			rgb[2] = 1;
			break;

		case Gray:
			rgb[0] = 0.5;
			rgb[1] = 0.5;
			rgb[2] = 0.5;
			break;

		case Green:
			rgb[0] = 0;
			rgb[1] = 1;
			rgb[2] = 0;
			break;

		case Red:
			rgb[0] = 1;
			rgb[1] = 0;
			rgb[2] = 0;
			break;

		default:
		case White:
			rgb[0] = 1;
			rgb[1] = 1;
			rgb[2] = 1;
			break;
	}
}



/// Coloca a geometria no estado em que se encontrava quando foi criada.
void Geometry::Reset()
{
	SetPosition(this->startPosition);
	SetRotation(this->startRotation);
	SetColor(this->startColor);
}



/// Devolve a posição anterior.
XYZ Geometry::GetPreviousPosition()
{
	return this->previousPosition;
}



/// Define o nível de transparência da geometria.
void Geometry::SetTransparency(Transparency transparency)
{
	this->transparency = transparency;
}



/// Devolve o nível de transparência da geometria.
Geometry::Transparency Geometry::GetTransparency()
{
	return this->transparency;
}



/// Devolve o alpha de transparência do objecto. 1.0 é completamente opaco e 0.0 é completamente transparente.
float Geometry::Alpha()
{
	switch(this->transparency)
	{
		case Transparent:
			return 0.0;

		case AlmostTransparent:
			return 0.25;

		case SemiTransparent:
			return 0.5;

		case AlmostOpaque:
			return 0.75;

		case Opaque:
		default:
			return 1.0;
	}
}



/// Devolve a identificação da geometria.
dGeomID Geometry::ID()
{
	return this->geometry;
}



/// Indica se a geometri colide com outra geometria.
bool Geometry::Intersects(Geometry &anotherGeometry)
{
	dContact contact;
	int n;

	n = dCollide(this->geometry, anotherGeometry.geometry, 1, &contact.geom, sizeof(dContact));

	return (n > 0);
}



/// Remove a geometria do espaço em que esteja.
void Geometry::RemoveFromSpace()
{
	dSpaceRemove(dGeomGetSpace(this->geometry), this->geometry);
}



/// Define a categoria da geometria.
void Geometry::SetCategory(long bits)
{
	dGeomSetCategoryBits(this->geometry, bits);
}



/// Define com o que é que colide.
void Geometry::SetCollide(long bits)
{
	dGeomSetCollideBits(this->geometry, bits);
}



/// Indica se foi tocada por algum objecto.
bool Geometry::WasTouched() const
{
	return this->touched;
}



/// Devolve True se esta geometria tocou em object na última iteração do mundo.
bool Geometry::Touched(Object& object) const
{
	return Touched(*(object.Geometry()));
}



/// Devolve True se esta geometria tocou em geometry na última iteração do mundo.
bool Geometry::Touched(Geometry &geometry) const
{
	return Touched(geometry.ID());
}



/// Devolve True se esta geometria tocou em geom na última iteração do mundo.
bool Geometry::Touched(dGeomID geom) const
{
	for(int i = 0; i < (int)this->touchedGeometries.size(); i++)
	{
		if(this->touchedGeometries[i] == geom)
		{
			return true;
		}
	}

	return false;
}



/// Adiciona geom à lista de geoms tocadas.
void Geometry::AddTouchedGeometry(dGeomID geom)
{
	this->touched = true;
	this->touchedGeometries.push_back(geom);
}



/// Limpa a lista de geometrias que foram tocadas.
void Geometry::ClearTouchedGeometries()
{
	this->touched = false;
	this->touchedGeometries.clear();
}



/// Prepara a geometria para mais um ciclo.
void Geometry::Prepare()
{
	ClearTouchedGeometries();
}



/// Define a posição inicial.
void Geometry::SetStartPosition(XYZ position)
{
	this->startPosition = position;
}



/// Define a rotação inicial.
void Geometry::SetStartRotation(XYZ rotation)
{
	this->startRotation = rotation;
}
#include <drawstuff/drawstuff.h>
#include "Camera.h"
#include "World.h"

bool operator == (const XYZ &xyz1, const XYZ &xyz2)
{
	return (xyz1.x == xyz2.x) && (xyz1.y == xyz2.y) && (xyz1.z == xyz2.z);
}

/// Compara duas estruturas View e devolve true se forem iguais.
bool operator == (const Camera::View &view1, const Camera::View &view2)
{
	return (view1.position == view2.position) && (view1.rotation == view2.rotation);
}

const Camera::View Camera::CLOSE_VIEW = Camera::View(XYZ(2, 2, 2), XYZ(0, -30, 90));
const Camera::View Camera::NORMAL_VIEW = Camera::View(XYZ(8, 8, 8), XYZ(0, -30, 90));
const Camera::View Camera::FAR_VIEW = Camera::View(XYZ(18, 18, 18), XYZ(0, -30, 90));
const Camera::View Camera::TOP_VIEW = Camera::View(XYZ(0, 0, 90), XYZ(0, -90, 90));

/// Cria uma nova câmara com Viewpoint default (posição na origem e sem rotação).
Camera::Camera()
{
}



/// Cria uma nova câmara com Viewpoint default (posição na origem e sem rotação).
Camera::Camera(World &world)
{
	Init(world);
	SetViewpoint(0);
}



/// Cria uma nova câmera com Viewpoint view e adiciona view à lista de viewpoints da câmera.
Camera::Camera(World &world, View view)
{
	Init(world);
	AddView(view);
	SetViewpoint(view);
}



/// Cria uma nova câmera e liga-a a object.
Camera::Camera(World &world, Object& object)
{
	Init(world);
	Attach(object);
}



/// Destrói a câmera
Camera::~Camera()
{
}



/// Adiciona a vista default à câmera (posição na origem e sem rotação).
void Camera::Init(World &world)
{
	View new_view;

	this->world = &world;
	this->object = NULL;
	new_view.position.x = 0;
	new_view.position.y = 0;
	new_view.position.z = 0;
	new_view.rotation.x = 0;
	new_view.rotation.y = 0;
	new_view.rotation.z = 0;
	AddView(new_view);
	this->free = true;
	this->attachType = Normal;
}



/// Liga a câmera a um objecto.
void Camera::Attach(Object& object)
{
	this->free = false;
	this->object = &object;
	Refresh();
}



/// Actualiza o viewpoint da câmera.
void Camera::Refresh()
{
	if( !this->world->Started() || this->free )
	{
		return;
	}

	float xyz[3], hpr[3];

	if(this->object != NULL)
	{
		View view;
		XYZ position, rotation;
		double width, length, height;

		view = GetView(this->attachType);
		position = this->object->Geometry()->GetPosition();
		rotation = this->object->Geometry()->GetRotation();
		width = this->object->Geometry()->Width() + view.position.x;
		length = this->object->Geometry()->Length() + view.position.y;
		height = this->object->Geometry()->Height() + view.position.z;
		xyz[0] = (float) ( position.x + width * sin(Math::ToRadians(rotation.z)) );
		xyz[1] = (float) ( position.y - length * cos(Math::ToRadians(rotation.z)) );
		xyz[2] = (float) (position.z + height);
		hpr[0] = (float) (rotation.z + view.rotation.z);
		hpr[1] = (float) view.rotation.y;
		hpr[2] = (float) view.rotation.x;
	}
	else
	{
		xyz[0] = (float) this->position.x;
		xyz[1] = (float) this->position.y;
		xyz[2] = (float) this->position.z;

		hpr[0] = (float) this->rotation.x;
		hpr[1] = (float) this->rotation.y;
		hpr[2] = (float) this->rotation.z;
	}
	dsSetViewpoint(xyz, hpr);
}



/// Liberta a câmera do objecto a que está associada e deixa-a livre de viewpoint.
Object* Camera::Free()
{
	Object *tmp;

	tmp = this->object;
	this->object = NULL;
	this->free = true;

	return tmp;
}



/// Muda a posição da câmera.
void Camera::SetPosition(XYZ position)
{
	this->free = true;
	this->position = position;
	Refresh();
}



/// Devolve as coordenadas da câmera.
XYZ Camera::GetPosition()
{
	float pos[3], rot[3];
	XYZ xyz;

	dsGetViewpoint(pos, rot);
	xyz.x = pos[0];
	xyz.x = pos[1];
	xyz.x = pos[2];

	return xyz;
}



/// Muda a rotação da câmera.
void Camera::SetRotation(XYZ rotation)
{
	this->free = true;
	this->position = position;
	Refresh();
}



/// Devolve a rotação da câmera.
XYZ Camera::GetRotation()
{
	float pos[3], rot[3];
	XYZ xyz;

	dsGetViewpoint(pos, rot);
	xyz.x = rot[0];
	xyz.x = rot[1];
	xyz.x = rot[2];

	return xyz;
}



/// Estabelece a vista da câmera e devolve true se for câmera válida ou false em contrário.
bool Camera::SetViewpoint(View view)
{
	for(unsigned int i = 0; i < this->views.size(); i++)
	{
		if(this->views[i] == view)
		{
			return SetViewpoint(i);
		}
	}

	return false;
}



/// Estabelece a vista da câmera e devolve true se for câmera válida ou false em contrário.
bool Camera::SetViewpoint(int view_index)
{
	if( (view_index < 0) || (view_index >= (int) this->views.size()) )
	{
		return false;
	}

	this->position = this->views[view_index].position;
	this->rotation = this->views[view_index].rotation;
	this->free = false;
	Refresh();

	return true;
}



/// Adiciona a vista à câmera e devolve o seu índice.
int Camera::AddView(View view)
{
	this->views.push_back(view);
	
	return (int) this->views.size();
}



/// Estabelece o tipo de attach que efectua.
void Camera::SetAttachType(AttachType type)
{
	this->attachType = type;
}



/// Devolve o tipo de attach que efectua.
Camera::AttachType Camera::GetAttachType() const
{
	return this->attachType;
}



/// Devolve uma vista baseada no tipo de attach
Camera::View Camera::GetView(AttachType type) const
{
	switch (type)
	{
		case Close:
			return Camera::CLOSE_VIEW;

		case Far:
			return Camera::FAR_VIEW;

		case Top:
			return Camera::TOP_VIEW;

		case Normal:
		default:
			return Camera::NORMAL_VIEW;
	}
}



/// Devolve o número de vistas instaladas na câmara.
int Camera::GetViewpointCount() const
{
	return (int)this->views.size();
}
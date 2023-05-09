#ifndef Camera_h
#define Camera_h

#include <vector>
#include "Auxiliary.h"
#include "Object.h"

class Camera
{
	public:
		typedef struct View
		{
			XYZ position;
			XYZ rotation;

			View()
			{
			}

			View(XYZ position, XYZ rotation)
			{
				this->position = position;
				this->rotation = rotation;
			}
		} View;

		enum AttachType
		{
			Close,
			Normal,
			Far,
			Top
		};

		Camera();
		Camera(World &world);
		Camera(World &world, View view);
		Camera(World &world, Object& object);
		~Camera();

		void Attach(Object& object);
		void Refresh();
		Object * Free();
		void SetPosition(XYZ position);
		XYZ GetPosition();
		void SetRotation(XYZ rotation);
		XYZ GetRotation();
		bool SetViewpoint(View view);
		bool SetViewpoint(int view_index);
		int AddView(View view);
		void SetAttachType(AttachType type);
		AttachType GetAttachType() const;
		int GetViewpointCount() const;

	protected:
		static const View CLOSE_VIEW;
		static const View NORMAL_VIEW;
		static const View FAR_VIEW;
		static const View TOP_VIEW;

		Object* object;
		std::vector< View > views;
		XYZ position, rotation;
		World *world;
		bool free;
		AttachType attachType;

		void Init(World &world);
		View GetView(AttachType type) const;
};

#endif
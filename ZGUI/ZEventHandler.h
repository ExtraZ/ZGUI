#pragma once
namespace ZGUI
{
	class ZEventHandler
	{
	public:
		ZEventHandler();
		virtual ~ZEventHandler();
	};

	class ZEvent
	{
	public:
		ZEvent() {}
		virtual ~ZEvent() {}

		struct MouseClickEvent
		{
			struct Location
			{
				float x, y;
			} location;
			unsigned char mousebutton;
		};

		struct KeyPressEvent
		{
			unsigned char key;
			bool double_;
		};

		enum EventCategory
		{
			MouseEvent,
			KeyEvent
		} category;

		enum MouseEventType
		{
			MouseMove,
			MouseClick,
			MouseDrag
		} mouseEventType;

		union
		{
			MouseClickEvent click;
		};
	};
}

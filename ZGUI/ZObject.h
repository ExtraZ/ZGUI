#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <new>
#include <functional>

#include "ZEventHandler.h"
#include "ZEnums.h"

namespace ZGUI
{
	class ZObject;
	typedef std::function<void(ZObject&)> DrawCallbackFunction;

	class ZObject
	{
	public:
		ZObject();
		ZObject(std::string);
		virtual ~ZObject();

		virtual ZObject&	createChildObject(std::string name);
		virtual void		updateFocus(ZObject* focused_object);
		virtual void		move(float x, float y);
		virtual void		resize(float width, float height);
		virtual void		draw();
		virtual void		interact(ZEvent event);
	protected: virtual void doInteract(ZEvent event); public:
		virtual bool		checkCollision(StateSpace with);
				void		registerDrawCallback(DrawCallbackFunction function);
		


		std::string	getName() { return this->name; }
#ifdef _DEBUG
		std::string getTabPadding() { return this->tabpadding; }
#endif //_DEBUG

		ZObject*	getParent() { return this->parent; }
		void		setParent(ZObject& parent)
		{
			this->parent = &parent;
#ifdef _DEBUG
			if (this->parent)
				this->tabpadding = this->parent->getTabPadding().append("\t");
			else this->tabpadding = "\t";
#endif //_DEBUG
		}

		ZObject*	getChildObject(unsigned int index) { if (index < objects.size()) return objects.at(index); return 0; }

		virtual void setHighestFocus()
		{
			if (this->parent)
			{
				this->parent->updateFocus(this);
				this->focuslevel = 0;
			}
			else
				this->focuslevel = 0;
		}

		void		setLocation(float x, float y)
		{ 
			this->location.x = x;
			this->location.y = y;
		}
		void		setDimension(float width, float height) 
		{
			this->dimension.width = width;
			this->dimension.height = height;
		}


		// Operators
		ZObject&	operator[](unsigned int index);
		ZObject&	operator[](std::string name);

	protected:
		std::string name;
		struct Header
		{
			float height;
			std::string title;
		} header;

		struct Origin
		{
			float x;
			float y;
		} origin;
		struct Location
		{
			float x;
			float y;
		} location;
		struct Dimension
		{
			float width;
			float height;
		} dimension;

		short focuslevel;

		DrawCallbackFunction drawCallback;

		std::vector < ZObject* > objects; // All child objects
		ZObject* parent; // Pointer to parent object


		//tabpadding used to display correct tabbing in console (when _DEBUG is active)
#ifdef _DEBUG
		std::string tabpadding;
#endif // _DEBUG
	private:

	};
};
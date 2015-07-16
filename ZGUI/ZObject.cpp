#include "ZObject.h"

using namespace ZGUI;

ZObject::ZObject()
{
	origin.x = 0.f;
	origin.y = 0.f;

	location.x = 0.f;
	location.y = 0.f;

	dimension.width = 100.f;
	dimension.height = 50.f;

	header.height = 0.f;

	this->tabpadding = "\t";
}

ZObject::ZObject(std::string name)
{
	origin.x = 0.f;
	origin.y = 0.f;

	location.x = 0.f;
	location.y = 0.f;

	dimension.width = 100.f;
	dimension.height = 50.f;

	header.height = 0.f;
	
	this->tabpadding = "\t";
	this->name = name;

	focuslevel = 0;
}

ZObject::~ZObject()
{
#ifdef _DEBUG
	std::cout << "ZObject destructor - " << this->name << std::endl;
#endif // _DEBUG
	for (auto& object : objects)
		if (object)
		{
			delete object;
			object = 0;
		}
}

ZObject& ZObject::createChildObject(std::string name)
{
	ZObject* object = new ZObject(name);
	objects.push_back(object);
	objects.back()->setParent(*dynamic_cast<ZObject*>(this));
	object->setHighestFocus();
	return *object;
}

void ZObject::updateFocus(ZObject* focused_object)
{
	for (auto& object : objects)
		if (focused_object->focuslevel == 0)
			object->focuslevel++;
		else // TODO: Test this part, make sure no unexpected behavior occurs
			if (object->focuslevel <= focused_object->focuslevel)
				object->focuslevel++;
}

void ZObject::move(float x, float y)
{
	location.x = x - origin.x;
	location.y = y - origin.y;
}

void ZObject::resize(float width, float height)
{
	dimension.width = width;
	dimension.height = height;
}

void ZObject::draw()
{
	if (drawCallback)
		drawCallback(*this);
#ifdef _DEBUG
	if (!objects.empty())
		std::cout << this->getTabPadding() << "-Drawing " << this->getName() << "'s child objects" << std::endl;
#endif //_DEBUG
	for (auto& object : objects)
	{
#ifdef _DEBUG
		std::cout << object->getTabPadding() << "Drawing " << this->getName() << "'s child object " << object->getName() << std::endl;
#endif //_DEBUG
		object->draw();
	}
}

// Loop through all child objects, if interaction needed, call child's interact
// Needs a little revision to work with non mouse related events
void ZObject::interact(ZEvent event)
{
	// Looping all child object, to call interact or set focus
	for (auto& object : objects)
	{
		switch (event.category)
		{
		case ZEvent::MouseEvent:
			if (event.mouseEventType == ZEvent::MouseClick)
				if(this->checkCollision(StateSpace({ event.click.location.x, event.click.location.y, 1.f, 1.f } )))
					if (object->focuslevel == 0)
						object->interact(event);
					else
						object->setHighestFocus();
			break;
		case ZEvent::KeyEvent:
			// TODO: Add tab interaction to cycle focus
			break;
		default:
			//TODO: add default interaction?
			break;
		}
	}

	this->doInteract(event); // Call the actual interaction function (separated so overridden function will be used)
}

void ZObject::doInteract(ZEvent event)
{
	// Make sure focus level is updated, we assume that "this" object should be the highest focused because doInteract was called
	if (this->focuslevel != 0)
		this->setHighestFocus();

	// Checking interaction type
	switch (event.category)
	{
	case ZEvent::MouseEvent:
		if (event.mouseEventType == ZEvent::MouseClick)
		{
			if (this->checkCollision({ event.click.location.x, event.click.location.y, 1.f, 1.f }))
			{
#ifdef _DEBUG
				std::cout << "Object " << this->name << "s checkCollision with {" << event.click.location.x << ", " << event.click.location.y << ", 0.f, 0.f} returned true";
#endif // _DEBUG
				// Collision interaction goes here

			}
		}
		break;
	case ZEvent::KeyEvent:

		break;
	default:

		break;
	}
}

bool ZObject::checkCollision(StateSpace with)
{
	if (with.x >= this->location.x - this->origin.x && with.x <= this->location.x - this->origin.x + this->dimension.width)
		if (with.y >= this->location.y - this->origin.y && with.y <= this->location.y - this->origin.y + this->dimension.height)
			return true;
	return false;
}

void ZObject::registerDrawCallback(DrawCallbackFunction function)
{
	this->drawCallback = function;
}

ZObject& ZObject::operator[](unsigned int index)
{
	if (objects.size() > index)
		return *objects[index];
	throw std::exception("Object out of scope");
	return *objects[0];
}

ZObject& ZObject::operator[](std::string name)
{
	for (auto& object : objects)
		if (object->getName() == name)
			return *object;
	throw std::exception("No object with corresponding name found");
	return *objects[0];
}
#include "ZWindow.h"
#include "ZInterface.h"
#include "ZEnums.h"

using namespace ZGUI;

ZWindow::ZWindow()
{
	this->focuslevel = 0;
	this->header.height = ZWindowConsts::DEFAULT_HEADER_HEIGHT;
}

ZWindow::ZWindow(std::string name)
{
	this->name = name;
	this->focuslevel = 0;
	this->header.height = ZWindowConsts::DEFAULT_HEADER_HEIGHT;
}

ZWindow::~ZWindow()
{
	std::cout << "ZWindow destructor - " << this->name << std::endl;
	for (auto& object : objects)
		if (object)
		{
			delete object;
			object = 0;
		}
}

void ZWindow::setHighestFocus()
{
	if (this->parent)
	{
		reinterpret_cast<ZInterface*>(this->parent)->updateFocus(this);
		this->focuslevel = 0;
	}
	else
		this->focuslevel = 0;
}

void ZWindow::move(float x, float y)
{
	location.x = x - origin.x;
	location.y = y - origin.y;
}

void ZWindow::resize(float width, float height)
{
	dimension.width = width;
	dimension.height = height;
}

void ZWindow::draw()
{
	if (drawCallback)
		drawCallback(*this);
#ifdef _DEBUG
	std::cout << this->getTabPadding() << "-Drawing " << this->getName() << "'s child objects " << std::endl;
#endif // _DEBUG
	for (auto& object : objects)
	{
#ifdef _DEBUG
		std::cout << object->getTabPadding() << "Drawing " << this->getName() << "'s child object " << object->getName() << std::endl;
#endif // _DEBUGE
		object->draw();
	}
}
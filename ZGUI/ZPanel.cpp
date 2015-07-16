#include "ZPanel.h"

using namespace ZGUI;

ZPanel::ZPanel()
{
}

ZPanel::ZPanel(std::string name)
{
	this->name = name;
}

ZPanel::~ZPanel()
{
}

void ZPanel::draw()
{
	std::cout << "\t\tDrawing objects" << std::endl;
	for (auto& object : objects)
	{
		object->draw();
		std::cout << "\t\t\tDrawing object " << object->getName() << std::endl;
	}
}
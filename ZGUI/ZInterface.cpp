#include "ZInterface.h"

using namespace ZGUI;

ZInterface::ZInterface()
{
}


ZInterface::~ZInterface()
{
	
}

ZObject& ZInterface::createWindow(std::string name)
{
	ZWindow* zwindow = new ZWindow(name);
	windows.push_back(zwindow);
	windows.back()->setParent(this);
	zwindow->setHighestFocus();
	return *zwindow;
}

ZWindow* ZInterface::getWindow(std::string name)
{
	for (auto& window : windows)
		if (window->getName() == name)
			return window;
	return 0;
}

void ZInterface::updateFocus(ZWindow* focused_window)
{
	for (auto& window : windows)
		if (focused_window->focuslevel == 0)
			window->focuslevel++;
		else // TODO: Test this part, make sure no unexpected behavior occurs
			if (window->focuslevel <= focused_window->focuslevel)
				window->focuslevel++;
}

void ZInterface::draw()
{
#ifdef _DEBUG
	if (!windows.empty())
		std::cout << "Drawing windows\n";
#endif //_DEBUG
	for (auto& window : windows)
	{
#ifdef _DEBUG
		std::cout << window->getTabPadding() << "Drawing window " << window->getName() << std::endl;
#endif //_DEBUG
		window->draw();
	}
}

void ZInterface::destory()
{
#ifdef _DEBUG
	std::cout << "ZInterface destructor\n";
#endif //_DEBUG
	for (auto& window : windows)
		if (window)
		{
			delete window;
			window = 0;
		}
}

void ZInterface::interact(ZEvent event)
{
	for (auto& window : windows)
		if (window)
			window->interact(event);
}
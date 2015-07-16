#include <windows.h>
#include <iostream>
#include <conio.h>

#include "../ZGUI/ZInterface.h"

void Draw(ZGUI::ZObject& object)
{
	std::cout << "Draw Callback called for object " << object.getName() << std::endl;
}

int main()
{
	ZGUI::ZInterface zInterface;
	zInterface.createWindow("First Window").createChildObject("First Object").getParent()->createChildObject("Second Object").createChildObject("First Child Object");
	zInterface.createWindow("Second Window").createChildObject("First Object").createChildObject("First Child Object");
	zInterface.createWindow("Third Window").createChildObject("First Object").getParent()->createChildObject("Second Object").getParent()->createChildObject("Third Object").createChildObject("First Child Object");
	
	zInterface[0][0].registerDrawCallback(Draw);

	zInterface.draw();
	
	std::cout << std::endl << std::endl;
	ZGUI::ZWindow* window = &zInterface["Third Window"]; //zInterface.getWindow("Third Window");
	std::cout << window->getName() << "\n\n";
	window->setLocation(500.f, 300.f);
	window->setDimension(200.f, 150.f);
	ZGUI::ZObject* object = window->getChildObject(1);
	object->setLocation(550.f, 350.f);
	object->setDimension(100.f, 200.f);

	ZGUI::ZEvent event;
	event.category = ZGUI::ZEvent::MouseEvent;
	event.mouseEventType = ZGUI::ZEvent::MouseClick;
	event.click.location.x = 600.f;
	event.click.location.y = 400.f;
	event.click.mousebutton = 1;

	window->interact(event);

	std::cout << "Press any key to exit.\n";
	_getch();
	zInterface.destory();
	return 0;
}
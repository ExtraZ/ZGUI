#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "ZWindow.h"

namespace ZGUI
{
	class ZInterface
	{
	public:
		ZInterface();
		virtual ~ZInterface();

		ZObject& createWindow(std::string name);
		;
		ZWindow* getWindow(std::string name);

		void updateFocus(ZWindow* focused_window);

		void draw();
		void destory();
		void interact(ZEvent event);

		ZWindow& operator[](unsigned int index)
		{
			if (windows.size() > index)
				return *windows[index];
			throw std::exception("Object out of bound");
			return *windows[0];
		}

		ZWindow& operator[](std::string name)
		{
			for (auto& window : windows)
				if (window->getName() == name)
					return *window;
			throw std::exception("No object with corresponding name found");
			return *windows[0];
		}
		
	protected:
		std::vector < ZWindow* > windows;

	private:

	};
};
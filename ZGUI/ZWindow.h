#pragma once 

#include <vector>
#include <string>

#include "ZPanel.h"

namespace ZGUI
{
	class ZWindow : public ZObject
	{
	public:
		ZWindow();
		ZWindow(std::string);
		~ZWindow();
		
		void move(float x, float y);
		void resize(float width, float height);
		void draw();

		std::string getName() { return this->name; }
		void		setParent(void* parent)
		{
			this->parent = parent;
			this->tabpadding = "\t";
		}

		void		setHighestFocus();
		

		short focuslevel;

		void* parent;

	protected:
		
	private:

	};
};
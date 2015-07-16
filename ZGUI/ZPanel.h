#pragma once

#include "ZObject.h"

namespace ZGUI 
{
	class ZPanel : public ZObject
	{
	public:
		ZPanel();
		ZPanel(std::string name);
		virtual ~ZPanel();

		void draw();

	protected:

	private:
	};
};
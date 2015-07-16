#pragma once 

namespace ZGUI
{
	struct ZWindowConsts
	{
		static const float DEFAULT_HEADER_HEIGHT;
	};

	struct StateSpace
	{
		StateSpace(float x, float y, float width, float height) :
			x(x), y(y), width(width), height(height) {}
		float x, y;
		float width, height;
	};
}
#pragma once
#include "Component/Component.h"

namespace henry
{
	class Renderer;
	class GraphicsComponent : public Component
	{
	public:
		virtual void Draw(Renderer* renderer) = 0;

	};
}
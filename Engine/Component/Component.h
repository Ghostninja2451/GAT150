#pragma once
#include"Object/Object.h"

namespace henry
{
	class Actor;

	class Component : public Object
	{
	public:
		virtual void Update() = 0;

	public:
		Actor* owner{ nullptr };
		
	};
}
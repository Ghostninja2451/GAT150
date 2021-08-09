#pragma once
//#include"Graphics/ParticleSystem.h"
//#include"AudioSystem/AudioSystem.h"

//core
#include"Core/FileSystem.h"
#include "Core/Timer.h"

//Math
#include"Math/Vector2.h"
#include"Math/Color.h"
#include"Math/Random.h"
#include"Math/MathUtils.h"
#include"Math/Transform.h"

//#include"Graphics/Shape.h"

#include"Object/Actor.h"
#include"Object/Scene.h"

//inputsystem
#include"Input/InputSystem.h"

//Graphic
#include"Graphics/Renderer.h"
#include"Graphics/Texture.h"

//framework
#include"FrameWork/EventSystem.h"

//resource
#include "Resource/ResourceSystem.h"

#define NOMINMAX

#include <vector>
#include <memory>
#include<algorithm>


namespace henry
{
	class Engine
	{
	public:
		void Startup();
		void Shutdown();

		void Update();
		void Draw();

		template<typename T>
		T* Get();

	public:
		FrameTimer time;

	private:
		std::vector<std::unique_ptr<System>> systems;

	};

	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems)
		{
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}
		
		return nullptr;
	}
}
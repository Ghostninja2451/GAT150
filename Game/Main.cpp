#include"Engine.h"
#include<SDL.h>
#include<SDL_image.h>
#include <iostream>

int main(int, char**)
{

	henry::Engine engine;
	engine.Startup();

	henry::Scene scene;
	scene.engine = &engine;


	engine.Get<henry::Renderer>()->Create("GAT150", 800, 600);
	std::cout << henry::GetFilePath() << std::endl;
	henry::SetFilePath("../Resources");
	std::cout << henry::GetFilePath() << std::endl;

	std::shared_ptr<henry::Texture> texture = engine.Get<henry::ResourceSystem>()->Get<henry::Texture>("HenryStickmen.png", engine.Get<henry::Renderer>());
	//std::shared_ptr<henry::Texture> texture = engine.Get<henry::ResourceSystem>()->Get<henry::Texture>("sf2.png", engine.Get<henry::Renderer>());

	for (size_t i = 0; i < 10; i++)
	{
		henry::Transform transform{ {henry::RandomRange(0,800), henry::RandomRange(0 ,600)}, henry::RandomRange(0, 360), 0.1f };
		std::unique_ptr<henry::Actor> actor = std::make_unique<henry::Actor>(transform, texture);
		scene.AddActor(std::move(actor));

	}

	bool quit = false;
	SDL_Event event;
	float quitTime = engine.time.time + 3.0f;

	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		//update
		engine.Update();
		quit = (engine.Get<henry::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == henry::InputSystem::eKeyState::Pressed);
		scene.Update(engine.time.deltaTime);

		if (engine.time.time >= quitTime) quit = true;
		engine.time.timeScale = 2;

		//draw
		engine.Get<henry::Renderer>()->BeginFrame();
		scene.Draw(engine.Get<henry::Renderer>());
		engine.Get<henry::Renderer>()->EndFrame();

	}
		
	SDL_Quit();

	return 0;
}
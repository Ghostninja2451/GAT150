#include"Game.h"

int main(int, char**)
{
		
	Game game;
	game.Initialize();


	bool quit = false;
	SDL_Event event;
	//float quitTime = engine.time.time + 3.0f;


	while (!quit && !game.IsQuit())
	{
		//quit = (game.engine->Get<henry::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == henry::InputSystem::eKeyState::Pressed);
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		//draw

		game.Update();
		game.Draw();
	}

	SDL_Quit();

	return 0;
}
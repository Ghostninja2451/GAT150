#include "Game.h"

void Game::Initialize()
{
	// create engine

	engine = std::make_unique<henry::Engine>();
	engine->Startup();
	engine->Get<henry::Renderer>()->Create("GAT150", 800, 600);
	//create scene

	scene = std::make_unique<henry::Scene>();
	scene->engine = engine.get();
	henry::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	henry::SetFilePath("../Resources");


	std::unique_ptr<henry::Actor> actor = std::make_unique<henry::Actor>(henry::Transform{ {400 , 300},0 , 1 });
	{
		std::unique_ptr<henry::SpriteComponent> component = std::make_unique<henry::SpriteComponent>();
		component->texture = engine->Get<henry::ResourceSystem>()->Get<henry::Texture>("HenryStickmen.png", engine->Get<henry::Renderer>());
		actor->AddComponent(std::move(component));
	}
	{
		std::unique_ptr<henry::PhysicsComponent> component = std::make_unique<henry::PhysicsComponent>();
		component->ApplyForce(henry::Vector2::right * 200);
		actor->AddComponent(std::move(component));
	}

		scene->AddActor(std::move(actor));
	}

void Game::Shutdown()
{
	scene->RemoveAllActor();
	engine->Shutdown();
}

void Game::Update()
{
	engine->Update();
	
	quit = (engine->Get<henry::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == henry::InputSystem::eKeyState::Pressed);
	
	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	engine->Get<henry::Renderer>()->BeginFrame();

	engine->Draw(engine->Get<henry::Renderer>());
	scene->Draw(engine->Get<henry::Renderer>());

	engine->Get<henry::Renderer>()->EndFrame();
}


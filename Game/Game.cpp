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
	
	rapidjson::Document document;
	bool success = henry::json::Load("scene.txt", document);
	assert(success);

	scene->Read(document);

	//std::unique_ptr<henry::Actor> actor = std::make_unique<henry::Actor>(henry::Transform{ {400 , 300},0 , 1 });
	//{
	//	auto component = henry::ObjectFactory::Instance().Create<henry::SpriteAnimationComponent>("SpriteAnimationComponent");

	//	component->texture = engine->Get<henry::ResourceSystem>()->Get<henry::Texture>("Images/Wisp.png", engine->Get<henry::Renderer>());
	//	//henry::SpriteAnimationComponent* component = actor->AddComponent<henry::SpriteAnimationComponent>();
	//	component->fps = 12; //<number of frames to display per second(animation is typically 12 - 30)>;
	//	component->numFramesX = 8; //<number of images horizontally>;
	//	component->numFramesY = 8; //<number of images vertically>;
	//	actor->AddComponent(std::move(component));
	//}
	//{
	//	henry::SpriteComponent* component = actor->AddComponent<henry::SpriteComponent>();
	//	component->texture = engine->Get<henry::ResourceSystem>()->Get<henry::Texture>("Images/Link.png", engine->Get<henry::Renderer>());
	//}
	//{
	//	henry::PhysicsComponent* component = actor->AddComponent<henry::PhysicsComponent>();
	//	//component->ApplyForce(henry::Vector2::right * 200);
	//}
	//scene->AddActor(std::move(actor));

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


#include "Game.h"
#include "GameComponent/PlayerComponent.h"
#include "GameComponent/EnemyComponent.h"
#include "GameComponent/PickUpComponent.h"
void Game::Initialize()
{
	// create engine

	engine = std::make_unique<henry::Engine>();
	engine->Startup();
	engine->Get<henry::Renderer>()->Create("GAT150", 1000, 700);
	//create scene

	scene = std::make_unique<henry::Scene>();
	scene->engine = engine.get();
	henry::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	henry::SetFilePath("../Resources");

	// register classes
	REGISTER_CLASS(PlayerComponent);
	REGISTER_CLASS(EnemyComponent);
	REGISTER_CLASS(PickUpComponent);
	//Events
	engine->Get <henry::EventSystem>()->Subscribe("add_more", std::bind(&Game::OnAddScore, this, std::placeholders::_1));
	engine->Get <henry::EventSystem>()->Subscribe("lose_lives", std::bind(&Game::OnLooseLive, this, std::placeholders::_1));
	// Player Death

	engine->Get<henry::AudioSystem>()->AddAudio("music", "Audio/tropic.mp3");
	

	}

void Game::Shutdown()
{
	scene->RemoveAllActor();
	engine->Shutdown();
}

void Game::Update()
{
	engine->Update();
	
	if (engine->Get<henry::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == henry::InputSystem::eKeyState::Pressed)
	{
		quit = true;
	}
	
	switch (state)
	{
	case Game::eState::Reset:
		Reset();
		break;
	case Game::eState::Title:
		Title();
		break;
	case Game::eState::StartGame:
		StartGame();
		break;
	case Game::eState::StartLevel:
		StartLevel();
		break;
	case Game::eState::Level:
		Level();
		break;
	case Game::eState::PlayerDead:
		PlayerDead();
		break;
	case Game::eState::GameOver:
		GameOver();
		break;
	default:
		break;
	}

	//update score
	auto scoreActor = scene->FindActor("score");
	if (scoreActor)
	{
		scoreActor->GetComponent<henry::TextComponent>()->SetText(std::to_string(score));
	}
	auto liveActor = scene->FindActor("lives");
	if (scoreActor)
	{
		liveActor->GetComponent<henry::TextComponent>()->SetText(std::to_string(lives));
	}

	
	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	engine->Get<henry::Renderer>()->BeginFrame();

	engine->Draw(engine->Get<henry::Renderer>());
	scene->Draw(engine->Get<henry::Renderer>());

	engine->Get<henry::Renderer>()->EndFrame();
}

void Game::Reset()
{
	score = 0;
	lives = 3;
	enemyTimer = 0;
	scene->RemoveAllActor();

	rapidjson::Document document;
	bool success = henry::json::Load("Title.txt", document);
	assert(success);

	scene->Read(document);

	audioChannel.Stop();
	audioChannel = engine->Get<henry::AudioSystem>()->PlayAudio("music");

	state = eState::Title;
}

void Game::Title()
{
	if (engine->Get<henry::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == henry::InputSystem::eKeyState::Pressed)
	{
		auto title = scene->FindActor("title");
		assert(title);
		title->destroy = true;

		state = eState::StartGame;
	}
}

void Game::StartGame()
{
	rapidjson::Document document;
	bool success = henry::json::Load("scene.txt", document);
	assert(success);

	scene->Read(document);
	henry::TileMap tilemape;
	tilemape.scene = scene.get();
	success = henry::json::Load("Map.txt", document);
	assert(success);
	tilemape.Read(document);
	tilemape.Create();

	state = eState::StartLevel;
	stateTimer = 0;
}

void Game::StartLevel()
{
	stateTimer += engine->time.deltaTime;
	if (stateTimer >= 1)
	{
		auto player = henry::ObjectFactory::Instance().Create<henry::Actor>("Henry");
		player->transform.position = henry::Vector2{ 500, 400 };
		scene->AddActor(std::move(player));
		
		spawnTimer = 2;
		state = eState::Level;
	}
}

void Game::Level()
{
	spawnTimer -= engine->time.deltaTime;
	if (spawnTimer <= 0)
	{
		spawnTimer = henry::RandomRange(1, 4);

		auto coin = henry::ObjectFactory::Instance().Create<henry::Actor>("coins");
		coin->transform.position = henry::Vector2{ henry::RandomRange(100.0f, 800.0f), 300.0f };
		scene->AddActor(std::move(coin));
	}

	enemyTimer -= engine->time.deltaTime;
	if (enemyTimer <= 0)
	{
		enemyTimer = 10;

		auto bats = henry::ObjectFactory::Instance().Create<henry::Actor>("Bats");
		bats->transform.position = henry::Vector2{ henry::RandomRange(100.0f, 800.0f), 100.0f };
		scene->AddActor(std::move(bats));
	}
}

void Game::PlayerDead()
{
	if (lives == 0)
	{
		state = eState::GameOver;
	}
	else
	{
		spawnTimer -= engine->time.deltaTime;
		if (spawnTimer <= 0)
		{
			state = eState::StartLevel;
		}
	}
}

void Game::GameOver()
{
	
	rapidjson::Document document;
	bool success = henry::json::Load("GameOver.txt", document);
	assert(success);

	scene->Read(document);

	if (engine->Get<henry::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == henry::InputSystem::eKeyState::Pressed)
	{

		state = eState::Reset;
	}

}

void Game::OnAddScore(const henry::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnLooseLive(const henry::Event& event)
{
	lives += std::get<int>(event.data);

	stateTimer = 1;
	state = eState::PlayerDead;
}


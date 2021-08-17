#include "Game.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Enemy2.h"


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

	std::cout << henry::GetFilePath() << std::endl;

	engine->Get<henry::AudioSystem>()->AddAudio("explosion", "Audio/explosion.wav");
	engine->Get<henry::AudioSystem>()->AddAudio("music", "Audio/Music.mp3");
	musicChannel = engine->Get<henry::AudioSystem>()->PlayAudio("music", 1.0f, 1.0f, true);
	std::cout << henry::GetFilePath() << std::endl;

	//std::shared_ptr<henry::Texture> texture = engine->Get<henry::ResourceSystem>()->Get<henry::Texture>("sf2.png", engine.Get<henry::Renderer>());
	//std::shared_ptr<henry::Texture> texture = engine->Get<henry::ResourceSystem>()->Get<henry::Texture>("HenryStickmen.png", engine->Get<henry::Renderer>());
	//std::shared_ptr<henry::Texture> player = engine->Get<henry::ResourceSystem>()->Get<henry::Texture>("Images/Player.png", engine->Get<henry::Renderer>());
	//particleTexture = engine->Get<henry::ResourceSystem>()->Get<henry::Texture>("Explosion.png", engine->Get<henry::Renderer>());
	backgroundTexture = engine->Get<henry::ResourceSystem>()->Get<henry::Texture>("Images/Background.jpg", engine->Get<henry::Renderer>());

	//font

	int size = 25;
	std::shared_ptr<henry::Font> font = engine->Get<henry::ResourceSystem>()->Get<henry::Font>("Fonts/ITCBLKAD.TTF", &size);

	textTexture = std::make_shared<henry::Texture>(engine->Get<henry::Renderer>());

	//textTexture->Create(font->CreateSurface("hello world", henry::Color{ 0, 1, 1 }));

	engine->Get<henry::ResourceSystem>()->Add("textTexture", textTexture);


	//for (size_t i = 0; i < 10; i++)
	//{
	//	henry::Transform transform{ {henry::RandomRange(0,800), henry::RandomRange(0 ,600)}, henry::RandomRange(0, 360), 0.1f };
	//	std::unique_ptr<henry::Actor> actor = std::make_unique<henry::Actor>(transform, texture);
	//	scene->AddActor(std::move(actor));
	//}

	//gameplay
	engine->Get<henry::AudioSystem>()->AddAudio("player_fire", "Audio/PlayerShots.wav");
	engine->Get<henry::AudioSystem>()->AddAudio("player_explosion", "Audio/PlayerExlosion.wav");
	engine->Get<henry::AudioSystem>()->AddAudio("enemy_fire", "Audio/EnemyShot.wav");
	engine->Get<henry::AudioSystem>()->AddAudio("enemyexplosion", "Audio/EnemyExplosion.wav");

	engine->Get<henry::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<henry::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
}

void Game::Shutdown()
{
	scene->RemoveAllActor();
	engine->Shutdown();
}

void Game::Update()
{
	engine->Update();
	float dt = engine->time.deltaTime;
	stateTimer += dt;

	//(this->*stateFunction)(dt);

	switch (state)
	{
	case Game::eState::TitleScreen:
		if (engine->Get<henry::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == henry::InputSystem::eKeyState::Pressed)
		{
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		scene->AddActor(std::make_unique<Player>(henry::Transform{ henry::Vector2{300, 300}, 0, 0.3f }, engine->Get<henry::ResourceSystem>()->Get<henry::Texture>("Images/Player.png" , engine->Get<henry::Renderer>()), 500.0f));
		score = 0;
		lives = 5;
		rounds = 1;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
		UpdateLevelStart(dt);
		state = eState::Game;

		break;
	case Game::eState::Game:
		
		if (scene->GetActors<Enemy>().size() == 0 && scene->GetActors<Enemy2>().size() == 0)
		{
			rounds++;
			state = eState::StartLevel;
		}

		if (lives == 0)
		{
			state = eState::Gameover;
		}
		break;
	case Game::eState::Gameover:
		scene->RemoveAllActor();
		if (engine->Get<henry::InputSystem>()->GetKeyState(SDL_SCANCODE_LSHIFT) == henry::InputSystem::eKeyState::Pressed)
		{
			state = eState::TitleScreen;
		}
		break;
	default:
		break;
	}

	//update

	//if (engine->Get<henry::InputSystem>()->GetButtonState((int)henry::InputSystem::eMouseButton::Left) == henry::InputSystem::eKeyState::Pressed)
	//{
	//	henry::Vector2 position = engine->Get<henry::InputSystem>()->GetMousePosition();
	//	//create particles
	// engine->Get<henry::ParticleSystem>()->Create({ position.x, position.y }, 10, 2, particleTexture, 50);
	//	engine->Get<henry::AudioSystem>()->PlayAudio("explosion", 1, henry::RandomRange(-2.0f, 6.0f));
	//	musicChannel.SetPitch(henry::RandomRange(0.2f, 2.0f));

	//}
	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	int size = 25;
	std::shared_ptr<henry::Font> font = engine->Get<henry::ResourceSystem>()->Get<henry::Font>("Fonts/ITCBLKAD.TTF", &size);

	textTexture = std::make_shared<henry::Texture>(engine->Get<henry::Renderer>());
	engine->Get<henry::Renderer>()->BeginFrame();

	henry::Transform transform{ henry::Vector2{433,400}, 0, 0.7f };
	engine->Get<henry::Renderer>()->Draw(backgroundTexture, transform);
	henry::Transform t;
	switch (state)
	{
	case Game::eState::TitleScreen:
		t.position = { 400, 200 };
		textTexture->Create(font->CreateSurface("ELS invasion Press Space to Start", henry::Color{ 0, 1, 1 }));
		engine->Get<henry::Renderer>()->Draw(textTexture, t);
		t.position = { 400, 250 };
		textTexture->Create(font->CreateSurface("WASD to move", henry::Color{ 0, 1, 1 }));
		engine->Get<henry::Renderer>()->Draw(textTexture, t);
		t.position = { 400, 300 };
		textTexture->Create(font->CreateSurface("Space bar to shoot", henry::Color{ 0, 1, 1 }));
		engine->Get<henry::Renderer>()->Draw(textTexture, t);


		break;
	case Game::eState::StartGame:
		
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		t.position = { 30, 20};
		textTexture->Create(font->CreateSurface(std::to_string(lives).c_str(), henry::Color::white));
		engine->Get<henry::Renderer>()->Draw(textTexture, t);
		t.position = { 30, 40 };
		textTexture->Create(font->CreateSurface(std::to_string(score).c_str(), henry::Color::white));
		engine->Get<henry::Renderer>()->Draw(textTexture, t);
		t.position = { 30, 60 };
		textTexture->Create(font->CreateSurface(std::to_string(rounds).c_str(), henry::Color::white));
		engine->Get<henry::Renderer>()->Draw(textTexture, t);
		break;
	case Game::eState::Gameover:
		t.position = { 400, 200 };
		textTexture->Create(font->CreateSurface("Game Over", henry::Color::red));
		engine->Get<henry::Renderer>()->Draw(textTexture, t);
		t.position = { 400, 250 };
		textTexture->Create(font->CreateSurface("Hit Left shift to main menu", henry::Color::red));
		engine->Get<henry::Renderer>()->Draw(textTexture, t);
		break;
	default:
		break;
	}
	//textTexture->Create(font->CreateSurface(, henry::Color::green));
	/*graphics.SetColor(henry::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(750, 20, std::to_string(lives).c_str());
	graphics.DrawString(750, 40, std::to_string(rounds).c_str());*/
	//draw

	
	engine->Draw(engine->Get<henry::Renderer>());
	scene->Draw(engine->Get<henry::Renderer>());



	engine->Get<henry::Renderer>()->EndFrame();
}
void Game::UpdateTitle(float dt)
{
	//if (Core::Input::IsPressed(VK_SPACE))
	//{
	//	stateFunction = &Game::UpdateLevelStart;

	//	//state = eState::StartGame;
	//}
}

void Game::UpdateLevelStart(float dt)
{

	for (size_t i = 0; i < henry::RandomRange(2.0f , 7.0f); i++)
	{
		scene->AddActor(std::make_unique <Enemy>(henry::Transform{ henry::Vector2{ henry::RandomRange(0.0f,800.0f), henry::RandomRange(100.0f,600)}, henry::RandomRange(0, henry::TwoPi), 0.2f }, engine->Get<henry::ResourceSystem>()->Get<henry::Texture>("Images/Shootie.PNG", scene->engine->Get<henry::Renderer>()), 100.0f));
	}
	for (size_t i = 0; i < henry::RandomRange(2.0f, 6.0f); i++)
	{
		scene->AddActor(std::make_unique <Enemy2>(henry::Transform{ henry::Vector2{ henry::RandomRange(0.0f,800.0f), henry::RandomRange(100.0f,600)}, henry::RandomRange(0, henry::TwoPi), 0.2f }, engine->Get<henry::ResourceSystem>()->Get<henry::Texture>("Images/Kamakazi.PNG", scene->engine->Get<henry::Renderer>()), 100.0f));
	
	}
	state = eState::Game;
	
}

void Game::OnAddPoints(const henry::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerDead(const henry::Event& event)
{
	lives--;
	std::cout << std::get<std::string>(event.data) << std::endl;
	if (lives != 0)
	{
		scene->AddActor(std::make_unique<Player>(henry::Transform{ henry::Vector2{300, 300}, 0, 0.3f }, engine->Get<henry::ResourceSystem>()->Get<henry::Texture>("Images/Player.png", engine->Get<henry::Renderer>()), 500.0f));
	}
	else
	{
		state = eState::Gameover;

	}
}

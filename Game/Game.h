#pragma once
#include"Engine.h"


class Game
{
public:
	enum class eState
	{
		Reset,
		Title,
		StartGame,
		StartLevel,
		Level,
		PlayerDead,
		GameOver
	};
public :
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	bool IsQuit() { return quit; }

private:
	void Reset();
	void Title();
	void StartGame();
	void StartLevel();
	void Level();
	void PlayerDead();
	void GameOver();

	void OnAddScore(const henry::Event& event);
	void OnLooseLive(const henry::Event& event);

public:
	std::unique_ptr<henry::Engine> engine;
	std::unique_ptr<henry::Scene> scene;


private:
	bool quit = false;

	henry::AudioChannel audioChannel;

	eState state = eState::Reset;
	float stateTimer = 0;
	float spawnTimer = 0;
	float enemyTimer = 0;
	int score = 0;
	int lives = 3;
	
};


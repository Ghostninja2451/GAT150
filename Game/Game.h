#pragma once
#include"Engine.h"


class Game
{
public:
	enum class eState
	{
		TitleScreen,
		StartGame,
		StartLevel,
		Game,
		Gameover,
	};

public :
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	bool IsQuit() { return quit; }

private:
	void UpdateTitle(float dt);
	void UpdateLevelStart(float dt);

	void OnAddPoints(const henry::Event& event);
	void OnPlayerDead(const henry::Event& event);
	
public:
	std::unique_ptr<henry::Engine> engine;
	std::unique_ptr<henry::Scene> scene;


private:
	bool quit = false;
	eState state = eState::TitleScreen; 
	float stateTimer = 0.0f;

	size_t score = 0;	
	size_t lives = 0;
	size_t rounds = 0;

	henry::AudioChannel musicChannel;
	std::shared_ptr<henry::Texture> particleTexture;
	std::shared_ptr<henry::Texture> textTexture;

};

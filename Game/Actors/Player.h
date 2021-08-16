#pragma once
#include"Object/Actor.h"

class Player : public henry::Actor
{
public:
	Player(const henry::Transform& transform, std::shared_ptr<henry::Texture> texture, float speed);

	void Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float speed = 500;
	float fireRate = 0.1f;
	float fireTimer = 0.0f;

	henry::Vector2 velocity;
};
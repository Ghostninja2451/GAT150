#pragma once
#include"Object/Actor.h"


class Enemy : public henry::Actor
{
public:
	Enemy(const henry::Transform& transform, std::shared_ptr<henry::Texture> texture, float speed) : henry::Actor{transform , texture}, speed{speed}  {}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float speed = 300;
	float fireTimer{ 1.5f };
	float fireRate{ 1.3f };
};
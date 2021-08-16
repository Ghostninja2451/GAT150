#pragma once
#include"Object/Actor.h"

class Projectile : public henry::Actor
{
public:
	Projectile(const henry::Transform& transform, std::shared_ptr<henry::Texture> texture, float speed) : henry::Actor{ transform , texture }, speed{ speed }  {}

	void Update(float dt) override;

private:
	float lifetime{ 1 };
	float speed = 300;
};

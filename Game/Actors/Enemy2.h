#pragma once
#include"Object/Actor.h"


class Enemy2 : public henry::Actor
{
public:
	Enemy2(const henry::Transform& transform, std::shared_ptr<henry::Texture> texture, float speed) : henry::Actor{ transform , texture }, speed{ speed }  {}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float speed = 300;

};
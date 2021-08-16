#include"Projectile.h"
#include"Math/MathUtils.h"
#include"Engine.h"

void Projectile::Update(float dt)
{
	Actor::Update(dt);

	lifetime -= dt;
	if (lifetime <= 0) 
	{
		destroy = true;
	}

	transform.position += henry::Vector2::Rotate(henry::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = henry::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = henry::Wrap(transform.position.y, 0.0f, 600.0f);

	//std::vector<henry::Color> colors = { henry::Color::white, henry::Color::red, henry::Color::green, henry::Color::blue, henry::Color::yellow };
	//scene->engine->Get<henry::ParticleSystem>()->Create(transform.position, 10, 0.5f, colors[henry::RandomRangeInt(0, colors.size())], 10);
}
#include "Enemy2.h"
#include"Projectile.h"
#include"Player.h"
#include"Engine.h"

void Enemy2::Update(float dt)
{
	Actor::Update(dt);

	if (scene->GetActor<Player>())
	{
		henry::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
		henry::Vector2 forward = henry::Vector2::Rotate(henry::Vector2::right, transform.rotation);

		float angle = henry::Vector2::Angle(forward, direction.Normalized());

		//transform.rotation = direction.Angle();
	}

	transform.position += henry::Vector2::Rotate(henry::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = henry::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = henry::Wrap(transform.position.y, 0.0f, 600.0f);

}
void Enemy2::OnCollision(Actor * actor)
{
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")
	{
			destroy = true;
			actor->destroy = true;

			scene->engine->Get<henry::AudioSystem>()->PlayAudio("enemyexplosion");
			std::vector<henry::Color> colors = { henry::Color::white, henry::Color::red, henry::Color::green, henry::Color::blue, henry::Color::yellow };
			//scene->engine->Get<henry::ParticleSystem>()->Create(transform.position, 200, 1, henry::Color::red, 50);
			scene->engine->Get<henry::ParticleSystem>()->Create(transform.position, 10, 1, scene->engine->Get<henry::ResourceSystem>()->Get<henry::Texture>("Images/EnemyExplosion.png", scene->engine->Get<henry::Renderer>()), 50);


			henry::Event event;
			event.name = "AddPoints";
			event.data = 300;
			scene->engine->Get<henry::EventSystem>()->Notify(event);
	}
}
#include "Enemy.h"
#include"Projectile.h"
#include"Player.h"
#include"Engine.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt); 

	if (scene->GetActor<Player>())
	{
		henry::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
		henry::Vector2 forward = henry::Vector2::Rotate(henry::Vector2::right, transform.rotation);

		float turnAngle = henry::Vector2::SignedAngle(forward, direction.Normalized());
		transform.rotation = transform.rotation + turnAngle * (3 * dt);
		//transform.rotation = henry::Lerp(transform.rotation, transform.rotation + turnAngle, direction.Angle(), 2 * dt);

		float angle = henry::Vector2::Angle(forward, direction.Normalized());

		fireTimer -= dt;
		if (fireTimer <= 0 && angle <= henry::DegToRad(10))
		{
			fireTimer = fireRate;

			std::vector<henry::Vector2> points = { {-5,-5}, {5,-5}, {0,10}, {-5,-5} };
			//std::shared_ptr <henry::Texture> shape1 = std::make_shared<henry::Texture>(points, henry::Color{ 0 , 1 ,0 });

			henry::Transform t = transform;
			t.scale = 1.0f;
			std::unique_ptr<Projectile> projectile = std::make_unique <Projectile>(t, scene->engine->Get<henry::ResourceSystem>()->Get<henry::Texture>("Images/Enemymissile.png", scene->engine->Get<henry::Renderer>()), 600.0f);
			projectile->tag = "Enemy";
			scene->AddActor(std::move(projectile));
			scene->engine->Get<henry::AudioSystem>()->PlayAudio("enemy_fire");

		}


		//transform.rotation = direction.Angle();
	}

	transform.position += henry::Vector2::Rotate(henry::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = henry::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = henry::Wrap(transform.position.y, 0.0f, 600.0f);
}

void Enemy::OnCollision(Actor* actor)
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


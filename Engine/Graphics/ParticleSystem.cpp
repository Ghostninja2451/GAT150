#include"ParticleSystem.h"
#include"Renderer.h"
#include"Math/Random.h"

namespace henry
{
	
	void ParticleSystem::Startup()
	{
		particle.resize(1000);
	}

	void ParticleSystem::Shutdown()
	{
		particle.clear();
	}
	
	void ParticleSystem::Update(float dt)
	{
		for (Particle& particle : particle)
		{
			if (particle.isActive)
			{
				particle.lifetime -= dt;
				particle.isActive = particle.lifetime > 0;
				particle.prevPosition = particle.position;
				particle.position += particle.velocity * dt;
				
			}
		}


	}
	
	void ParticleSystem::Draw(Renderer* renderer)
	{
		for (const Particle& particle : particle)
		{
			if (particle.isActive)
			{
				renderer->Draw(particle.texture, particle.position);
			}
		}
	}
	
	void ParticleSystem::Create(Vector2 position, size_t count, float lifetime, std::shared_ptr<Texture> texture, float speed)
	{
		for (size_t i = 0; i < count; i++)
		{
			auto particles = std::find_if(particle.begin(), particle.end(), Particle::IsNotActive);
			if (particles != particle.end())
			{
				particles->isActive = true;
				particles->lifetime = lifetime;
				particles->position = position;
				particles->prevPosition = position;
				particles->texture = texture;

				particles->velocity = Vector2{ RandomRange( -1, 1 ), RandomRange( -1, 1 ) } * (speed * Random());
			}
		}
	}
	void ParticleSystem::Create(Vector2 position, size_t count, float lifetime, std::shared_ptr<Texture> texture, float speed, float angle, float angleRange)
	{
		for (size_t i = 0; i < count; i++)
		{
			auto particles = std::find_if(particle.begin(), particle.end(), Particle::IsNotActive);
			if (particles != particle.end())
			{
				particles->isActive = true;
				particles->lifetime = lifetime;
				particles->position = position;
				particles->prevPosition = position;
				particles->texture = texture;

				particles->velocity = henry::Vector2::Rotate(henry::Vector2::right, angle + henry::RandomRange(-angleRange, angleRange)) * (speed * Random());
			}
		}
	}
}
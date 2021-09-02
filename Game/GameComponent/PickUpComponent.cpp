#include "PickUpComponent.h"
#include"Engine.h"

using namespace henry;

	void PickUpComponent::Create()
	{
		owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&PickUpComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
		owner->scene->engine->Get<EventSystem>()->Subscribe("collision_exit", std::bind(&PickUpComponent::OnCollisionExit, this, std::placeholders::_1), owner);

		owner->scene->engine->Get<AudioSystem>()->AddAudio("coins", "Audio/coin.wav");
	}

	void PickUpComponent::Update()
	{
		Vector2 force = Vector2::zero;

		PhysicsComponent* physicsComponent = owner->GetComponent<PhysicsComponent>();
		assert(physicsComponent);
		physicsComponent->ApplyForce(force);
	}

	PickUpComponent::~PickUpComponent()
	{
		owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
	}

	void PickUpComponent::OnCollisionEnter(const henry::Event& event)
	{
		void* p = std::get<void*>(event.data);
		Actor* actor = reinterpret_cast<Actor*>(p);

		if (istring_compare(actor->name, "Henry"))
		{
			owner->scene->engine->Get<AudioSystem>()->PlayAudio("coins");
			owner->destroy = true;

			Event event;
			event.name = "add_more";
			event.data = 10;
			
			owner->scene->engine->Get<EventSystem>()->Notify(event);
		}
	}

	void PickUpComponent::OnCollisionExit(const henry::Event& event)
	{

	}

	bool PickUpComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool PickUpComponent::Read(const rapidjson::Value& value)
	{
		return true;
	}


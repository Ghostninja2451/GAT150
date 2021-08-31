#pragma once
#include"Component/Component.h"
#include"Framework/EventSystem.h"


class PlayerComponent : public henry::Component
{
public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<PlayerComponent>(*this); }

	void Create() override;
	virtual void Update() override;

	~PlayerComponent();

	virtual void OnCollisionEnter(const henry::Event& event);
	virtual void OnCollisionExit(const henry::Event& event);

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

public:
	float speed{ 0 };

private:
	std::list<henry::Actor*> contacts;
};

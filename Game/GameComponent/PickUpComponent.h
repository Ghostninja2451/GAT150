#pragma once
#include "Component/Component.h"
#include "Framework/EventSystem.h"

	class PickUpComponent : public henry::Component
	{
	public:
		std::unique_ptr<Object> Clone() const { return std::make_unique<PickUpComponent>(*this); }

		void Create() override;

		void Update()override;

		~PickUpComponent();

		virtual void OnCollisionEnter(const henry::Event& event);
		virtual void OnCollisionExit(const henry::Event& event);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	};


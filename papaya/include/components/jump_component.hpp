// jump_component.hpp

#pragma once

#include "game/component.hpp"
#include "game/gameobject.hpp"
#include "components/transform_component.hpp"
#include "platform/debug.hpp"
#include "platform/time.hpp"

namespace papaya
{
	class JumpComponent : public ComponentBase
	{
	public:
		JumpComponent(GameObject *parent, const ComponentFamilyId id);
		~JumpComponent();

		void update(const Time &delta_time);
		void jump();

	private:
		Transform *transform_;

		bool is_jumping_, is_falling_, on_ground_;
		float ground_height_;
		float velocity_, gravity_;
		
	};
} // !papaya

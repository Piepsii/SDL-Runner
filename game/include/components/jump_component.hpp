// jump_component.hpp

#pragma once

#include "game/component.hpp"
#include "game/gameobject.hpp"
#include "components/transform_component.hpp"
#include "input/input.hpp"
#include "platform/debug.hpp"
#include "platform/time.hpp"

namespace papaya
{
	class JumpComponent : public ComponentBase
	{
	public:
		JumpComponent(GameObject *game_object, const ComponentFamilyId id);
		~JumpComponent();

		void update(const Time &delta_time);
		void handle_input(Input &input);
		void jump();

	private:
		Transform *transform_;

		bool is_jumping_, is_falling_, on_ground_;
		float ground_height_;
		float velocity_, gravity_, gravity_scaling_, thrust_;
		
	};
} // !papaya

// animation_component.hpp

#pragma once

#include "components/sprite_component.hpp"
#include "game/component.hpp"
#include "game/gameobject.hpp"
#include "scene/sprite.hpp"

namespace runner
{
	class AnimationComponent : public papaya::ComponentBase
	{
	public:
		AnimationComponent(papaya::GameObject *game_object, papaya::ComponentFamilyId id);
		~AnimationComponent();

		void update(const papaya::Time &delta_time);

	private:
		papaya::Sprite *sprite_;
		int counter_;
		const int animation_speed_;
	};

} // !runner

// sprite_component.hpp

#pragma once

#include "game/component.hpp"
#include "game/gameobject.hpp"
#include "components/transform_component.hpp"
#include "scene/sprite.hpp"
#include "scene/renderer.hpp"
#include "scene/transform.hpp"

namespace papaya
{
	class SpriteComponent : public ComponentBase
	{
	public:
		SpriteComponent(GameObject *game_object, const ComponentFamilyId id);
		~SpriteComponent();

		void update(const Time &delta_time);
		void render(Renderer &renderer);

		Sprite sprite_;

	};
} // !papaya
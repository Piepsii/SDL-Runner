// text_component.hpp

#pragma once

#include "game/component.hpp"

namespace runner
{
	class TextComponent : public papaya::ComponentBase
	{
	public:
		TextComponent(papaya::GameObject &game_object, papaya::ComponentFamilyId id);
		~TextComponent();

		void update(const papaya::Time &delta_time);
		void render(const papaya::Renderer &renderer);
	};
} // !runner

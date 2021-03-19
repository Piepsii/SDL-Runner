// text_component.hpp

#pragma once

#include "game/component.hpp"
#include "scene/sprite.hpp"

namespace runner
{
	class TextComponent : public papaya::ComponentBase
	{
	public:
		TextComponent(papaya::GameObject *game_object, papaya::ComponentFamilyId id);
		~TextComponent();

		void update(const papaya::Time &delta_time);
		void render(papaya::Renderer &renderer);

		void set_number(int number);
		void set_texture(const papaya::Texture *texture, int index);
		void set_digit_count(int digit_count);

	private:
		int number_;
		int digit_count_;
		int *digits_;
		papaya::Sprite *sprites_;
		const papaya::Texture **textures_;

		void calculate_digits();

	};
} // !runner

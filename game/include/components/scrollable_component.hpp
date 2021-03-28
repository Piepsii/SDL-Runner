// scrollable_component.hpp

#pragma once

#include <components/transform_component.hpp>
#include <components/sprite_component.hpp>
#include <game/component.hpp>
#include <platform/window.hpp>
#include <scene/transform.hpp>
#include <scene/sprite.hpp>

namespace runner
{
	class ScrollableComponent : public papaya::ComponentBase
	{
	public:
		static const papaya::Texture *transparent_texture_;
		static float scroll_speed_;

	public:
		ScrollableComponent(papaya::GameObject *game_object, const papaya::ComponentFamilyId id);
		~ScrollableComponent();

		void update(const papaya::Time &delta_time);
		void add_texture(const papaya::Texture *texture);
		void set_transparent();
		void set_speed_variance(float value);
		void set_is_changing_texture(bool value);

		int chance_of_spawning;

	private:
		papaya::Transform *transform_;
		papaya::Sprite *sprite_;

		class TextureNode
		{
		public:
			const papaya::Texture *texture_;
			TextureNode *next_;
		} *textures_;
		int texture_count_;
		float speed_variance_;

		bool is_scrolling_;
		bool is_changing_texture_;
	};
} // !runner

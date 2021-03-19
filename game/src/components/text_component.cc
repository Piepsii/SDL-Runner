// text_component.cc

#include "components/text_component.hpp"
#include "components/transform_component.hpp"
#include "graphics/texture.hpp"
#include "math/color.hpp"
#include "scene/renderer.hpp"
#include "scene/transform.hpp"
#include <cmath>

namespace runner
{
	TextComponent::TextComponent(papaya::GameObject *game_object, papaya::ComponentFamilyId id)
		: ComponentBase(game_object, id)
		, number_(0)
		, digit_count_(6)
		, digits_(new int[digit_count_])
		, sprites_(new papaya::Sprite[digit_count_])
		, textures_((const papaya::Texture**) malloc(sizeof(papaya::Texture *) * digit_count_))
	{
		calculate_digits();
		for( int i = 0; i < digit_count_; i++ )
		{
			sprites_[i].set_color(papaya::Color::White);
			sprites_[i].set_size(papaya::Vector2{ 32, 32 });
			sprites_[i].set_texcoord(papaya::Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
		}
	}

	TextComponent::~TextComponent()
	{
		delete digits_;
		delete sprites_;
		delete textures_;
	}

	void TextComponent::update(const papaya::Time &delta_time)
	{
	}

	void TextComponent::render(papaya::Renderer &renderer)
	{
		papaya::Transform transform = game_object_->get_component<papaya::TransformComponent>()->transform_;
		for( int i = 0; i < digit_count_; i++ )
		{
			transform.position_.x_ -= textures_[digits_[i]]->width();
			calculate_digits();
			renderer.draw(sprites_[i], transform);
		}
	}

	void TextComponent::calculate_digits()
	{
		for( int i = 0; i < digit_count_; i++ )
		{
			digits_[i] = number_ %static_cast<int>(pow(10, i + 1)) / static_cast<int>(pow(10, i));
			sprites_[i].set_texture(textures_[digits_[i]]);
		}
	}

	void TextComponent::set_number(int number)
	{
		number_ = number;
	}

	void TextComponent::set_texture(const papaya::Texture *texture, int index)
	{
		textures_[index] = texture;
	}

	void TextComponent::set_digit_count(int digit_count)
	{
		digit_count_ = digit_count;
	}

} // !runner

// scrollable_component.cc

#include <components/scrollable_component.hpp>
#include <stdlib.h>
#include <time.h>

namespace runner
{
	ScrollableComponent::ScrollableComponent(papaya::GameObject *game_object, const papaya::ComponentFamilyId id)
		: ComponentBase(game_object, id)
		, transform_(&game_object->get_component<papaya::TransformComponent>()->transform_)
		, sprite_(&game_object->get_component<papaya::SpriteComponent>()->sprite_)
		, texture_count_(0)
		, chance_of_spawning(100)
		, speed_variance_(0)
		, is_scrolling_(true)
		, is_changing_texture_(false)
	{
		textures_ = new TextureNode;
		textures_->texture_ = game_object->get_component<papaya::SpriteComponent>()->sprite_.get_texture();
		textures_->next_ = nullptr;
		texture_count_++;
	}

	float ScrollableComponent::scroll_speed_ = 1.0f;
	const papaya::Texture* ScrollableComponent::transparent_texture_ = nullptr;

	ScrollableComponent::~ScrollableComponent()
	{
		TextureNode *currentptr = textures_;
		TextureNode *tempptr = nullptr;
		while( currentptr->next_ != nullptr )
		{
			tempptr = currentptr;
			currentptr = currentptr->next_;
			delete tempptr;
		}
		tempptr = nullptr;
		currentptr = nullptr;
	}

	void ScrollableComponent::update(const papaya::Time &delta_time)
	{
		if( !is_scrolling_ )
			return;

		transform_->position_.x_ -= scroll_speed_ + speed_variance_;

		if( transform_->position_.x_ + sprite_->get_size().x_ < 0.0f )
		{
			int chance = rand() % 100 + 1;
			transform_->position_.x_ = static_cast<float>(papaya::Window::width_);
			if( !is_changing_texture_ )
			{
				return;
			}
			if( chance < chance_of_spawning )
			{

				int texture_index = rand() % texture_count_;
				const papaya::Texture *texture;
				if( textures_ == nullptr )
				{
					return;
				}
					TextureNode *currentptr = textures_;
				for( int i = 0; i < texture_index; i++ )
				{
					currentptr = currentptr->next_;
				}
				texture = currentptr->texture_;
				sprite_->set_texture(texture);
			}
			else
			{
				sprite_->set_texture(transparent_texture_);
			}
		}
	}

	void ScrollableComponent::add_texture(const papaya::Texture *texture)
	{
		TextureNode *currentptr = textures_;
		while( currentptr->next_ != nullptr )
		{
			currentptr = currentptr->next_;
		}
		currentptr->next_ = new TextureNode;
		currentptr->next_->texture_ = texture;
		currentptr->next_->next_ = nullptr;
		texture_count_++;
	}

	void ScrollableComponent::set_transparent()
	{
		sprite_->set_texture(transparent_texture_);
	}

	void ScrollableComponent::set_speed_variance(float value)
	{
		speed_variance_ = value;
	}

	void ScrollableComponent::set_is_changing_texture(bool value)
	{
		is_changing_texture_ = value;
	}


} // !runner

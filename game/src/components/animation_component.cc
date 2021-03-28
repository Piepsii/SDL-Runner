// animation_component.cc

#include "components/animation_component.hpp"

namespace runner
{
	AnimationComponent::AnimationComponent(papaya::GameObject *game_object, papaya::ComponentFamilyId id)
		: ComponentBase(game_object, id)
		, sprite_(nullptr)
		, counter_(0)
		, animation_speed_(30)
	{

	}

	AnimationComponent::~AnimationComponent()
	{

	}

	void AnimationComponent::update(const papaya::Time &delta_time)
	{
		if( sprite_ == nullptr )
		{
			sprite_ = &game_object_->get_component<papaya::SpriteComponent>()->sprite_;
		}


		if( counter_ < animation_speed_ / 4 )
		{
			sprite_->set_texcoord({ 0.0f, 0.0f, 0.25f, 1.0f });
		}
		else if(counter_ < (animation_speed_ / 2))
		{
			sprite_->set_texcoord({ 0.25f, 0.0f, 0.5f, 1.0f });
		}
		else if( counter_ < (animation_speed_ / 4) * 3 )
		{
			sprite_->set_texcoord({ 0.5f, 0.0f, 0.75f, 1.0f });
		}
		else if( counter_ < animation_speed_ )
		{
			sprite_->set_texcoord({ 0.75f, 0.0f, 1.0f, 1.0f });
		}
		counter_++;

		if( counter_ > animation_speed_ )
		{
			counter_ = 0;
		}
	}

} // !runner

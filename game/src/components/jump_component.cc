// jump_component.cc

#include "components\jump_component.hpp"

namespace runner
{
	JumpComponent::JumpComponent(papaya::GameObject *game_object, const papaya::ComponentFamilyId id)
		: ComponentBase(game_object, id)
		, transform_(&game_object->get_component<papaya::TransformComponent>()->transform_)
		, is_jumping_(false)
		, is_falling_(false)
		, on_ground_(true)
		, velocity_(0.0f)
		, gravity_(0.5f)
		, gravity_scaling_(25.0f)
		, thrust_(6.0f)
	{
		ground_height_ = transform_->position_.y_;
	}

	JumpComponent::~JumpComponent()
	{

	}

	void JumpComponent::update(const papaya::Time &delta_time)
	{
 		velocity_ = velocity_ - gravity_ * delta_time.as_seconds() * gravity_scaling_;
		transform_->position_.y_ -= velocity_;

		if( velocity_ > 0.0f )
		{
			on_ground_ = false;
		}
		else if( velocity_ < 0.0f )
		{
			is_jumping_ = false;
			is_falling_ = true;
		}

		if( transform_->position_.y_> ground_height_ )
		{
			is_falling_ = false;
			on_ground_ = true;
			velocity_ = 0.0f;
			transform_->position_.y_ = ground_height_;
		}
	}

	void JumpComponent::handle_input(papaya::Input &input)
	{
		if( input.keyboard().pressed(papaya::Key::Space) )
		{
			jump();
		}

	}

	void JumpComponent::jump()
	{
		if( on_ground_ )
		{
			is_jumping_ = true;
			velocity_ = thrust_;
		}
	}
} // !runner
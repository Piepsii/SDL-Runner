// jump_component.cc

#include "components\jump_component.hpp"

namespace papaya
{
	JumpComponent::JumpComponent(GameObject *parent, const ComponentFamilyId id)
		: ComponentBase(parent, id)
		, transform_(&parent_->get_component<TransformComponent>()->transform_)
		, is_jumping_(false)
		, is_falling_(false)
		, on_ground_(true)
	{
		ground_height_ = transform_->position_.y_;
		velocity_ = 0.0f;
		gravity_ = 0.5f;
	}

	JumpComponent::~JumpComponent()
	{

	}

	void JumpComponent::update(const Time &delta_time)
	{
 		velocity_ = velocity_ - gravity_ * delta_time.as_seconds() * 25;
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

	void JumpComponent::jump()
	{
		if( on_ground_ )
		{
			is_jumping_ = true;
			velocity_ = 5.0f;
		}
	}
} // !papaya
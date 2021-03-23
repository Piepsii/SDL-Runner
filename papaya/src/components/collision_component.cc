// collision_component.cc

#pragma once

#include "components/collision_component.hpp"

namespace papaya
{
	CollisionComponent::CollisionComponent(GameObject *game_object, ComponentFamilyId id)
		: ComponentBase(game_object, id)
		, transform_(&game_object->get_component<TransformComponent>()->transform_)
		, collision_shape_({ Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f) })
		, is_colliding_(false)
	{

	}

	CollisionComponent::~CollisionComponent()
	{

	}

	void CollisionComponent::update(const Time &delta_time)
	{
		collision_shape_.center_ = transform_->position_;

		GameObject *currentptr = game_object_->next_;
		while( currentptr != nullptr )
		{
			while( currentptr->get_component<CollisionComponent>() == nullptr)
			{
				currentptr = currentptr->next_;
			}

			is_colliding_ = intersect(currentptr->get_component<CollisionComponent>()->collision_shape());
			currentptr = currentptr->next_;
		}
	}

	bool CollisionComponent::intersect(AxisAlignedBoundingBox other)
	{
		return (other.center_.y_ + other.half_.y_ >= collision_shape_.center_.y_ - collision_shape_.half_.y_
				  && other.center_.x_ - other.half_.x_ <= collision_shape_.center_.x_ + collision_shape_.half_.x_
				  && other.center_.y_ - other.half_.y_ <= collision_shape_.center_.y_ + collision_shape_.half_.y_
				  && other.center_.x_ + other.half_.x_ >= collision_shape_.center_.x_ - collision_shape_.half_.x_);
	}

	AxisAlignedBoundingBox CollisionComponent::collision_shape()
	{
		return collision_shape_;
	}

	void CollisionComponent::set_collision_shape(Vector2 half)
	{
		collision_shape_.half_ = half;
	}

	bool CollisionComponent::is_colliding()
	{
		return is_colliding_;
	}

} // !papaya

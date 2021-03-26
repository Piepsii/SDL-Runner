// collision_component.cc

#pragma once

#include "components/collision_component.hpp"

namespace runner
{
	CollisionComponent::CollisionComponent(papaya::GameObject *game_object, papaya::ComponentFamilyId id)
		: ComponentBase(game_object, id)
		, transform_(&game_object->get_component<papaya::TransformComponent>()->transform_)
		, collision_shape_({ papaya::Vector2(0.0f, 0.0f), papaya::Vector2(0.0f, 0.0f) })
		, is_colliding_(false)
	{
		collision_sprite_.set_color(papaya::Color::White);
		collision_sprite_.set_size(collision_shape_.half_);
		collision_sprite_.set_texcoord(papaya::Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	}

	CollisionComponent::~CollisionComponent()
	{

	}

	void CollisionComponent::update(const papaya::Time &delta_time)
	{
		collision_shape_.center_ = transform_->position_;

		if( game_object_->has_component<papaya::SpriteComponent>() )
		{
			if( game_object_->get_component<papaya::SpriteComponent>()->sprite_.get_texture() == ScrollableComponent::transparent_texture_ )
			{
				is_colliding_ = false;
				return;
			}
		}

		papaya::GameObject *currentptr = game_object_->next_;
		while( currentptr != nullptr )
		{
			if( currentptr->has_component<CollisionComponent>())
			{
				is_colliding_ = intersect(currentptr->get_component<CollisionComponent>()->collision_shape());
			}
			currentptr = currentptr->next_;
		}


		collision_sprite_.set_size(collision_shape_.half_);
	}

	void CollisionComponent::render(papaya::Renderer &renderer)
	{
		// Debug: renderer.draw(collision_sprite_, *transform_);
	}

	bool CollisionComponent::intersect(papaya::AxisAlignedBoundingBox other)
	{
		return(other.center_.y_ <= collision_shape_.center_.y_ + collision_shape_.half_.y_
				 && other.center_.y_ + other.half_.y_ >= collision_shape_.center_.y_
				 && other.center_.x_ <= collision_shape_.center_.x_ + collision_shape_.half_.x_
				 && other.center_.x_ + other.half_.x_ >= collision_shape_.center_.x_);
	}

	papaya::AxisAlignedBoundingBox CollisionComponent::collision_shape()
	{
		return collision_shape_;
	}

	void CollisionComponent::set_collision_shape(papaya::Vector2 half)
	{
		collision_shape_.half_ = half;
	}

	bool CollisionComponent::is_colliding()
	{
		return is_colliding_;
	}

} // !runner

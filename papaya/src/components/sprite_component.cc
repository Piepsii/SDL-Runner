// sprite_component.cc

#include "components\sprite_component.hpp"

namespace papaya
{
	SpriteComponent::SpriteComponent(GameObject *game_object, const ComponentFamilyId id)
		: ComponentBase(game_object, id)
	{

	}

	SpriteComponent::~SpriteComponent()
	{

	}

	void SpriteComponent::update(const Time &delta_time)
	{
		
	}

	void SpriteComponent::render(Renderer &renderer)
	{
		Transform transform = game_object_->get_component<TransformComponent>()->transform_;
		renderer.draw(sprite_, transform);
	}

} // !papaya
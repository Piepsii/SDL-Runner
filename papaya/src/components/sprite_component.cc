// sprite_component.cc

#include "components\sprite_component.hpp"

namespace papaya
{
	SpriteComponent::SpriteComponent(GameObject *parent, const ComponentFamilyId id)
		: ComponentBase(parent, id)
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
		Transform transform = parent_->get_component<TransformComponent>()->transform_;
		renderer.draw(sprite_, transform);
	}

} // !papaya
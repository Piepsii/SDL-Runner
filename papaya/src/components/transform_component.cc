// transform_component.cc

#include "components\transform_component.hpp"
#include "components\sprite_component.hpp"
#include "platform/window.hpp"

namespace papaya
{
	TransformComponent::TransformComponent(GameObject *game_object, const ComponentFamilyId id)
		: ComponentBase(game_object, id)
	{
	}

	TransformComponent::~TransformComponent()
	{

	}

	void TransformComponent::update(const Time &delta_time)
	{
	}

	void TransformComponent::render(Renderer &renderer)
	{
	}

} // !papaya

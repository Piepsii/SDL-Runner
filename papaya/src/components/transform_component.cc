// transform_component.cc

#include "components\transform_component.hpp"

namespace papaya
{
	TransformComponent::TransformComponent(GameObject *parent, const ComponentFamilyId id)
		: ComponentBase(parent, id)
	{

	}

	TransformComponent::~TransformComponent()
	{

	}

	void TransformComponent::update(const Time &delta_time)
	{

	}

} // !papaya

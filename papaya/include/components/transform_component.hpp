// transform_component.hpp

#pragma once

#include "game/component.hpp"
#include "scene/transform.hpp"

namespace papaya
{
	class TransformComponent : public ComponentBase
	{
	public:
		TransformComponent(GameObject *parent, const ComponentFamilyId id);
		 ~TransformComponent();

		 void update(const Time &delta_time);

		Transform transform_;


	};
} // !papaya

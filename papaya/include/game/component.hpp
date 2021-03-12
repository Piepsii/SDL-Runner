// component.hpp

#pragma once

#include <game/component_registry.hpp>

namespace papaya {
   class Time;
   class Renderer;
   class GameObject;

   class ComponentBase {
   public:
      ComponentBase(GameObject *parent, const ComponentFamilyId id);
      virtual ~ComponentBase() = default;

      ComponentFamilyId id() const;

      virtual void update(const Time &deltatime);
      virtual void render(Renderer &renderer);

   protected:
      GameObject *parent_;
      ComponentFamilyId id_;
   };

   template <typename Derived>
   class Component : public ComponentBase {
   public:
      Component(GameObject *parent)
         : ComponentBase(parent, ComponentRegistry::family<Derived>())
      {
      }
   };
} // !papaya

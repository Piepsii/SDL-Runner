// component.hpp

#pragma once

#include <game/component_registry.hpp>

namespace papaya {
   class Time;
   class Renderer;
   class GameObject;
   class Input;

   class ComponentBase {
   public:
      ComponentBase(GameObject *game_object, const ComponentFamilyId id);
      virtual ~ComponentBase() = default;

      ComponentFamilyId id() const;

      virtual void update(const Time &deltatime);
      virtual void render(Renderer &renderer);
      virtual void handle_input(Input &input);

   protected:
      GameObject *game_object_;
      ComponentFamilyId id_;
   };

   template <typename Derived>
   class Component : public ComponentBase {
   public:
      Component(GameObject *game_object)
         : ComponentBase(game_object, ComponentRegistry::family<Derived>())
      {
      }
   };
} // !papaya

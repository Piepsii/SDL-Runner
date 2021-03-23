// gameobject.hpp

#pragma once

#include <vector>
#include <type_traits>
#include <game/component_registry.hpp>

namespace papaya {
   class Time;
   class Renderer;
   class ComponentBase;
   class Input;

   class GameObject {
   public:
      GameObject();
      GameObject(GameObject &game_object);
      ~GameObject();

      void update(const Time &deltatime);
      void render(Renderer &renderer);
      void handle_input(Input &input);

      template <typename ComponentType>
      bool has_component()
      {
         return (get_component<ComponentType>() != nullptr);
      }

      template <typename ComponentType>
      ComponentType *add_component()
      {
         static_assert(std::is_base_of<ComponentBase, ComponentType>::value,  
                       "ComponentType must inherit from ComponentBase");

         ComponentType *component = new ComponentType(this, ComponentRegistry::family<ComponentType>());
         components_.push_back(component);
         return component;
      }

      template <typename ComponentType>
      ComponentType *get_component()
      {
         const ComponentFamilyId id = ComponentRegistry::family<ComponentType>();
         for (auto &component : components_) { 
            if (component->id() == id) {
               return static_cast<ComponentType *>(component);
            }
         }

         return nullptr;
      }

    

      GameObject *next_;

   private:
      std::vector<ComponentBase *> components_;
   };
} // !papaya

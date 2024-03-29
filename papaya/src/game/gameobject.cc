// gameobject.cc

#include "components/transform_component.hpp"
#include "game/gameobject.hpp"
#include "game/component.hpp"

#include "platform/time.hpp"
#include "scene/renderer.hpp"

namespace papaya {
   GameObject::GameObject()
   {
      add_component<TransformComponent>();
   }

   GameObject::GameObject(GameObject &game_object)
   {
      components_ = game_object.components_;
   }

   GameObject::~GameObject()
   {
      for (auto &component : components_) {
         delete component;
      }
   }

   void GameObject::update(const Time &deltatime)
   {
      for (auto &component : components_) {
         component->update(deltatime);
      }
   }

   void GameObject::render(Renderer &renderer)
   {
      for (auto &component : components_) {
         component->render(renderer);
      }
   }

   void GameObject::handle_input(Input &input)
   {
      for( auto &component : components_ )
      {
         component->handle_input(input);
      }

   }
} // !papaya

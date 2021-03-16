// component.cc

#include "game/component.hpp"

namespace papaya {
   ComponentBase::ComponentBase(GameObject *parent, const ComponentFamilyId id)
      : game_object_(parent)
      , id_(id)
   {
   }

   ComponentFamilyId ComponentBase::id() const
   {
      return id_;
   }

   void ComponentBase::update(const Time &deltatime)
   {
   }

   void ComponentBase::render(Renderer &renderer)
   {
   }

   void ComponentBase::handle_input(Input &input)
   {
   }
} // !papaya

// component.cc

#include "game/component.hpp"

namespace papaya {
   ComponentBase::ComponentBase(GameObject *parent, const ComponentFamilyId id)
      : parent_(parent)
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
} // !papaya

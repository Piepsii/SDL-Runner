// component_registry.hpp

#pragma once

#include <type_traits>

namespace papaya {
   using ComponentFamilyId = unsigned int;

   class ComponentBase;

   class ComponentRegistry {
   public:
      template <typename ComponentType>
      static ComponentFamilyId family()
      {
         static_assert(std::is_base_of<ComponentBase, ComponentType>::value,
                       "ComponentType needs to inherit from ComponentBase");

         static const ComponentFamilyId id = next_++;
         return id;
      }

   private:
      static inline ComponentFamilyId next_ = 0;
   };
} // !papaya

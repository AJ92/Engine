#ifndef COMPOSITIONHELPER_H
#define COMPOSITIONHELPER_H

#include <vector>
#include <bitset>
#include <memory>
#include <array>

//#include "Object/component.h"

class Component;

using ComponentID = std::size_t;

namespace Internal
{
//return a unique ID !!!
inline ComponentID getUniqueComponentID()
{
    static ComponentID lastID{0u};
    return lastID++;
}
}

//return a unique ID for every Component TYPE!!!
template<typename T> inline ComponentID getComponentTypeID()
{
    static_assert(std::is_base_of<Component, T>::value,
                  "T must inherit from Component");

    static ComponentID typeID{Internal::getUniqueComponentID()};
    return typeID;
}

using Group = std::size_t;

constexpr std::size_t maxComponents{32};
using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

constexpr std::size_t maxGroups{32};
using GroupBitset = std::bitset<maxGroups>;



#endif // COMPOSITIONHELPER_H

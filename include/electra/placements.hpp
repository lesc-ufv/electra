// vim: set ts=2 sw=2 tw=0 et :
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : placements
// @created     : Saturday Aug 10, 2019 17:07:00 -03
// @license     : MIT
// @description : Electra - Field-Coupled Nanocomputing Data Structures
//

#pragma once
#include <map>
#include <utility>
#include <memory>
#include <optional>
#include <electra/area.hpp>

namespace electra::placement {

// Data types
template<typename T>
using PlacementIdData = std::map< std::pair<T,T>, T >;
template<typename T>
using IdPlacementData = std::map< T, std::pair<T,T> >;
template<typename T>
using const_iterator = typename PlacementIdData<T>::const_iterator;

// Dynamic memory storage
template<typename T>
using PlacementId = std::unique_ptr<PlacementIdData<T>>;
template<typename T>
using IdPlacement = std::unique_ptr<IdPlacementData<T>>;
template<typename T>
using Area = std::unique_ptr<electra::area::Area<T>>;

template<typename T>
class Placements
{
  private:
  // Private Members
    PlacementId<T> placements_id;
    IdPlacement<T> id_placements;
    Area<T> area;
  public:
  // Constructors
    Placements() noexcept;
  // Iterators
    const_iterator<T> cbegin() const noexcept;
    const_iterator<T> cend() const noexcept;
  // Public Methods
    // Element Access
    template<typename U = std::pair<T,T>>
    std::optional<T> at(U&& u) const noexcept;
    // Capacity
    auto size() const noexcept;
    // Modifiers
    template<typename U = std::pair<std::pair<T,T>,T>>
    void insert(U&& u) noexcept;
    template<typename U>
    void erase(U&& u) const noexcept;
    // Lookup
    template<typename U = T>
    std::optional<std::pair<T,T>> find(U&& u) const noexcept;
    std::pair<T,T> get_area() const noexcept;
};

//
// Constructors
//
template<typename T>
Placements<T>::Placements() noexcept
  : placements_id(std::make_unique<
      typename PlacementId<T>::element_type>())
  , id_placements(std::make_unique<
      typename IdPlacement<T>::element_type>())
  , area(std::make_unique<
      typename Area<T>::element_type>())
{
}

//
// Iterators
//
template<typename T>
const_iterator<T> Placements<T>::cbegin() const noexcept
{
  return this->placements_id->cbegin();
}

template<typename T>
const_iterator<T> Placements<T>::cend() const noexcept
{
  return this->placements_id->cend();
}

//
// Public Methods
//

template<typename T>
template<typename U>
std::optional<T> Placements<T>::at(U&& u) const noexcept
{
  auto search { this->placements_id->find(u) };

  if ( search == this->placements_id->cend() )
    return std::nullopt;
  return search->second;
}

template<typename T>
auto Placements<T>::size() const noexcept
{
  return this->id_placements->size();
}

template<typename T>
template<typename U>
void Placements<T>::insert(U&& u) noexcept
{
  this->area->insert({u.first});
  this->id_placements->insert({u.second,u.first});
  this->placements_id->insert(std::forward<U>(u));
}

template<typename T>
template<typename U>
void Placements<T>::erase(U&& u) const noexcept
{
  auto search {this->id_placements->find(u)};
  if ( search != this->id_placements->end() )
  {
    this->area->erase( {search->second} );
    this->placements_id->erase(search->second);
    this->id_placements->erase(search);
  }
}

template<typename T>
template<typename U>
std::optional<std::pair<T,T>> Placements<T>::find(U&& u) const noexcept
{
  auto search { this->id_placements->find(u) };

  if ( search == this->id_placements->cend() )
    return std::nullopt;
  return search->second;
}

template<typename T>
std::pair<T,T> Placements<T>::get_area() const noexcept
{
  return this->area->get_area();
}

} // namespace electra::placement

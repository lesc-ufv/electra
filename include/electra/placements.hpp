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

namespace electra::placement {

template<typename T>
using ContainerA = std::map< std::pair<T,T>, T >;
template<typename T>
using ContainerB = std::map< T, std::pair<T,T> >;

template<typename T>
using const_iterator = typename ContainerA<T>::const_iterator;

template<typename T>
class Placements
{
  private:
  // Private Members
    std::unique_ptr<ContainerA<T>> placements_id;
    std::unique_ptr<ContainerB<T>> id_placements;
  // Public Members
  public:
  // Constructors
    Placements() noexcept;
  // Iterators
    const_iterator<T> cbegin() const noexcept;
    const_iterator<T> cend() const noexcept;
  // Public Methods
    template<typename U = std::pair<std::pair<T,T>,T>>
    void insert(U&& u) noexcept;
    template<typename U = T>
    std::optional<std::pair<T,T>> find(U&& u) const noexcept;
    template<typename U = std::pair<T,T>>
    std::optional<T> at(U&& u) const noexcept;
    template<typename U>
    void erase(U&& u) const noexcept;
  // Private Methods
  // Operators
};

//
// Constructors
//
template<typename T>
Placements<T>::Placements() noexcept
  : placements_id(std::make_unique<ContainerA<T>>())
  , id_placements(std::make_unique<ContainerB<T>>())
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
void Placements<T>::insert(U&& u) noexcept
{
  this->id_placements->insert({u.second,u.first});
  this->placements_id->insert(std::forward<U>(u));
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
template<typename U>
std::optional<T> Placements<T>::at(U&& u) const noexcept
{
  auto search { this->placements_id->find(u) };

  if ( search == this->placements_id->cend() )
    return std::nullopt;
  return search->second;
}

template<typename T>
template<typename U>
void Placements<T>::erase(U&& u) const noexcept
{
  auto search {this->id_placements->find(u)};
  if ( search != this->id_placements->end() )
  {
    this->placements_id->erase(search->second);
    this->id_placements->erase(search);
  }
}
} // namespace electra::placement

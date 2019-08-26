// vim: set ts=2 sw=2 tw=0 et :
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : wire
// @created     : Sunday Aug 04, 2019 18:50:03 -03
// @license     : MIT
// @description : Electra - Field-Coupled Nanocomputing Data Structures
//

#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <fstream>
#include <optional>

#include <electra/area.hpp>
#include <electra/wire/const_iterator.hpp>

namespace electra::wire
{
// Data types
template<typename T>
using _Wires = std::vector<std::vector<std::pair<T,T>>>;

// Dynamic memory storage
template<typename T>
using Storage = std::unique_ptr<_Wires<T>>;
template<typename T>
using Area = std::unique_ptr<area::Area<T>>;

template<typename T>
class Wires
{
  private:
  // Private Members
    Storage<T> wires;
    Area<T> area;
  public:
  // Constructors
    Wires();
  // Iterators
    const_iterator::const_iterator<_Wires<T>,
      typename _Wires<T>::const_iterator> cbegin() const noexcept;
    const_iterator::const_iterator<_Wires<T>,
      typename _Wires<T>::const_iterator> cend() const noexcept;
  // Public Methods
    // Capacity
    auto size() const noexcept;
    auto get_area() const noexcept;
    // Modifiers
    template<typename U = std::vector<std::pair<T,T>>>
    void insert(U&& u) noexcept;
    template<typename U = std::pair<T,T>>
    void erase(U&& a, U&& b) noexcept;
    // Lookup
    template<typename U = std::pair<T,T>>
    std::optional<const_iterator::const_iterator<_Wires<T>,
      typename _Wires<T>::const_iterator>> find(U&& a, U&& b) noexcept;
    // Operations
    template<typename U>
    void write(U&& filename) const noexcept;
    template<typename U>
    void read(U&& filename) noexcept;
  private:
  // Private Methods
    // Lookup
    template<typename U>
    auto find_if(U&& a, U&& b) noexcept;
    // Operations
    auto json() const noexcept;
  public:
  // Operators
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, Wires<U> const& wires);
};

//
// Constructors
//
template<typename T>
Wires<T>::Wires()
  : wires(std::make_unique<
    typename Storage<T>::element_type>())
  , area(std::make_unique<
    typename Area<T>::element_type>())
{
}

//
// Iterators
//
template<typename T>
const_iterator::const_iterator<_Wires<T>,
  typename _Wires<T>::const_iterator> Wires<T>::cbegin() const noexcept
{
  return const_iterator::const_iterator(*this->wires, this->wires->cbegin());
}

template<typename T>
const_iterator::const_iterator<_Wires<T>,
  typename _Wires<T>::const_iterator> Wires<T>::cend() const noexcept
{
  return const_iterator::const_iterator(*this->wires, this->wires->cend());
}

//
// Methods
//
template<typename T>
auto Wires<T>::size() const noexcept
{
  return this->wires->size();
}

template<typename T>
auto Wires<T>::get_area() const noexcept
{
  return this->area->get_area();
}

template<typename T>
template<typename U>
void Wires<T>::insert(U&& u) noexcept
{
  area->insert(u);
  this->wires->emplace_back(wire::encode(u.cbegin(), u.cend()));
}

template<typename T>
template<typename U>
void Wires<T>::erase(U&& a, U&& b) noexcept
{
  auto it {this->find_if(std::forward<U>(a),std::forward<U>(b))};

  if( it == this->wires->cend() ) return;

  //
  // Decode the wire to unset each region from
  // the area class
  //
  auto decoded_wire { decode(it->cbegin(), it->cend()) };
  area->erase( decoded_wire );

  this->wires->erase( it );
}

template<typename T>
template<typename U>
std::optional<const_iterator::const_iterator<_Wires<T>,
  typename _Wires<T>::const_iterator>> Wires<T>::find(U&& a, U&& b) noexcept
{
  auto search { this->find_if(std::forward<U>(a),std::forward<U>(b)) };
  if( search == this->wires->cend() )
  {
    return std::nullopt;
  }
  else
  {
    return const_iterator::const_iterator(*this->wires, search);
  }
}


template<typename T>
template<typename U>
void Wires<T>::write(U&& filename) const noexcept
{
  std::ofstream file{std::forward<U>(filename)};

  if( file.good() )
  {
    file << this->json();
  }
}

template<typename T>
template<typename U>
void Wires<T>::read(U&& filename) noexcept
{
  using Json = nlohmann::json;

  std::ifstream file{std::forward<U>(filename)};

  if( file.good() )
  {
    this->wires = std::make_unique<_Wires<T>>();
    Json j;
    file >> j;
    *this->wires = j.get<_Wires<T>>();
  }

}

//
// Private Methods
//
template<typename T>
template<typename U>
auto Wires<T>::find_if(U&& a, U&& b) noexcept
{
  return std::find_if(this->wires->cbegin(), this->wires->cend(),
    [&](auto const& wire)
    {
      return ( a == *(wire.begin()) ) && ( b == *(wire.rbegin()) );
    }
  );
}

template<typename T>
auto Wires<T>::json() const noexcept
{
  using Json = nlohmann::json;
  Json j;
  for(auto it{this->cbegin()}; it != this->cend(); ++it)
  {
    j += *it;
  }
  return j;
}

//
// Operators
//
template<typename U>
std::ostream& operator<<(std::ostream& os, Wires<U> const& wires)
{
  using Json = nlohmann::json;

  Json j{wires.json()};

  std::cout << "\033[92;1m * \033[mWires:" << std::endl;
  for( auto const& wire : j[0] )
  {
    std::cout << "\t\033[92;1m * \033[m ";
    std::cout << wire;
    std::cout << std::endl;
  }
  return os;
}

} // namespace electra::wire

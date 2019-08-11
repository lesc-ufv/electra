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
#include <memory>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

#include <electra/area.hpp>

namespace electra::wire
{
  template<typename T>
  using Container = std::vector<std::vector<std::pair<T,T>>>;

  template<typename T>
  using const_iterator = typename Container<T>::const_iterator;

  template<typename T>
  class Wires
  {
    private:
    // Private Members
      std::unique_ptr<Container<T>> wires;
      std::unique_ptr<area::Area<T>> area;
    public:
    // Constructors
      Wires();
    // Iterators
      const_iterator<T> cbegin() const noexcept;
      const_iterator<T> cend() const noexcept;
    // Public Methods
      template<typename U = std::vector<std::pair<T,T>>>
      void add(U&& u) noexcept;
      template<typename U = std::pair<T,T>>
      auto get(U&& a, U&& b) noexcept;
      template<typename U = std::pair<T,T>>
      void erase(U&& a, U&& b) noexcept;
      template<typename U>
      void write(U&& filename) const noexcept;
      template<typename U>
      void read(U&& filename) noexcept;
      auto size() const noexcept;
      auto get_area() const noexcept;
    private:
    // Private Methods
      auto json() const noexcept;
      template<typename U>
      auto find_if(U&& a, U&& b) noexcept;
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
    : wires(std::make_unique<Container<T>>())
    , area(std::make_unique<area::Area<T>>())
  {
  }

  //
  // Iterators
  //
  template<typename T>
  const_iterator<T> Wires<T>::cbegin() const noexcept
  {
    return this->wires->cbegin();
  }

  template<typename T>
  const_iterator<T> Wires<T>::cend() const noexcept
  {
    return this->wires->cend();
  }

  //
  // Methods
  //
  template<typename T>
  template<typename U>
  void Wires<T>::add(U&& u) noexcept
  {
    area->set(u);
    this->wires->emplace_back(wire::encode(u.cbegin(), u.cend()));
  }

  template<typename T>
  template<typename U>
  auto Wires<T>::get(U&& a, U&& b) noexcept
  {
    return this->find_if(std::forward<U>(a),std::forward<U>(b));
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
    area->unset( decoded_wire );

    this->wires->erase( it );
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
      this->wires = std::make_unique<Container<T>>();
      Json j;
      file >> j;
      *this->wires = j.get<Container<T>>();
    }

  }

  template<typename T>
  auto Wires<T>::size() const noexcept
  {
    return this->wires->size();
  }

  template<typename T>
  auto Wires<T>::get_area() const noexcept
  {
    return this->area->get();
  }

  //
  // Private Methods
  //
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

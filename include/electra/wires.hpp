/* vim: set ts=2 sw=2 tw=0 et :*/
/**
 * @company     : Universidade Federal de Viçosa - Florestal
 * @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
 * @file        : wire
 * @created     : Sunday Aug 04, 2019 18:50:03 -03
 * @license     : MIT
 * @description : Electra - Field-Coupled Nanocomputing Data Structures
*/

#pragma once

#include <vector>
#include <memory>

namespace electra
{

  template<typename T>
  class Wires
  {
    private:
    public:
      Wires() = default;
      template<typename U>
      void add(U&& u) noexcept;
      template<typename U, typename V>
      V const& get(U&& a, U&& b) const noexcept;
      template<typename U>
      void erase(U&& a, U&& b) noexcept;
  };

  template<typename T>
  template<typename U>
  void Wires<T>::add(U&& u) noexcept
  {
  }

  template<typename T>
  template<typename U, typename V>
  V const& Wires<T>::get(U&& a, U&& b) const noexcept
  {
  }

  template<typename T>
  template<typename U>
  void Wires<T>::erase(U&& a, U&& b) noexcept
  {
  }

} // namespace electra

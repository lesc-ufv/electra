// vim: set ts=2 sw=2 tw=0 et :
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : const_iterator
// @created     : Sunday Aug 25, 2019 23:08:22 -03
// @license     : MIT
// @description : Electra - Field-Coupled Nanocomputing Data Structures
//

#pragma once

#include <iterator>

namespace electra::wire::const_iterator
{

//
// Forward const iterator
//
template<typename T1, typename InIt, typename T2 = typename InIt::value_type>
class const_iterator {
  private:
  // Private Members
    T1 const& wires;
    InIt current;
    T2 decoded_cache;
  public:
  // Public Members
    using iterator_tag = std::input_iterator_tag;
    using value_type = T1;
    using const_pointer = T1 const *;
    using const_reference = T1 const &;
  // Constructors
    const_iterator() = default;
    const_iterator(T1 const& wires, InIt current);
  // Operators
    InIt const& operator++();
    T2 const& operator*();
    T2 const* operator->();
    bool operator==( const_iterator const& rhs );
    bool operator!=( const_iterator const& rhs );
};

//
// Constructors
//
template<typename T1, typename InIt, typename T2>
const_iterator<T1,InIt,T2>::const_iterator(T1 const& wires, InIt current)
  : wires(wires)
  , current(current)
  , decoded_cache(T2{})
{
}

//
// Operators
//
template<typename T1, typename InIt, typename T2>
InIt const& const_iterator<T1,InIt,T2>::operator++()
{
  this->current = ++this->current;
  return this->current;
}

template<typename T1, typename InIt, typename T2>
T2 const& const_iterator<T1,InIt,T2>::operator*()
{
  this->decoded_cache = wire::decode(this->current->cbegin(), this->current->cend());
  return this->decoded_cache;
}

template<typename T1, typename InIt, typename T2>
T2 const* const_iterator<T1,InIt,T2>::operator->()
{
  return &(operator*());
}

template<typename T1, typename InIt, typename T2>
bool const_iterator<T1,InIt,T2>::operator==( const_iterator const& rhs )
{
  return this->current == rhs.current;
}

template<typename T1, typename InIt, typename T2>
bool const_iterator<T1,InIt,T2>::operator!=( const_iterator const& rhs )
{
  return !this->operator==(rhs);
}

} // namespace electra::wire::const_iterator

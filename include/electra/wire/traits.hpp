// vim: set ts=2 sw=2 tw=0 et :
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : traits
// @created     : Saturday Aug 10, 2019 21:07:46 -03
// @license     : MIT
// @description : Electra - Field-Coupled Nanocomputing Data Structures
//

#pragma once

#include <type_traits>
#include <iterator>

namespace electra::wire::traits {

// has_value_type
template<typename T, typename = std::void_t<>>
struct has_value_type
: std::false_type {};

template<typename T>
struct has_value_type< T, std::void_t<typename T::value_type>>
: std::true_type {};


// is_iterator
template<typename T, typename = std::void_t<>>
struct is_iterator
: std::false_type {};

template<typename T>
struct is_iterator< T, std::void_t<typename std::iterator_traits<T>::iterator_category>>
: std::true_type {};

} // namespace electra::traits

// vim: set ts=2 sw=2 tw=0 et :
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : tests
// @created     : Tuesday Aug 06, 2019 10:55:07 -03
// @license     : MIT
// @description : Electra - Field-Coupled Nanocomputing Data Structures
//

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

template<typename InIt1, typename InIt2, typename T = typename InIt1::value_type>
void compare(InIt1&& cbegin, InIt1&& cend, InIt2&& target)
{
  for( auto it{cbegin}; it!=cend;)
  {
    REQUIRE(it->first == target->first);
    REQUIRE(it->second == target->second);
    ++it;
    ++target;
  }
}

#include "include/electra/wire/encode.cpp"
#include "include/electra/wire/decode.cpp"
#include "include/electra/wires.cpp"
#include "include/electra/area.cpp"
#include "include/electra/placements.cpp"

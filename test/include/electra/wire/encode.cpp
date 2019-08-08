/* vim: set ts=2 sw=2 tw=0 et :*/
/**
 * @company     : Universidade Federal de Viçosa - Florestal
 * @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
 * @file        : encode
 * @created     : Tuesday Aug 06, 2019 10:56:25 -03
 * @license     : MIT
 * @description : Electra - Field-Coupled Nanocomputing Data Structures
*/

#include <vector>
#include <utility>
#include <cstdint>

#include <electra/wire/encode.hpp>

template<typename InIt, typename T = typename InIt::value_type>
void compare(InIt&& cbegin, InIt&& cend, InIt&& target)
{
  for( auto it{cbegin}; it!=cend;)
  {
    REQUIRE(it->first == target->first);
    REQUIRE(it->second == target->second);
    ++it;
    ++target;
  }
}

TEST_CASE("Encoding a wire", "[encode]")
{
  using Wire = std::vector<std::pair<int32_t,int32_t>>;

  SECTION("Single Element")
  {
    Wire w {{4,2}};

    auto e {electra::wire::encode(w.cbegin(),w.cend())};

    Wire s {{4,2}};

    compare(e.cbegin(), e.cend(), s.cbegin());
  }

  SECTION("Vertical Orientation")
  {
    Wire w1 {{0,3},{0,2},{0,1},{0,0}};
    Wire w2 {{0,0},{0,1},{0,2},{0,3}};

    auto e1 {electra::wire::encode(w1.cbegin(),w1.cend())};
    auto e2 {electra::wire::encode(w2.cbegin(),w2.cend())};

    Wire s1 {{0,3},{0,-1},{0,0}};
    Wire s2 {{0,0},{0,1},{0,3}};

    REQUIRE(e1.size() == s1.size());
    REQUIRE(e2.size() == s2.size());

    compare(e1.cbegin(), e1.cend(), s1.cbegin());
    compare(e2.cbegin(), e2.cend(), s2.cbegin());
  }

  SECTION("Horizontal Orientation")
  {
    Wire w1{{0,0},{1,0},{2,0},{3,0}};
    Wire w2{{3,0},{2,0},{1,0},{0,0}};

    auto e1 {electra::wire::encode(w1.cbegin(),w1.cend())};
    auto e2 {electra::wire::encode(w2.cbegin(),w2.cend())};

    Wire s1 {{0,0},{1,0},{3,0}};
    Wire s2 {{3,0},{-1,0},{0,0}};

    REQUIRE(e1.size() == s1.size());
    REQUIRE(e2.size() == s2.size());

    compare(e1.cbegin(), e1.cend(), s1.cbegin());
    compare(e2.cbegin(), e2.cend(), s2.cbegin());
  }

  SECTION("Mixed Orientations")
  {
    /* Right and Downwards */
    Wire w1{{0,0},{1,0},{2,0},{3,0},{3,1},{3,2},{3,3}};
    /* Left and Downwards */
    Wire w2{{3,0},{2,0},{1,0},{0,0},{0,1},{0,2},{0,3}};
    /* Right and Upwards */
    Wire w3{{0,0},{1,0},{2,0},{3,0},{3,-1},{3,-2},{3,-3}};
    /* Left and Upwards */
    Wire w4{{3,0},{2,0},{1,0},{0,0},{0,-1},{0,-2},{0,-3}};

    auto e1 {electra::wire::encode(w1.cbegin(),w1.cend())};
    auto e2 {electra::wire::encode(w2.cbegin(),w2.cend())};
    auto e3 {electra::wire::encode(w3.cbegin(),w3.cend())};
    auto e4 {electra::wire::encode(w4.cbegin(),w4.cend())};

    /* Right and Downwards */
    Wire s1 {{0,0},{1,0},{3,0},{3,1},{0,1},{3,3}};
    /* Left and Downwards */
    Wire s2 {{3,0},{-1,0},{0,0},{0,1},{0,1},{0,3}};
    /* Right and Upwards */
    Wire s3 {{0,0},{1,0},{3,0},{3,-1},{0,-1},{3,-3}};
    /* Left and Upwards */
    Wire s4 {{3,0},{-1,0},{0,0},{0,-1},{0,-1},{0,-3}};

    REQUIRE(e1.size() == s1.size());
    REQUIRE(e2.size() == s2.size());
    REQUIRE(e3.size() == s3.size());
    REQUIRE(e4.size() == s4.size());

    compare(e1.cbegin(), e1.cend(), s1.cbegin());
    compare(e2.cbegin(), e2.cend(), s2.cbegin());
    compare(e3.cbegin(), e3.cend(), s3.cbegin());
    compare(e4.cbegin(), e4.cend(), s4.cbegin());
  }
}

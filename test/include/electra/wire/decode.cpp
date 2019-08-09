/* vim: set ts=2 sw=2 tw=0 et :*/
/**
 * @company     : Universidade Federal de Viçosa - Florestal
 * @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
 * @file        : decode
 * @created     : Friday Aug 09, 2019 01:28:08 -03
 * @license     : MIT
 * @description : Electra - Field-Coupled Nanocomputing Data Structures
*/

#include <electra/wire/decode.hpp>

TEST_CASE("Decoding a Wire")
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
    Wire w1 {{0,3},{0,-1},{0,0}};
    Wire w2 {{0,0},{0,1},{0,3}};

    auto e1 {electra::wire::decode(w1.cbegin(),w1.cend())};
    auto e2 {electra::wire::decode(w2.cbegin(),w2.cend())};

    Wire s1 {{0,3},{0,2},{0,1},{0,0}};
    Wire s2 {{0,0},{0,1},{0,2},{0,3}};

    REQUIRE(e1.size() == s1.size());
    REQUIRE(e2.size() == s2.size());

    compare(e1.cbegin(), e1.cend(), s1.cbegin());
    compare(e2.cbegin(), e2.cend(), s2.cbegin());
  }

  SECTION("Horizontal Orientation")
  {
    Wire w1 {{0,0},{1,0},{3,0}};
    Wire w2 {{3,0},{-1,0},{0,0}};

    auto e1 {electra::wire::decode(w1.cbegin(),w1.cend())};
    auto e2 {electra::wire::decode(w2.cbegin(),w2.cend())};

    Wire s1{{0,0},{1,0},{2,0},{3,0}};
    Wire s2{{3,0},{2,0},{1,0},{0,0}};

    REQUIRE(e1.size() == s1.size());
    REQUIRE(e2.size() == s2.size());

    compare(e1.cbegin(), e1.cend(), s1.cbegin());
    compare(e2.cbegin(), e2.cend(), s2.cbegin());
  }

  SECTION("Mixed Orientations")
  {
    /* Right and Upwards */
    Wire w1 {{0,0},{1,0},{3,0},{0,-1},{3,-3}};
    /* Right and Downwards */
    Wire w2 {{0,0},{1,0},{3,0},{0,1},{3,3}};
    /* Left and Downwards */
    Wire w3 {{3,0},{-1,0},{0,0},{0,1},{0,3}};
    /* Left and Upwards */
    Wire w4 {{3,0},{-1,0},{0,0},{0,-1},{0,-3}};
    /* Upwards and Right */
    Wire w5 {{10,5},{0,-1},{10,2},{1,0},{12,2}};
    /* Upwards and left */
    Wire w6 {{10,5},{0,-1},{10,2},{-1,0},{7,2}};
    /* Downwards and Right */
    Wire w7 {{10,5},{0,1},{10,8},{1,0},{13,8}};
    /* Downwards and left */
    Wire w8 {{10,5},{0,1},{10,8},{-1,0},{7,8}};

    auto e1 {electra::wire::decode(w1.cbegin(),w1.cend())};
    auto e2 {electra::wire::decode(w2.cbegin(),w2.cend())};
    auto e3 {electra::wire::decode(w3.cbegin(),w3.cend())};
    auto e4 {electra::wire::decode(w4.cbegin(),w4.cend())};
    auto e5 {electra::wire::decode(w5.cbegin(),w5.cend())};
    auto e6 {electra::wire::decode(w6.cbegin(),w6.cend())};
    auto e7 {electra::wire::decode(w7.cbegin(),w7.cend())};
    auto e8 {electra::wire::decode(w8.cbegin(),w8.cend())};

    /* Right and Upwards */
    Wire s1{{0,0},{1,0},{2,0},{3,0},{3,-1},{3,-2},{3,-3}};
    /* Right and Downwards */
    Wire s2{{0,0},{1,0},{2,0},{3,0},{3,1},{3,2},{3,3}};
    /* Left and Downwards */
    Wire s3{{3,0},{2,0},{1,0},{0,0},{0,1},{0,2},{0,3}};
    /* Left and Upwards */
    Wire s4{{3,0},{2,0},{1,0},{0,0},{0,-1},{0,-2},{0,-3}};
    /* Upwards and Right */
    Wire s5 {{10,5},{10,4},{10,3},{10,2},{11,2},{12,2}};
    /* Upwards and left */
    Wire s6 {{10,5},{10,4},{10,3},{10,2},{9,2},{8,2},{7,2}};
    /* Downwards and Right */
    Wire s7 {{10,5},{10,6},{10,7},{10,8},{11,8},{12,8},{13,8}};
    /* Downwards and left */
    Wire s8 {{10,5},{10,6},{10,7},{10,8},{9,8},{8,8},{7,8}};


    REQUIRE(e1.size() == s1.size());
    REQUIRE(e2.size() == s2.size());
    REQUIRE(e3.size() == s3.size());
    REQUIRE(e4.size() == s4.size());
    REQUIRE(e5.size() == s5.size());
    REQUIRE(e6.size() == s6.size());
    REQUIRE(e7.size() == s7.size());
    REQUIRE(e8.size() == s8.size());

    compare(e1.cbegin(), e1.cend(), s1.cbegin());
    compare(e2.cbegin(), e2.cend(), s2.cbegin());
    compare(e3.cbegin(), e3.cend(), s3.cbegin());
    compare(e4.cbegin(), e4.cend(), s4.cbegin());
    compare(e5.cbegin(), e5.cend(), s5.cbegin());
    compare(e6.cbegin(), e6.cend(), s6.cbegin());
    compare(e7.cbegin(), e7.cend(), s7.cbegin());
    compare(e8.cbegin(), e8.cend(), s8.cbegin());
  }
}

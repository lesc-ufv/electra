// vim: set ts=2 sw=2 tw=0 et :
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : placements
// @created     : Sunday Aug 11, 2019 08:39:10 -03
// @license     : MIT
// @description : Electra - Field-Coupled Nanocomputing Data Structures
//

#include <electra/placements.hpp>

TEST_CASE("Placements testing unit", "[placements]")
{
  electra::placement::Placements<int32_t> placements;

  SECTION("Insertion")
  {
    placements.insert( {{{8,8},9},{{3,8},8}} );
  }

  SECTION("LookUp")
  {
    placements.insert( {{{8,8},9},{{3,8},8}} );

    REQUIRE( placements.find(9) );
    REQUIRE( placements.find(8) );
    REQUIRE_FALSE( placements.find(4) );
    REQUIRE_FALSE( placements.find(3) );

    REQUIRE( placements.at({8,8}) );
    REQUIRE( placements.at({3,8}) );
    REQUIRE_FALSE( placements.at({7,8}) );
    REQUIRE_FALSE( placements.at({-10,-30}) );
  }

  SECTION("Removal")
  {
    placements.insert({{{4,8},9},{{-10,8},8}});

    auto search { placements.at({-10,8}) };

    REQUIRE( search );

    placements.erase( 8 );

    search = placements.at({-10,8});

    REQUIRE_FALSE( search );
  }
}

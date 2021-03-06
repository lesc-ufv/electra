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
#include <filesystem>

TEST_CASE("Placements testing unit", "[placements]")
{
  using Placements = electra::placement::Placements<int32_t>;

  Placements placements;

  SECTION("Insertion")
  {
    placements.insert( {{8,8},9} );
    placements.insert( {{3,8},8} );
  }

  SECTION("LookUp")
  {
    placements.insert( {{8,8},9} );
    placements.insert( {{3,8},8} );

    REQUIRE( placements.find(9) );
    REQUIRE( placements.find(8) );
    REQUIRE_FALSE( placements.find(4) );
    REQUIRE_FALSE( placements.find(3) );

    REQUIRE( placements.at( {8,8}) );
    REQUIRE( placements.at( {3,8}) );
    REQUIRE_FALSE( placements.at({7,8}) );
    REQUIRE_FALSE( placements.at({-10,-30}) );
  }

  SECTION("Removal")
  {
    placements.insert( {{  4,8},9} );
    placements.insert( {{-10,8},8} );

    auto search { placements.at( {-10,8} ) };

    REQUIRE( search );

    placements.erase( 8 );

    search = placements.at( {-10,8} );

    REQUIRE_FALSE( search );
  }

  SECTION("Area")
  {
    placements.insert( {{ 0,2},1} );
    placements.insert( {{-2,4},2} );

    auto area { placements.get_area() };
    REQUIRE( area.first == 3 );
    REQUIRE( area.second == 3 );

    placements.erase( 2 );

    area = placements.get_area();
    REQUIRE( area.first == 1 );
    REQUIRE( area.second == 1 );
  }

  SECTION("Size")
  {
    placements.insert( {{  4,8},9} );
    placements.insert( {{-10,8},8} );

    REQUIRE( placements.size() == 2 );

    placements.erase(9);

    REQUIRE( placements.size() == 1 );

    placements.erase(8);

    REQUIRE( placements.size() == 0 );
  }

  SECTION("Json I/O")
  {
    placements.insert( {{8,8},9} );
    placements.insert( {{4,3},7} );
    placements.insert( {{1,2},5} );
    placements.insert( {{0,8},1} );

    std::filesystem::create_directory("./test/json-output/");

    placements.write("./test/json-output/");

    Placements test;
    test.read("./test/json-output/");

    REQUIRE(test.size() == 4);
    REQUIRE(*test.find(1) == std::make_pair(0,8));
    REQUIRE(*test.find(5) == std::make_pair(1,2));
    REQUIRE(*test.find(7) == std::make_pair(4,3));
    REQUIRE(*test.find(9) == std::make_pair(8,8));
    REQUIRE(test.get_area() == std::make_pair(9,7));

    std::filesystem::remove_all("./test/json-output");
  }

}

// vim: set ts=2 sw=2 tw=0 et :
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : area
// @created     : Friday Aug 09, 2019 20:50:23 -03
// @license     : MIT
// @description : Electra - Field-Coupled Nanocomputing Data Structures
//

#include <electra/area.hpp>
#include <electra/wire/encode.hpp>
#include <electra/wire/decode.hpp>
#include <electra/wires.hpp>

TEST_CASE("Area", "[area]")
{
  electra::wire::Wires<int64_t> wires;

  SECTION("Insertion")
  {
    auto area {wires.get_area()};

    REQUIRE(area.first == 0);
    REQUIRE(area.second == 0);

    // Setting a wire of length 4
    wires.insert({{3,0},{3,1},{3,2},{3,3}});

    // Updating the area
    area = wires.get_area();

    // Checking for 1x4 dimensions
    REQUIRE(area.first == 1);
    REQUIRE(area.second == 4);
  }

  SECTION("Removal")
  {
    // Setting a wire of length 4
    wires.insert({{3,0},{3,1},{3,2},{3,3}});

    // Removing the wire
    wires.erase({3,0},{3,3});

    auto area {wires.get_area()};

    // Checking for 0x0 dimensions
    REQUIRE(area.first == 0);
    REQUIRE(area.second == 0);
  }

  SECTION("Insertion and Removal")
  {
    // Setting the wires
    wires.insert({{3,0},{3,1},{3,2},{3,3}});
    wires.insert({{10,0},{9,0},{8,0},{8,1}});

    auto area {wires.get_area()};

    // Checking for 8x4 dimensions
    REQUIRE(area.first == 8);
    REQUIRE(area.second == 4);

    wires.erase({10,0},{8,1});

    area = wires.get_area();

    // Checking for 1x4 dimensions
    REQUIRE(area.first == 1);
    REQUIRE(area.second == 4);
  }
}

/* vim: set ts=2 sw=2 tw=0 et :*/
/**
 * @company     : Universidade Federal de Viçosa - Florestal
 * @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
 * @file        : wires
 * @created     : Wednesday Aug 07, 2019 21:55:11 -03
 * @license     : MIT
 * @description : Electra - Field-Coupled Nanocomputing Data Structures
*/

#include <electra/wires.hpp>

TEST_CASE("Wires" "[wires]")
{
  electra::wire::Wires<int32_t> wires;
  SECTION("Insertion")
  {
    wires.add({{3,1},{3,2},{3,3},{3,4}});
    auto wire {wires.get({3,1},{3,4})};

    REQUIRE(wire->size() == 3);
  }

  SECTION("Removal")
  {
    wires.add({{3,1},{3,2},{3,3},{3,4}});
    wires.erase({3,1},{3,4});

    auto wire {wires.get({3,1},{3,4})};

    REQUIRE(wire == wires.cend());
    REQUIRE(wires.size() == 0);
    wires.add({{3,1},{3,2},{3,3},{3,4}});
    REQUIRE(wires.size() == 1);
  }

  SECTION("Json Read")
  {
    wires.add({{3,1},{3,2},{3,3},{3,4}});
    wires.add({{10,1},{9,1},{9,2},{9,3}});
    wires.add({{3,1},{3,0},{3,-1},{3,-2}});
    wires.add({{4,5},{5,5},{5,6},{5,7}});
    wires.write("wires.json");

    electra::wire::Wires<int32_t> _wires;
    _wires.read("wires.json");

    REQUIRE(_wires.size() == 4);
  }
}

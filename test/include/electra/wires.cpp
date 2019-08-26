// vim: set ts=2 sw=2 tw=0 et :
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : wires
// @created     : Wednesday Aug 07, 2019 21:55:11 -03
// @license     : MIT
// @description : Electra - Field-Coupled Nanocomputing Data Structures
//

#include <electra/wires.hpp>
#include <cstdio>
#include <fstream>

TEST_CASE("Wires" "[wires]")
{
  electra::wire::Wires<int32_t> wires;
  SECTION("Insertion")
  {
    wires.insert( {{3,1},{3,2},{3,3},{3,4}} );

    auto search { wires.find( {3,1},{3,4} ) };

    REQUIRE( search );

    REQUIRE( (*search)->size() == 4 );
  }

  SECTION("Removal")
  {
    wires.insert({{3,1},{3,2},{3,3},{3,4}});
    wires.erase({3,1},{3,4});

    REQUIRE_FALSE( wires.find({3,1},{3,4}) );

    REQUIRE( wires.size() == 0 );

    wires.insert( {{3,1},{3,2},{3,3},{3,4}} );

    REQUIRE( wires.size() == 1 );
  }

  SECTION("Transparent Decoding")
  {
    using Wires = std::vector<std::vector<std::pair<int32_t,int32_t>>>;

    Wires samples
    {
      {{3,1},{3,2},{3,3},{3,4}},
      {{-1,1},{-2,1},{-2,2},{-2,3}},
    };

    wires.insert( samples.at(0) );
    wires.insert( samples.at(1) );

    auto it2{ samples.cbegin() };
    for( auto it1{ wires.cbegin() }; it1 != wires.cend(); ++it1, ++it2)
    {
      auto vec {*it1};
      compare(vec.cbegin(), vec.cend(), it2->cbegin());
    }
  }

  SECTION("Json Read")
  {
    wires.insert( {{3,1},{3,2},{3,3},{3,4}}   );
    wires.insert( {{10,1},{9,1},{9,2},{9,3}}  );
    wires.insert( {{3,1},{3,0},{3,-1},{3,-2}} );
    wires.insert( {{4,5},{5,5},{5,6},{5,7}}   );
    wires.write( "wires.json" );

    electra::wire::Wires<int32_t> _wires;
    _wires.read("wires.json");

    REQUIRE( _wires.size() == 4 );

    // Delete file wires.json
    std::remove( "wires.json" );
  }
}

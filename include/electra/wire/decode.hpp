// vim: set ts=2 sw=2 tw=0 et :
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : decode
// @created     : Thursday Aug 08, 2019 23:20:03 -03
// @license     : MIT
// @description : Electra - Field-Coupled Nanocomputing Data Structures
//

#pragma once

#include <vector>

//
// Algorithm's Description:
//   Expand a list length using directional separators. E.g:
//   {{0,1},{0,1},{0,5}} becomes
//   {{0,1},{0,2},{0,3},{0,4},{0,5}}
//   Where the second pair indicates the direction for which
//   the list must be expanded to reach the original size.
// Cavefeats:
//   A list must change only one of its pair elements
//   at a time, sequentially, else the behaviour is undefined
//

namespace electra::wire
{

template<typename InIt, typename T = typename InIt::value_type>
std::vector<T> decode( InIt&& it_beg, InIt&& it_end )
{

  //
  // Define the directions enumeration
  //
  enum class Direction
  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
  };

  std::vector<T> list;

  //
  // If the list has size 1, return its only element
  //
  if( it_beg == it_end-1 )
  {
    list.push_back(*it_beg);
    return list;
  }

  //
  // Iterate through the list
  //
  bool first{true};
  for( auto it{it_beg}; it!=it_end; )
  {
    Direction dir;

    //
    // Discover the direction of the wire
    //
    if( (it+1)->first == 0 )
    {
      if( (it+1)->second == 1 )
      {
        dir = Direction::DOWN;
      }
      else
      {
        dir = Direction::UP;
      }

    }
    else
    {
      if( (it+1)->first == 1 )
      {
        dir = Direction::RIGHT;
      }
      else
      {
        dir = Direction::LEFT;
      }
    }

    auto i{ it->first };
    auto j{ it->second };

    switch (dir)
    {
      case Direction::RIGHT:
        if( ! first ) ++i;
        for(; i != (it+2)->first+1; ++i )
        {
          list.emplace_back( i, j );
        }
        break;
      case Direction::LEFT:
        if( ! first ) --i;
        for(; i != (it+2)->first-1; --i )
        {
          list.emplace_back( i, j );
        }
        break;
      case Direction::DOWN:
        if( ! first ) ++j;
        for(; j != (it+2)->second+1; ++j )
        {
          list.emplace_back( i, j );
        }
        break;
      default:
        if( ! first ) --j;
        for(; j != (it+2)->second-1; --j )
        {
          list.emplace_back( i, j );
        }
    }

    //
    // Format of the wire is assumed
    // to be consistent, next (it+2) comes a
    // starting point, a direction and
    // an ending point
    // (0,3),(0,1),(0,8),(1,0),(5,8)
    //    ^           ^           ^
    //   it        (it+2)      (it+4)
    //
    if( it+3 == it_end )
    {
      it = it_end;
    }
    else
    {
      it = it+2;
    }
    first = false;
  }

  return list;
}

} // namespace electra::wire

// vim: set ts=2 sw=2 tw=0 et :
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : encode
// @created     : Tuesday Aug 06, 2019 10:31:23 -03
// @license     : MIT
// @description : Electra - Field-Coupled Nanocomputing Data Structures
//

#pragma once

#include <vector>

//
// Algorithm's Description:
//   Reduce a list length using directional separators. E.g:
//   {{0,1},{0,2},{0,3},{0,4},{0,5}} becomes
//   {{0,1},{0,1},{0,5}}
//   Where the second pair indicates the direction for which
//   the list must be expanded to reach the original size.
// Cavefeats:
//   A list must change only one of its pair elements
//   at a time, sequentially, else the behaviour is undefined
//
namespace electra::wire
{

template<typename InIt, typename T = typename InIt::value_type>
std::vector<T> encode( InIt&& it_beg, InIt&& it_end )
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
    // The first element of the item
    // is equal to the one of its
    // sucessor.
    //
    if( it->first == (it+1)->first )
    {
      if( it->second < (it+1)->second )
      {
        dir = Direction::DOWN;
      }
      else
      {
        dir = Direction::UP;
      }

      //
      // Advance until an element is found
      // such that its first element is not
      // equal to the one of its predecessor
      //
      do
      {
        if( it == it_end )
        {
          break;
        }
        else
        {
          ++it;
        }
      }
      while(it->first == (it+1)->first);

      //
      // Given a position, indicate the direction
      // in which the list must be expanded to
      // obtain the original one
      //
      if( dir == Direction::UP )
      {
        if( first )
        {
          list.emplace_back( *it_beg );
        }

        list.emplace_back( 0, -1 );

        if( it == it_end )
        {
          list.emplace_back( *(it-1) );
        }
        else
        {
          list.emplace_back( *it );
        }
      }
      else
      {
        if( first )
        {
          list.push_back( *it_beg );
        }

        list.emplace_back( 0, 1 );

        if( it == it_end )
        {
          list.push_back( *(it-1) );
        }
        else
        {
          list.push_back( *it );
        }
      }
    }

    //
    // The second element of the item
    // is equal to the second element
    // of its sucessor.
    //
    else
    {
      if( it->first < (it+1)->first )
      {
        dir = Direction::RIGHT;
      }
      else
      {
        dir = Direction::LEFT;
      }

      do
      {
        if( it == it_end )
        {
          break;
        }
        else
        {
          ++it;
        }
      }
      while( it->second == (it+1)->second );

      if( dir == Direction::LEFT )
      {
        if( first )
        {
          list.emplace_back( *it_beg );
        }

        list.emplace_back( -1, 0 );

        if( it == it_end )
        {
          list.emplace_back( *(it-1) );
        }
        else
        {
          list.emplace_back( *it );
        }
      }
      else
      {
        if( first )
        {
          list.push_back( *it_beg );
        }

        list.emplace_back( 1, 0 );

        if( it == it_end )
        {
          list.push_back( *(it-1) );
        }
        else
        {
          list.push_back( *it );
        }
      }
    }

    //
    // Move to process the next coordinate of the list
    // if it is not unidirectional in one of its
    // elements
    //
    if( it+1 == it_end ) it = it_end;
    first = false;
  }

  return list;
}

} // namespace electra::wire

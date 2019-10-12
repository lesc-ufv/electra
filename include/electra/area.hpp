// vim: set ts=2 sw=2 tw=0 et :
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : area
// @created     : Thursday Aug 08, 2019 22:54:24 -03
// @license     : MIT
// @description : Electra - Field-Coupled Nanocomputing Data Structures
//

#pragma once
#include <utility>
#include <map>

#include <nlohmann/json.hpp>

namespace electra::area
{
  template<typename T>
  using X = std::map<T, T>;
  template<typename T>
  using Y = std::map<T, T>;

  template<typename T>
  class Area
  {

    private:
      X<T> x_map;
      Y<T> y_map;
    public:
    // Public Methods
      // Element Access
      template<typename U = std::vector<std::pair<T,T>>>
      void insert(U&& u) noexcept;
      template<typename U = std::vector<std::pair<T,T>>>
      void erase(U&& u) noexcept;
      std::pair<T,T> get_area() const noexcept;
      // Operations
      template<typename _T>
      friend void to_json(nlohmann::json& j, Area<_T> const& area);
      template<typename _T>
      friend void from_json(const nlohmann::json& j, Area<_T>& area);
  };

  //
  // Public Methods
  //
  template<typename T>
  template<typename U>
  void Area<T>::insert(U&& u) noexcept
  {
    for( auto entry : u )
    {
      auto search_x {x_map.find(entry.first)};
      auto search_y {y_map.find(entry.second)};

      if(search_x == std::end(x_map)) x_map.insert({entry.first,1});
      else search_x->second++;

      if(search_y == std::end(y_map)) y_map.insert({entry.second,1});
      else search_y->second++;
    }
  }

  template<typename T>
  template<typename U>
  void Area<T>::erase(U&& u) noexcept
  {
    for( auto entry : u )
    {
      auto search_x {x_map.find(entry.first)};
      auto search_y {y_map.find(entry.second)};

      if(search_x == std::end(x_map)) return;
      if(search_y == std::end(y_map)) return;

      if(search_x->second<= 1) x_map.erase(search_x);
      else search_x->second--;

      if(search_y->second<= 1) y_map.erase(search_y);
      else search_y->second--;
    }
  }

  template<typename T>
  std::pair<T,T> Area<T>::get_area() const noexcept
  {
    if(x_map.empty()) return {0,0};

    auto x_max {std::rbegin(x_map)->first};
    auto x_min {std::begin(x_map)->first};
    auto x_delta{(x_max+1)-x_min};

    auto y_max {std::rbegin(y_map)->first};
    auto y_min {std::begin(y_map)->first};
    auto y_delta{(y_max+1)-y_min};

    return {x_delta,y_delta};
  }

  template<typename _T>
  void to_json(nlohmann::json& j, Area<_T> const& area)
  {
    j = nlohmann::json{{"x",area.x_map}, {"y",area.y_map}};
  }

  template<typename _T>
  void from_json(const nlohmann::json& j, Area<_T>& area)
  {
      j.at("x").get_to(area.x_map);
      j.at("y").get_to(area.y_map);
  }

} // namespace electra::area

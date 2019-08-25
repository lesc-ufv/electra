# Placements

```cpp
template<typename T> class Placements
```

The placements class has one template parameter, it represents
the **placement id**. Specify a type that will not overflow based
on the number of nodes of your networks.

### Constructors

```cpp
Placements() noexcept;
```

There is only a single default constructor.

### Iterators

```cpp
const_iterator<T> cbegin() const noexcept;
const_iterator<T> cend() const noexcept;
```

The objects of this class are iterable, as shown in the example
snippet below:

```cpp
using namespace electra::placement;

Placements<int32_t> ps;

for( auto it{ ps.cbegin() }; it!=ps.cend(); ++it )
{
  // Code goes here
}
```

### Public Methods

#### Element Access

```cpp
template<typename U = std::pair<T,T>>
std::optional<T> at(U&& u) const noexcept;
```
Given a **region**, get a placement **id**. Electra uses the `std::optional` C++ feature, so you can
easily verify if a placement is found or not and deal with the latter. An example
is shown in the snippet below:

```cpp
if( auto res { placements.at( {8,8} ) } )
{
  std::cout << "Placement found, id: " << *res << std::endl;
}
else
{
  std::cerr << "Placement not found" << std::endl;
}
```

#### Capacity

```cpp
auto size() const noexcept;
```

Returns the number of placements of an object.

#### Modifiers

```cpp
template<typename U = std::pair<std::pair<T,T>,T>>
void insert(U&& u) noexcept;
```

In a given region, inserts a placement, an example is shown below:

```cpp
placements.insert( {{ 0,2},1} );
placements.insert( {{-2,4},2} );
```

---

```cpp
template<typename U>
void erase(U&& u) const noexcept;
```

Erases an element given its *id*. An usage example is shown below:

```cpp
if( auto id {placements.at({-10,8})} )
{
  placements.erase(*id);
  std::cout << "Erased element with id: " << *id << std::endl;
}
else
{
  std::cout << "Failed to erase, element not found" << std::endl;
}
```

#### Lookup

```cpp
template<typename U = T>
std::optional<std::pair<T,T>> find(U&& u) const noexcept;
```
Given a placement **id** obtain its **region**, an usage example
is shown below:

```cpp
using namespace electra::placement;

Placements<int32_t> placements;

placements.insert( {{4,8},9} );

if( auto id {placements.find(9)} )
{
  std::cout << "Region: (" << id->first << ","
    << id->second << ")" << std::endl;
}
else
{
  std::cout << "Could not find a region with the given placement id"
    << std::endl;
}
```

Which outputs:

`→ Region: (4,8)`

---

```cpp
std::pair<T,T> get_area() const noexcept;
```

Get the area the placement occupy; the first element is
the width and the second the height. A usage example is
shown below:

```cpp
using namespace electra::placement;

Placements<int32_t> placements;

placements.insert( {{ 0,2},1} );
placements.insert( {{-2,4},2} );

auto area { placements.get_area() };

std::cout << "Area: " << area.first << " x " << area.second << std::endl;
```

Which yields:

`→ Area: 3 x 3`

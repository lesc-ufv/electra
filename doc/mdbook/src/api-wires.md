# Wires

```cpp
template<typename T> class Wires
```

The wires class has one template parameter, it represents
the **wire type**. The wire coordinates are not relative, so
specify a type, that, for your use case, will not overflow.

### Constructors

```cpp
Wires();
```

There is a single default constructor.

### Iterators

```cpp
const_iterator::const_iterator<_Wires<T>,
  typename _Wires<T>::const_iterator> cbegin() const noexcept;
const_iterator::const_iterator<_Wires<T>,
  typename _Wires<T>::const_iterator> cend() const noexcept;
```

Objects of this class are iterable, each iteration
yields a *compact* wire, which is expanded uppon
dereferencing with the \* or -> operators; therefore
avoiding overhead during each iteration. An example
is shown below:

```cpp
#include <electra/wires.hpp>

electra::wire::Wires<int32_t> wires;

wires.insert( {{3,1},{3,2},{3,3},{3,4}} );
wires.insert( {{-1,1},{-2,1},{-2,2},{-2,3}} );

for( auto it{ wires.cbegin() }; it != wires.cend(); ++it)
{
  // Code goes here
}
```

### Public Methods

#### Capacity

```cpp
auto size() const noexcept;
```

Returns the current number of wires in the data structure.

#### Modifiers
```cpp
template<typename U = std::vector<std::pair<T,T>>>
void insert(U&& u) noexcept;
```

Inserts a wire to be automatically shrunk by *Electra*.
Example:

```cpp
// Using an r-value
wires.insert( {{3,1},{3,2},{3,3},{3,4}} );

// Using your defined wire type and lvalues
using Wire = std::vector<std::pair<int32_t,int32_t>>;

Wire w { {3,2},{3,1},{3,0},{4,0},{5,0} };

wires.insert( w );
```

---

```cpp
template<typename U = std::pair<T,T>>
void erase(U&& a, U&& b) noexcept;
```

Given a *universal* or *forwarding* reference, erases a wire using its
**initial** and **final** pair of coordinates. Example:

```cpp
// Inserts a new wire
wires.insert({{3,1},{3,2},{3,3},{3,4}});

// Removes using the first and last coordinates
wires.erase({3,1},{3,4});
```

#### Lookup

```cpp
template<typename U = std::pair<T,T>>
std::optional<const_iterator::const_iterator<_Wires<T>,
  typename _Wires<T>::const_iterator>> find(U&& a, U&& b) noexcept;
```

Returns a iterator if a wire is found between the two
coordinates, else returns **std::nullopt**. For accessing the
iterator use the \* or -> operators.

```cpp
auto get_area() const noexcept;
```

Returns the area occupied by the current wires.

#### Operations

```cpp
template<typename U>
void write(U&& filename) const noexcept;
```

Writes the current wires data structure to the
*json* format using the *forwarding* reference filename.
Example:

```cpp
wires.write( "wires.json" );
```

---

```cpp
template<typename U>
void read(U&& filename) noexcept;
```

Reads a previously written wires data structure. Example:

```cpp
wires.read("wires.json");
```

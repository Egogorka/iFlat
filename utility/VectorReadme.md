# Vector.h

This file implements the basic concept of mathematical vector.\
The basic usage:
```c++
#include "utility/Vector.h"

Vector<2,int> vec1 {1,2};
Vector<2,int> vec2 {2,1};

// { 3, 3 }
auto vec_sum = vec1 + vec2;

// { 5, 10 }
auto vec_scaled = 5 * vec1;

// outputs: 1 2
std::cout << vec1;
```
Vector implements the functionality of addition, subtraction, multiplication by scalar (left and right).\
division by scalar (only right one `vec / 2`)

For convenience the following classes are implemented
```
Vector2f, Vector2i - for pair of floats and ints
Vector3f, Vector3i - for triplet of floats and ints
```

And these classes support these methods
```
Vector2f and Vector2i : 
x(), y() - returns x and y components

Vector3f and Vector3i : 
x(), y(), z() - returns x, y and z components
getXY() - returns corresponding Vector2 with x(),y() components
```



# C++ Map Implementation with BST

This project implements a Map container in C++ using a Binary Search Tree (BST) as the underlying data structure. The implementation provides an ordered collection that maintains key-value pairs with logarithmic time complexity for most operations.

## Overview

The Map is implemented through a template-based class that maintains key-value pairs in sorted order (by key) and ensures key uniqueness. Key features include:

- Template-based implementation supporting any comparable key type and any value type
- Red-black tree balancing for guaranteed O(log n) operations
- Bidirectional iterator implementation
- Memory-efficient node management
- Support for both copy and move semantics
- STL-compatible interface

## Class Structure

### `map<K, V>`

The main map class template with two parameters:

- K: Type of key used to sort and uniquely identify elements
- V: Type of mapped value associated with each key

Key components:

- Uses a custom `BST<pair<K,V>>` as the underlying data structure
- `iterator`: Public bidirectional iterator class
- Standard container interface methods

### Constructors

- Default constructor
- Copy constructor
- Move constructor
- Range constructor (from iterators)
- Initializer list constructor

### `map<K,V>::iterator`

The iterator class provides bidirectional traversal through the map:

- Wraps the underlying BST iterator
- Supports increment/decrement operations
- Provides access to key-value pairs through pair<K,V>

### `BST<pair<K,V>>`

The underlying Binary Search Tree implementation:

- `BNode`: Internal node structure storing key-value pairs
- Red-black tree balancing for self-balancing operations
- Memory management
- Tree traversal algorithms

## Map Operations

The implementation includes several key operations:

### Core Operations

- `insert()`: Insert key-value pairs (maintains key uniqueness)
- `operator[]`: Access or insert values by key
- `at()`: Access values by key with bounds checking
- `erase()`: Remove elements by iterator, key, or range
- `find()`: Search for elements by key
- `clear()`: Delete all elements
- `swap()`: Exchange two maps
- `size()`: Count elements
- `empty()`: Check if map is empty

### Iterator Support

- `begin()`: Get iterator to first element
- `end()`: Get iterator past the last element
- Bidirectional iteration support

### Memory Management

- Efficient node reuse in assignment operations
- Proper cleanup of unused nodes
- Prevention of memory leaks

## Usage Example

```cpp
#include "map.h"

// Create a map with string keys and integer values
custom::map<string, int> m;

// Insert elements
m.insert({"apple", 5});
m.insert({"banana", 3});
m.insert({"cherry", 7});

// Access using operator[] and at()
m["date"] = 9;  // Insert new element
m["apple"] = 6; // Modify existing element
try {
    int value = m.at("banana"); // Safe access with bounds checking
} catch (const std::out_of_range& e) {
    // Handle key not found
}

// Find an element
auto it = m.find("banana");
if (it != m.end())
    std::cout << "Found: " << it->first << " -> " << it->second << std::endl;

// Iterate through the map
for (auto it = m.begin(); it != m.end(); ++it)
    std::cout << it->first << ": " << it->second << std::endl;

// Remove elements
m.erase("apple");           // Remove by key
auto it2 = m.find("banana");
if (it2 != m.end())
    m.erase(it2);          // Remove by iterator

// Check if empty
if (!m.empty())
    std::cout << "Map size: " << m.size() << std::endl;
```

## Files

- `map.h`: Main map implementation
- `bst.h`: Underlying Binary Search Tree implementation
- `pair.h`: Pair implementation for key-value storage
- `testMap.h`: Unit tests for map
- `testBST.h`: Unit tests for BST

## Implementation Details

The map is implemented using a red-black tree to ensure balanced tree operations:

- All operations maintain O(log n) time complexity
- Elements are stored in sorted order by key
- Duplicate keys are not allowed (values are updated)
- Iterator invalidation follows standard container rules
- Exception safety guarantees for element access

## Authors

Nathan Bird  
[nathanbirdka@gmail.com](mailto:nathanbirdka@gmail.com)

Brock Hoskins  
[](.)

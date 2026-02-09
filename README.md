# RISC-V Olympiad Coding Challenge

A C++17 geometric shape descriptor demonstrating extensible object-oriented design where the main program remains completely agnostic to concrete object types.

---

## How the Requirements Are Achieved

### Requirement 1: Main Program Must Not Know What Objects Are

Achieved through three design patterns:

**1. Abstract Interface**
```cpp
class Shape {
    virtual void performCalculations_() = 0;
    // ... pure virtual methods
};
```
Main program works exclusively with `Shape*` pointers. Verification: `src/main.cpp` includes only `ShapeFactory.hpp`, never concrete shape headers.

**2. Factory Pattern**
```cpp
std::unique_ptr<Shape> shape = factory.createShape("circle");
```
Objects created by string name, main never sees concrete types.

**3. Polymorphism**
```cpp
shape->calculate(params);  // Virtual dispatch to concrete implementation
```
Runtime polymorphism ensures correct behavior without type knowledge.

---

### Requirement 2: Program Must Be Extensible

Achieved through **Self-Registration Pattern**.

Each shape registers itself automatically before `main()` runs:

```cpp
// In Circle.cpp
inline bool circle_registered = registerShape<Circle>("circle");
```

**How it works:**
- Static variables initialize before `main()`
- Each shape calls `registerShape<ShapeType>("name")`
- Factory stores creation lambdas in a registry
- By the time `main()` runs, all shapes are already registered

**To add Triangle:**
1. Uncomment `src/Triangle.cpp` in `CMakeLists.txt`
2. Rebuild

**Files unchanged:** main.cpp, ShapeFactory, all other shapes.

**Supporting patterns:**
- **Singleton Factory**: Ensures all shapes register with the same instance
- **C++17 Inline Variables**: Enables clean single-line registration

---

## Building the Project

**Requirements:** C++17 compiler, CMake 3.10+

**Quick build:**
```bash
cd "Coding challenge"
./build.sh
```

**Manual build:**
```bash
mkdir -p build && cd build
cmake ..
make
```

**Output:** `build/describe_object`

---

## Usage

**Syntax:**
```bash
./build/describe_object <shape>                         # Describe
./build/describe_object <shape> <params...>             # Calculate
./build/describe_object <shape> <params...> <property>  # Query
```

**Available shapes:** circle, square, rect

**Examples:**
```bash
./build/describe_object circle 5
# Circle with radius 5.00:
#   Circumference (Perimeter): 31.42
#   Area: 78.54

./build/describe_object square 4 diagonal
# diagonal: 5.66 units

./build/describe_object rect 3 7
# Rectangle with sides 3.00 and 7.00:
#   Perimeter: 20.00
#   Area: 21.00
```

---

## Extensibility Demonstration

**Triangle** is fully implemented but not compiled by default.

**Enable Triangle:**
1. Open `CMakeLists.txt`
2. Uncomment: `# src/Triangle.cpp` → `src/Triangle.cpp`
3. Run `./build.sh`
4. Test: `./build/describe_object triangle 3 4 5`

**Files modified:** Only `CMakeLists.txt` (1 line)

**Files unchanged:** main.cpp, ShapeFactory, Circle, Square, Rectangle

When `Triangle.cpp` compiles, the self-registration line executes before `main()`, automatically registering Triangle with the factory.

---

## Project Structure

```
Coding challenge/
├── include/
│   ├── Shape.hpp           # Abstract interface
│   ├── ShapeFactory.hpp    # Factory + registration
│   ├── Circle.hpp
│   ├── Square.hpp
│   ├── Rectangle.hpp
│   └── Triangle.hpp        # Not built by default
├── src/
│   ├── main.cpp            # Shape-agnostic entry point
│   ├── Shape.cpp
│   ├── ShapeFactory.cpp
│   ├── Circle.cpp
│   ├── Square.cpp
│   ├── Rectangle.cpp
│   └── Triangle.cpp        # Not built by default
├── CMakeLists.txt
├── build.sh
└── README.md
```

---

## Summary

**Main doesn't know objects:** Abstract interfaces + Factory pattern + Polymorphism

**Extensibility:** Self-registration pattern via static initialization

**Key innovation:** Shapes register themselves automatically before `main()` runs, enabling zero-modification extensibility.

**Coding style:** [RISC-V Performance Model Coding Style](https://github.com/riscv-software-src/riscv-perf-model/blob/master/CodingStyle.md)

---

## Acknowledgments

AI assistance was used for generating boilerplate code and portions of the documentation. All core design decisions, architecture choices, and implementation logic were developed independently.

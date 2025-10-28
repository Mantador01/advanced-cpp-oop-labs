# 💻 Advanced C++ Programming and Object-Oriented Labs

This repository contains a series of C++ practical assignments from the **Advanced Programming and Object-Oriented Concepts** course, completed during the **Master 1 in Computer Science** program at **Université Claude Bernard Lyon 1**.

The goal of these labs is to deepen understanding of **object-oriented design**, **memory management (RAII)**, **polymorphism**, **templates**, and **modern C++ features** such as copy and move semantics.

---

## 🧭 Overview

Each lab focuses on a different core concept of C++ programming:

| Theme | Focus | Example File |
|--------|--------|--------------|
| RAII and Move Semantics | Resource management and move optimization | `LaClasse.cpp`, `Note.markdown` |
| Inheritance & Polymorphism | Dynamic binding and abstract classes | `Image2.cpp`, `Expression.cpp` |
| Templates & Iterators | Generic programming and custom containers | `template.cpp`, `Tableau.cpp`, `Cellule.cpp` |
| Operator Overloading | Custom string and container operations | `String.cpp` |
| Functors & Generators | Function objects and stateful operations | `MultipleGenerator.cpp` |

---

## 🧩 Project Structure

| File | Description |
|------|--------------|
| `LaClasse.cpp` | Demonstrates **RAII**, copy/move constructors, assignment operators, and destructor sequencing. |
| `Note.markdown` | Theoretical report explaining the implementation of **RAII** and **move semantics**. |
| `String.cpp` | Custom implementation of a dynamic string class with operator overloading (`+`, `==`, `<`, etc.). |
| `template.cpp` | Template examples for `myMin`, `mySwap`, with overloads and specializations for string literals. |
| `Tableau.cpp` | Implementation of a dynamic, resizable array (`Tableau<T>`) with static counters and capacity expansion. |
| `Cellule.cpp` | Implementation of a **sorted linked list** (`ListeTriee<T>`) with copy constructors and ordered insertion. |
| `Insertor.cpp` | Demonstrates use of **custom insert iterators** for generic data structures. |
| `TabIterator.cpp` | Defines a **custom iterator** class for sequential access within containers. |
| `Image.cpp` | Class `Image` implementing **copy and move semantics** for low-level pixel buffers. |
| `Image2.h` / `Image2.cpp` | `Image2` manages **polymorphic pixels** (`PixelCouleur`, `PixelNiveauDeGris`) using dynamic allocation and cloning. |
| `Expression.cpp` | Implementation of a polymorphic **arithmetic expression tree** (classes `Expression`, `Plus`, `Mult`, etc.). |
| `MultipleGenerator.cpp` | Example of a **functor** generating multiples of a given number using operator `()`. |
| `main.cpp` | Entry point for testing image and polymorphism behavior. |
| `NOTE.markdown` | Comparison between **Java and C++** memory models (manual vs. garbage-collected). |

---

## 🧠 Key Concepts

### ⚙️ RAII & Move Semantics
Implemented in `LaClasse.cpp` and explained in `Note.markdown`:
- Resource acquisition in constructors, release in destructor.
- Copy and move constructors / assignment operators.
- Ensures no memory leaks and efficient transfer of ownership.

### 🧩 Polymorphism & Inheritance
- Abstract classes (`Expression`, `Pixel`) with pure virtual methods.
- Dynamic dispatch and `clone()` pattern.
- Safe copying using **deep cloning** and **dynamic_cast**.

### 🔁 Templates & Iterators
- Generic containers (`Tableau<T>`, `ListeTriee<T>`).
- Template specialization and type-safe iterators.
- Demonstrates how to build custom STL-like abstractions.

### 🧮 Expression Trees
`Expression.cpp` builds nested expressions such as:
```cpp
const Expression& e = Mult(
    Plus(Constante(5), Constante(-2)),
    Plus(Constante(1), Constante(3))
);
std::cout << e.eval(); // Output: 12
```

### 📷 Image Polymorphism
`Image2` supports color and grayscale pixels using polymorphic objects.
```cpp
Image2 imgColor(2, 2, true);
Image2 imgGray(2, 2, false);
imgColor.afficher();
imgGray.afficher();
```

### 🧰 Custom String Class
`String.cpp` reimplements a basic string type:
- Dynamic memory management.
- Concatenation and comparison operators.
- Substring extraction and I/O streaming.

### ⚡ Functor Example
`MultipleGenerator.cpp` defines a callable object:
```cpp
MultipleGenerator gen5(5);
for (int i = 0; i < 5; ++i) std::cout << gen5() << std::endl;
```

---

## 🧪 Learning Outcomes

- Understand the **copy control** mechanism (rule of 5).
- Apply **RAII** for robust resource management.
- Build **polymorphic hierarchies** and abstract interfaces.
- Implement **templates** and **generic programming** patterns.
- Manipulate memory safely with **move semantics** and destructors.
- Understand differences between **C++** and **Java** object lifecycles.

---

## ⚙️ How to Compile and Run

### Compile all files
```bash
g++ -std=c++17 *.cpp -o app
```

### Run
```bash
./app
```

### Or compile individual demos
```bash
g++ -std=c++17 LaClasse.cpp -o laClasse && ./laClasse
g++ -std=c++17 Expression.cpp -o expression && ./expression
```

---

## 🪄 Technologies Used

| Category | Tools |
|-----------|--------|
| Language | C++17 |
| Paradigm | Object-Oriented, Generic Programming |
| IDE | CLion / Visual Studio Code / QtCreator |
| OS | Linux / Windows / macOS |

---

## 👨‍💻 Author

**Alexandre COTTIER**  
Master’s student in Computer Science – *Image, Développement et Technologie 3D (ID3D)*  
Université Claude Bernard Lyon 1  

📍 Lyon, France  
🔗 [GitHub](https://github.com/Mantador01) · [LinkedIn](https://www.linkedin.com/in/alexandre-cottier-72ab20227/)

---

## 📜 License

This repository is shared for **educational and research purposes** only.  
You are free to reuse the code with attribution.

---

> *“C++ gives you enough rope to hang yourself — or to build something extraordinary.”*

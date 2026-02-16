# ✈️ AirBooking - Airline Management System
A comprehensive airline management system developed in C++ that simulates the daily operations of a modern airline (e.g., Wizz Air). The application is an academic project completed in 3 stages, progressively demonstrating advanced concepts of Object-Oriented Programming (OOP).

![C++](https://img.shields.io/badge/C++-11-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.10+-green.svg)

---

## 📋 Table of Contents

1. [Description](#description)
2. [Features](#features)
3. [Technical Architecture](#architecture)
4. [Project Structure](#structure)
5. [Compilation and Execution](#compilation)
6. [Academic Requirements](#requirements)

---

<a name="description"></a>
## Description

**AirBooking** is an airline management system that enables:
- Flight fleet administration
- Passenger registration and management
- Check-in processing with baggage allocation
- Dynamic ticket price calculation

The project was developed in **3 incremental stages**, each adding new OOP concepts:

| Stage | Main Focus | Git Tag |
|-------|------------|---------|
| Theme 1 | Classes, constructors, operators | `v0.1` |
| Theme 2 | Inheritance, polymorphism, exceptions | `v0.2` |
| Theme 3 | Design patterns, templates | `v0.3` |
| Personal | English version | `v0.4(english)` |

---

At startup, the application executes an Auto-Load and Auto-Save procedure:

- **Loading**: Data is read from `data.txt` (flights, passengers, configurations)
- **Saving**: Any modification is automatically saved when closing the program to `data.txt`
- **Pre-configuration**: The system comes with 3+ flights and passengers already defined for quick testing

---

<a name="features"></a>
## ✨ Features

### 🛫 Flight Management

- Add, search, and remove flights
- Update boarding gates and monitor capacity in real-time
- Sort by revenue, occupancy rate, or destination
- Filter full/available flights

### 👥 Passenger Management

- Passenger registration with complete validations
- Check-in system with baggage allocation
- Upgrade between fare classes with cost recalculation

### 🎫 Ticket System

Using Factory Method (`TicketFactory`), the application supports **4 ticket classes**:

| Class | Base Fee | Benefits |
|-------|----------|----------|
| Economy | €3.00 | Standard |
| Premium | €45.00 | Free drink, priority boarding |
| Business | €35.50 | Lounge access, extra comfort |
| First Class | €74.75 | Meal, VIP lounge, priority |

> **Note**: Final price = Base price + Airport tax (€15.75) + Class fee + Options - Discount

### 🧳 Baggage System (`Baggage`)

*Usage condition*: Adding baggage is only available after completing the Check-In process. Fees are calculated and added directly to the final ticket price.

| Baggage Type | Max Weight | Fee |
|--------------|------------|-----|
| Personal Item | 10 kg | Free |
| Carry-on | 10 kg | €20 |
| Checked Small | 23 kg | €35 |
| Checked Large | 32 kg | €50 |

> *Surcharge*: €15/kg for exceeding the weight limit


---

<a name="architecture"></a>
## 🔧 Technical Architecture

### 🏗️ Implemented Design Patterns

| Pattern | Implementation | Purpose |
|---------|----------------|---------|
| **Factory Method** | `TicketFactory` | Dynamic creation of ticket types |
| **Strategy** | `SortStrategy` | Interchangeable sorting algorithms |

### ⚠️ Exception Hierarchy

```cpp
FlightException (base)
├── ValidationException    // Invalid input data (seat format, gate, discount)
├── CapacityException      // Overbooking attempt (full flight)
└── OperationException     // Invalid actions (existing passenger, occupied seat)
```

### 🛡️ Implemented Validations

| Field | Format | Examples |
|-------|--------|----------|
| Seat | `[1-99][A-Z]` | 12A, 5B |
| Gate | `[A-Z][1-99]` | A12, B5 |
| Discount | 0% - 80% | 15, 50 |

---

<a name="structure"></a>
## 📂 Project Structure
```
/
├── headers/                # Class interfaces (.h)
│   ├── Airline.h           # Central system manager
│   ├── Flight.h            # Per-flight logic
│   ├── Passenger.h         # Passenger entity
│   ├── Ticket.h            # Ticket hierarchy + ILoungeAccess
│   ├── Baggage.h           # Baggage fee logic
│   ├── CheckIn.h           # Boarding process
│   ├── Exceptions.h        # Custom error classes
│   ├── Repository.h        # Generic template for collections
│   ├── SortStrategy.h      # Strategy Pattern for sorting
│   └── Utils.h             # Helpers (validations, UI, price formatting)
├── Pattern/
│   └── TicketFactory.h     # Factory Design Pattern implementation
├── src/                    # Method implementations (.cpp)
│   ├── Airline.cpp
│   ├── Flight.cpp
│   ├── Passenger.cpp
│   ├── Ticket.cpp
│   ├── Baggage.cpp
│   └── CheckIn.cpp
├── input/                  # I/O modules
│   ├── populateData.h      # File reading logic
│   └── saveData.h          # File writing logic
├── main.cpp                # Entry point (Interactive Menu)
└── data.txt                # Text database
```

---

<a name="compilation"></a>
## ⚙️Compilation and Execution

## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# sau ./scripts/cmake.sh configure
```

Sau pe Windows cu GCC folosind Git Bash:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
# sau ./scripts/cmake.sh configure -g Ninja
```

Pentru a configura cu ASan, avem opțiunea `-DUSE_ASAN=ON` (nu merge pe Windows cu GCC):
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DUSE_ASAN=ON
# sau ./scripts/cmake.sh configure -e "-DUSE_ASAN=ON"
```


La acest pas putem cere să generăm fișiere de proiect pentru diverse medii de lucru.


2. Pasul de compilare
```sh
cmake --build build --config Debug --parallel 6
# sau ./scripts/cmake.sh build
```

Cu opțiunea `parallel` specificăm numărul de fișiere compilate în paralel.


3. Pasul de instalare (opțional)
```sh
cmake --install build --config Debug --prefix install_dir
# sau ./scripts/cmake.sh install
```

Vezi și [`scripts/cmake.sh`](scripts/cmake.sh).

Observație: folderele `build/` și `install_dir/` sunt adăugate în fișierul `.gitignore` deoarece
conțin fișiere generate și nu ne ajută să le versionăm.


## Instrucțiuni pentru a rula executabilul

Există mai multe variante:

1. Din directorul de build (implicit `build`). Executabilul se află la locația `./build/oop` după ce a fost rulat pasul de compilare al proiectului (`./scripts/cmake.sh build` - pasul 2 de mai sus).

```sh
./build/oop
```

2. Din directorul `install_dir`. Executabilul se află la locația `./install_dir/bin/oop` după ce a fost rulat pasul de instalare (`./scripts/cmake.sh install` - pasul 3 de mai sus).

```sh
./install_dir/bin/oop
```

3. Rularea programului folosind Valgrind se poate face executând script-ul `./scripts/run_valgrind.sh` din rădăcina proiectului. Pe Windows acest script se poate rula folosind WSL (Windows Subsystem for Linux). Valgrind se poate rula în modul interactiv folosind: `RUN_INTERACTIVE=true ./scripts/run_valgrind.sh`

Implicit, nu se rulează interactiv, iar datele pentru `std::cin` sunt preluate din fișierul `date.txt`.

```sh
RUN_INTERACTIVE=true ./scripts/run_valgrind.sh
# sau
./scripts/run_valgrind.sh
```

4. Pentru a rula executabilul folosind ASan, este nevoie ca la pasul de configurare (vezi mai sus) să fie activat acest sanitizer. Ar trebui să meargă pe macOS și Linux. Pentru Windows, ar merge doar cu MSVC (nerecomandat).

Comanda este aceeași ca la pasul 1 sau 2. Nu merge combinat cu Valgrind.

```sh
./build/oop
# sau
./install_dir/bin/oop
```

--- 

<a name ="requirements"></a>
## Academic Requirements

## 🎓 Theme 1
#### Requirements
- [x] definition of at least **3-4 classes** using composition with your own defined classes; inheritance is not considered here
- [x] initialization constructors with parameters for each class
- [x] for one (single) class: copy constructor, copy `operator=`, destructor
<!-- - [ ] for another class: move constructor, move `operator=`, destructor -->
<!-- - [ ] for another class: all 5 special member functions -->
- [x] `operator<<` for **all** classes for display (`std::ostream`) using composed calls with `operator<<`
- [x] as many `const` as possible (where applicable) and `private` functions
- [x] implementation of at least 3 public member functions for non-trivial functionalities specific to the chosen theme, of which at least 1-2 more complex functions
  - not just reads/displays or adding/removing elements to/from a vector
- [x] **meaningful** usage scenario of the defined classes:
  - creating objects and calling all public member functions in main
  - only examples of keyboard input data will be added to the `data.txt` file (if any); if you need data from files, create separate files

## Theme 2
#### Requirements
- [x] separation of class code into `.h` (or `.hpp`) and `.cpp`
- [x] inheritance:
  - at least one base class and **3 derived classes** from the same hierarchy
  - the hierarchy must have its own base, not derived from a predefined class
  - [x] (pure) virtual functions called through base pointers from the class containing the base pointer type attribute
    - at least one virtual function must be **theme-specific** (i.e. not simple reads/displays or taken from libraries i.e. draw/update/render)
    - virtual constructors (clone): are necessary, but are not considered theme-specific functions
    - virtual display, non-virtual interface
  - [x] calling the base class constructor from derived constructors
  - [x] class with pointer attribute to a base class with derivatives; here you call virtual functions through base pointer, possibly through the non-virtual interface from base
    - [x] overridden cc/op= for correct copies/assignments, copy and swap
    - [x] `dynamic_cast`/`std::dynamic_pointer_cast` for meaningful downcast
    - [x] smart pointers (recommended, optional)
- [x] exceptions
  - [x] own hierarchy with base `std::exception` or derived from `std::exception`; at least **3** classes for distinct specific errors
    - exception classes must handle distinct error categories (example of equivalent errors: reading files with various extensions)
  - [x] meaningful usage: for example, `throw` in constructor (or function that returns an object), `try`/`catch` in `main`
  - this hierarchy will be completely independent of the hierarchy with virtual functions
- [x] `static` functions and attributes
- [x] STL
- [x] as many `const` as possible
- [x] *high-level* functions, eliminate as many getters/setters/low-level functions as possible
- [x] at the end: separate commit with adding a new derived class without modifying the rest of the code, **in addition to the 3 derivatives already added** from the same hierarchy
  - the new derivative cannot be an existing one that was deleted and added again
  - the new derivative will be integrated into the existing code (i.e. it will be used, not just added for the sake of it)

## Theme 3
#### Requirements
- [x] 2 design patterns
- [x] a meaningful template class; at least **2 instantiations**
  - [x] preferably also a meaningful template function; at least 2 instantiations

# Healthcare Patient, Employee, & Equipment Management System

A C++ console application that manages patient records, employees, visits, durable medical equipment, depreciation, and typed storage-unit inventories for the fictional Health Care Options (HCO) organization.

This project began as a university C++ programming course project and was independently completed, tested, and polished afterward as a public C++ foundations portfolio project.

> This is a programming simulation, not clinical software. All included people and records are fictional demo data.

![C++ CI](https://github.com/charliecleere/healthcare-management/actions/workflows/ci.yml/badge.svg)

## Highlights

- **Patient lifecycle** — CRUD, BPM analytics, visit history, case-manager assignment, and file import/export
- **Staff modeling** — Nurse, aide, and case-manager types built on a shared employee base class
- **Equipment reporting** — Polymorphic depreciation schedules (straight-line and double-declining-balance)
- **Inventory management** — Type-safe template storage units with input validation
- **Engineering quality** — CMake presets, automated unit tests (CTest), MSVC `/W4` warnings, and GitHub Actions CI

## C++ Concepts Demonstrated

Built in C++17 as a modular static library (`hco_core`) linked by the application and test targets.

### Classes, composition, and STL containers

Builds a healthcare management system by combining small pieces of code, where each piece does one specific job, rather than using one large, complicated piece that does everything.

- `Patient` contains `Visit`, `CaseManager`, and `std::vector` collections for BPM readings and visit history ([`Patient.h`](Patient.h))
- `Visit` contains `Nurse`, `Aide`, and a `std::vector<Service>` for per-visit care records ([`Visit.h`](Visit.h))
- `Date` provides shared calendar functionality for visits, equipment, and storage units ([`Date.h`](Date.h))

### Dynamic memory and the Rule of Three

Demonstrates explicit ownership of heap-allocated resources in a pre-smart-pointer style appropriate for foundational C++ coursework.

- `Employee` stores identity fields on the heap with a copy constructor, destructor, and assignment operator ([`Employee.h`](Employee.h), [`Employee.cpp`](Employee.cpp))
- `Main.cpp` manages dynamically allocated employee arrays for nurses, aides, and case managers

### Inheritance and polymorphism

Uses virtual methods so shared reporting logic operates on base pointers without knowing the concrete type.

- `Nurse`, `Aide`, and `CaseManager` extend `Employee` with role-specific fields and reports
- `MonitorEquipment` and `MobilityEquipment` override virtual `depreciate()` and `printDetails()` on the `Equipment` base ([`Equipment.h`](Equipment.h))

### Operator overloading

Custom operators keep console output and sorting logic close to the domain types.

- `Patient`: stream output (`operator<<`), alphabetical sort (`operator<`), and age increment (prefix/postfix `operator++`) ([`Patient.h`](Patient.h))
- `Date`: stream output for formatted display ([`Date.h`](Date.h))
- `Equipment`: less-than comparison for sorted inventory reports ([`Equipment.h`](Equipment.h))

### Recursion

Depreciation schedules are generated recursively, one period at a time, until the salvage-value floor is reached.

- Straight-line depreciation in `MonitorEquipment` ([`MonitorEquipment.h`](MonitorEquipment.h))
- Double-declining-balance depreciation in `MobilityEquipment` ([`MobilityEquipment.h`](MobilityEquipment.h))

### Templates

Generic code eliminates duplication while keeping type-safe inventories for each equipment category.

- `StorageUnit<T>` provides shared rental, validation, sorting, and reporting behavior for any equipment type ([`StorageUnit.h`](StorageUnit.h))
- Templated employee loaders and sorters in [`Main.cpp`](Main.cpp)

### Exceptions and validation

Custom exception types enforce business rules at the point of invalid input.

- `DuplicateIdException`, `InvalidDateException`, and `NegativeNumberException` with descriptive `what()` messages
- Leap-year-aware date parsing and duplicate visit-ID detection
- Negative-dimension and negative-cost guards on storage units

### File I/O and console UX

A menu-driven workflow loads startup data from `.txt` files and exports patient reports on demand.

- Startup loading for services, employees, and equipment in [`Main.cpp`](Main.cpp)
- Patient report export and interactive input validation across all menus

## Tech Stack and Quality

- **Language:** C++17 (compiler extensions disabled for portability)
- **Build:** CMake 3.20+ with presets (`ninja-debug`, `vs2022-debug`) — see [`CMakeLists.txt`](CMakeLists.txt), [`CMakePresets.json`](CMakePresets.json)
- **Tests:** CTest suite in [`tests/CoreTests.cpp`](tests/CoreTests.cpp) covering date validation, visits, storage units, depreciation, and exceptions
- **CI:** GitHub Actions on `windows-latest` with Release builds (see [`.github/workflows/ci.yml`](.github/workflows/ci.yml))

> **Note:** This project is configured and tested on Windows. While the CMake setup includes cross-platform compiler flags, other platforms (Linux, macOS) are not officially supported or tested.

## Architecture at a Glance

- **Application layer** — [`Main.cpp`](Main.cpp): interactive menus, file loading, search/sort helpers, and formatted reports
- **Domain layer** — `Patient`, `Visit`, `Service`, `Date`, employee hierarchy (`Employee` → `Nurse` / `Aide` / `CaseManager`), equipment hierarchy (`Equipment` → `MonitorEquipment` / `MobilityEquipment`), and `StorageUnit<T>`
- **Infrastructure** — `hco_core` static library, post-build copy of demo `.txt` data files, and CTest harness

## Quick Start

**Prerequisites:** Windows, Visual Studio 2022 with the **Desktop development with C++** workload, and VS Code with the **C/C++** and **CMake Tools** extensions (see [`.vscode/extensions.json`](.vscode/extensions.json)).

**Run in VS Code (recommended):**

1. Open this repository folder in VS Code.
2. When prompted, select the **`ninja-debug`** CMake preset.
3. Press **`F5`** and choose **Run Healthcare Management**.
4. Enter **`4`** at the main menu to exit.

For future runs, open the folder and press **`F5`**.

> If CMake fails to configure, confirm the C++ workload is installed, then run **Developer: Reload Window** from the Command Palette. Workspace settings load the Visual Studio developer environment automatically — no Developer Command Prompt required.

> Do not choose **C/C++: cl.exe build and debug active file**; that option compiles only the active `.cpp` file, not this multi-file CMake project.

### Run from a Terminal

Open **Developer PowerShell for VS 2022** in the repository folder:

```powershell
cmake --preset ninja-debug
cmake --build --preset ninja-debug
ctest --preset ninja-debug --output-on-failure
.\build\ninja-debug\healthcare_management.exe
```

A Visual Studio generator preset (`vs2022-debug`) is also available in [`CMakePresets.json`](CMakePresets.json).

The build copies demo `.txt` data files beside the executable.

## Sample Workflow

After launching the app, try this short path to see the main features:

1. **Import a demo patient** — Main menu `1` → `2` (Read patient information from file) → enter `Demo Patient Aurora` (no `.txt` extension).
2. **View the patient report** — `7` (Print patient report to screen) to see demographics, BPM statistics, visits, and case-manager assignment.
3. **View employee data** — `9` to return to the main menu, then `2` → `1` to print the nurse, aide, and case-manager report loaded at startup.
4. **Run a depreciation schedule** — Main menu `3` → `2` → enter equipment ID `2501` for straight-line monitor depreciation, or `1001` for double-declining-balance mobility depreciation.
5. **Exit** — Return to the main menu (`6` from Equipment, or `2` from Employee) and enter `4`.

For a full interactive regression pass, see [`docs/manual-test-checklist.md`](docs/manual-test-checklist.md).

## Project Structure

- [`Main.cpp`](Main.cpp) — interactive menu flow and file loading
- Domain headers and sources — patients, staff, services, visits, equipment, and storage units
- [`tests/CoreTests.cpp`](tests/CoreTests.cpp) — automated unit tests via CTest
- [`CMakeLists.txt`](CMakeLists.txt) / [`CMakePresets.json`](CMakePresets.json) — build configuration and presets
- [`docs/manual-test-checklist.md`](docs/manual-test-checklist.md) — interactive regression checklist

## License

Released under the [MIT License](LICENSE).

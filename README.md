# HCO Patient & Equipment Management

A C++ console application that models patient records, home-health employees, visits, durable medical equipment, depreciation, and typed storage-unit inventories for the fictional Health Care Options (HCO) organization.

This project began as a CSCN 112 course project and was independently completed, tested, and polished afterward as a public C++ foundations portfolio project.

> This is a programming simulation, not clinical software. All included people and records are fictional demo data.

## Highlights

- Patient records with BPM statistics, visit history, case-manager assignment, reporting, and file import/export
- Employee inheritance hierarchy for nurses, aides, and case managers
- Equipment polymorphism with recursive straight-line and double-declining-balance depreciation reports
- Template-based storage units that route monitor and mobility equipment into type-safe inventories
- Exception-driven validation for duplicate visit IDs, invalid dates, and negative storage-unit values
- Reproducible CMake build, CTest coverage, and Windows GitHub Actions CI

## C++ Concepts Demonstrated

| Concept | Where it appears |
| --- | --- |
| Classes, composition, and vectors | Patients, visits, services, and BPM readings |
| Dynamic memory | Employee data stored in dynamically allocated arrays and objects |
| Inheritance and polymorphism | Employee and equipment hierarchies |
| Operator overloading | Patient output, patient age increment, and sorting comparisons |
| Recursion | Equipment depreciation schedule generation |
| Templates | Storage units and reusable client helpers |
| Exceptions | Duplicate IDs, invalid dates, and negative values |
| File I/O | Startup data loading and patient report export |

## Build and Run

Requirements: CMake 3.20+ and a C++17 compiler. Visual Studio 2022 Community/MSVC is the primary Windows toolchain.

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
.\build\Debug\healthcare_management.exe
```

The build automatically copies the included fictional `.txt` data files beside the executable. To import a sample patient, choose **Read patient information from file** and enter a filename such as `Demo Patient Aurora` without the `.txt` extension.

## Project Structure

- `Main.cpp` contains the interactive menu flow and file loading.
- Domain classes model patients, staff, services, visits, equipment, and storage units.
- `tests/CoreTests.cpp` covers the core model behaviors through CTest.
- `docs/manual-test-checklist.md` lists the complete interactive regression checklist.

## License

Released under the [MIT License](LICENSE).

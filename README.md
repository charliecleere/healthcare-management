# HCO Patient & Equipment Management

A C++ console application that models patient records, home health employees, visits, durable medical equipment, depreciation, and typed storage-unit inventories for the fictional Health Care Options (HCO) organization.

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

Requirements: CMake 3.20+ and a C++17 compiler. Visual Studio 2022 Community/MSVC is the primary Windows toolchain, and Ninja is the easiest option for VS Code use.

```powershell
cmake --preset ninja-debug
cmake --build --preset ninja-debug
ctest --preset ninja-debug --output-on-failure
.\build\ninja-debug\healthcare_management.exe
```

For Visual Studio 2022, you can also use the `vs2022-debug` preset:

```powershell
cmake --preset vs2022-debug
cmake --build --preset vs2022-debug
ctest --preset vs2022-debug --output-on-failure
.\build\vs2022-debug\Debug\healthcare_management.exe
```

In VS Code, install the recommended Microsoft C/C++ and CMake Tools extensions when prompted. Open the repository folder and let CMake Tools configure the `ninja-debug` preset. Then use the Run button or press `F5`; choose `Run Healthcare Management` if VS Code asks which launch configuration to use. This launch configuration builds and runs the complete CMake target, including every `.cpp` file.

Do not choose `C/C++: cl.exe build and debug active file`. That generic option compiles only the currently open source file and requires a Visual Studio Developer Command Prompt, so it is not the project’s CMake workflow.

The build automatically copies the included fictional `.txt` data files beside the executable. To import a sample patient, choose **Read patient information from file** and enter a filename such as `Demo Patient Aurora` without the `.txt` extension.

## Project Structure

- `Main.cpp` contains the interactive menu flow and file loading.
- Domain classes model patients, staff, services, visits, equipment, and storage units.
- `tests/CoreTests.cpp` covers the core model behaviors through CTest.
- `docs/manual-test-checklist.md` lists the complete interactive regression checklist.

## License

Released under the [MIT License](LICENSE).

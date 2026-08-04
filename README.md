# HCO Patient & Equipment Management

A C++ console application that models patient records, home health employees, visits, durable medical equipment, depreciation, and typed storage-unit inventories for the fictional Health Care Options (HCO) organization.

This project began as a university C++ programming course project and was independently completed, tested, and polished afterward as a public C++ foundations portfolio project.

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

## Run in VS Code (Recommended)

### One-time setup

Install the following on Windows:

1. **Visual Studio 2022 Community** with the **Desktop development with C++** workload. This supplies the MSVC compiler, CMake, and Ninja used by the project.
2. **Visual Studio Code** with the recommended extensions when VS Code prompts you:
   - Microsoft C/C++
   - Microsoft CMake Tools

### First run

1. Open this repository's folder in VS Code.
2. Press `Ctrl+Shift+P`, run **Developer: Reload Window**, and wait for CMake Tools to configure the project.
3. If VS Code asks for a configure preset, choose **`ninja-debug`**.
4. Press `F5`.
5. If VS Code asks for a launch configuration, choose **Run Healthcare Management**.
6. The application opens in VS Code's integrated terminal. Enter `4` at the main menu to exit.

For future runs, open the folder and press `F5`. VS Code remembers the selected project configuration.

> Do not choose **C/C++: cl.exe build and debug active file**. That generic option tries to compile only the currently open `.cpp` file, while this is a multi-file CMake project.

### If VS Code shows a CMake error

1. Confirm Visual Studio's **Desktop development with C++** workload is installed.
2. Run **Developer: Reload Window** from the Command Palette.
3. Wait for CMake Tools to configure again, then press `F5` and select **Run Healthcare Management**.

This repository's workspace settings automatically load Visual Studio's developer environment, allowing CMake Tools to find MSVC and Ninja without manually opening a Developer Command Prompt.

## Run from a Terminal

Open **Developer PowerShell for VS 2022** in the repository folder, then run:

```powershell
cmake --preset ninja-debug
cmake --build --preset ninja-debug
ctest --preset ninja-debug --output-on-failure
.\build\ninja-debug\healthcare_management.exe
```

For the Visual Studio generator instead of Ninja, use the `vs2022-debug` preset:

```powershell
cmake --preset vs2022-debug
cmake --build --preset vs2022-debug
ctest --preset vs2022-debug --output-on-failure
.\build\vs2022-debug\Debug\healthcare_management.exe
```

The build automatically copies the included fictional `.txt` data files beside the executable. To import a sample patient, choose **Read patient information from file** and enter a filename such as `Demo Patient Aurora` without the `.txt` extension.

## Project Structure

- `Main.cpp` contains the interactive menu flow and file loading.
- Domain classes model patients, staff, services, visits, equipment, and storage units.
- `tests/CoreTests.cpp` covers the core model behaviors through CTest.
- `docs/manual-test-checklist.md` lists the complete interactive regression checklist.

## License

Released under the [MIT License](LICENSE).

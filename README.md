# HCO Patient & Equipment Management

A polished C++ console application that models patient records, home-health employees, visits, durable medical equipment, depreciation schedules, and typed storage-unit inventories for the fictional Health Care Options (HCO) organization.

Originally developed across eight CSCN 112 labs and later cleaned up and refactored, this repository is intended as a portfolio-quality demonstration of solid C++ foundations and good engineering practices.

> This is a programming simulation for learning and demonstration purposes, not clinical software. All people and records are fictional.

Table of contents
- Quick start (C++17, CMake) — build & run in a few commands
- What this project demonstrates — C++ concepts and design decisions
- Project structure & lab mapping
- How to run (short platform notes)
- Contributing, license, contact

Quick start (recommended)
- Requirements: C++17-capable compiler (g++, clang, or MSVC), CMake 3.20+ (or the version your platform recommends), Git

1. Clone the repository:
   git clone <repo-url>
2. Create a build folder and configure with CMake (recommended):
   mkdir build && cd build
   cmake -S .. -B . -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=17
3. Build and run:
   cmake --build . --config Release
   ./healthcare_management   # on Windows use healthcare_management.exe

Quick single-file compile (for quick smoke test on Unix-like systems)
- g++ -std=c++17 -O2 src/*.cpp -Iinclude -o healthcare_management
- ./healthcare_management

Visual Studio (Windows)
- Open the repository folder in Visual Studio (File → Open → Folder). The included CMakeLists.txt provides presets for Ninja and MSVC. After configuration, build and run from the IDE.

What to expect when you run it
- A console menu drives adding/listing patients and appointments, importing demo patient data, running reports (including equipment depreciation), and saving state to text files.
- The program ships with small sample data files in data/ (copied next to the executable at build time).

C++ Concepts Demonstrated (portfolio-focused)
This section is intentionally explicit so reviewers and recruiters can quickly see what skills the project highlights.

- Modern build & tooling
  - CMake-based build with presets for reproducible configuration and CI-friendly commands.
- Modularity & project structure
  - Clear separation between the interactive layer (menu & CLI), domain model (Patient, Visit, Employee, Equipment), and persistence layer (file load/save).
- Classes, encapsulation, and composition
  - Domain objects model real entities with constructors, accessors, and small, testable member functions.
- Ownership & resource management (RAII)
  - Files, streams, and heap-allocated resources are managed with deterministic cleanup patterns.
- Smart pointers & value semantics
  - std::unique_ptr and std::shared_ptr used where ownership and shared lifetimes are appropriate; move semantics used to avoid unnecessary copies.
- Polymorphism & inheritance
  - Employee and Equipment hierarchies expose abstract interfaces and virtual functions for extendable behavior (e.g., depreciation calculation).
- Templates and type-safe containers
  - Generic storage-unit templates enable compile-time type routing and safer inventories.
- STL & algorithms
  - std::vector, std::map, and standard algorithms keep the code concise and expressive.
- Error handling & exceptions
  - Validation and error conditions use exceptions with clear messages and safe cleanup.
- File I/O & simple serialization
  - Text-based persistence format for records; import/export utilities decoupled from domain logic.
- Test-friendly design
  - Core logic is written to be testable via small functions; unit tests (CTest) demonstrate behavior for key components.

Project structure (high level)
- src/        — source files and implementation
- include/    — public headers (if used)
- data/       — example data files used by the program (copied into build output)
- tests/      — CTest-based unit tests (e.g., tests/CoreTests.cpp)
- docs/       — lab instructions and manual test checklist

Example file references (for reviewers)
- Main program entry: [C:/Users/cclee/OneDrive/Coding Projects/healthcare-management/src/Main.cpp]
- Core domain code: [C:/Users/cclee/OneDrive/Coding Projects/healthcare-management/src/Patient.cpp] and corresponding headers
- Tests: [C:/Users/cclee/OneDrive/Coding Projects/healthcare-management/tests/CoreTests.cpp]
- Lab instructions (original assignment documents): <C:/Users/cclee/OneDrive - Liberty University/LU Spring 2026/CSCN 112/Lab Instructions>

Lab mapping (high level)
- The codebase grew incrementally across eight labs; expect the commit history or the docs/manual-test-checklist.md to show which labs introduced each feature (e.g., patient model, visits, inheritance, templates, persistence).

How to run (short platform notes)
- Windows (recommended development flow): Use Visual Studio or Developer PowerShell and the provided CMake presets. Example (PowerShell):
  cmake --preset ninja-debug
  cmake --build --preset ninja-debug
  .\build\ninja-debug\healthcare_management.exe

- macOS / Linux: Use the CMake recommended flow above or the single-command g++ example for quick testing.

Notes for reviewers
- Look for clear ownership semantics (where unique_ptr is used), concise functions, and single-responsibility classes.
- See tests/ for small, focused checks that demonstrate expected behavior.

Contributing
- Suggestions and PRs are welcome. Please open issues for proposed changes and keep PRs focused and incremental.

License
- Released under the MIT License. See [LICENSE](LICENSE) for details.

Contact
- [Your Name] — link to your GitHub profile or email (add preferred contact information here).

---

If you want any of the following adjustments, tell me and I will update and recommit:
- Add explicit C++20 notes (current README recommends C++17)
- Add direct links to additional source files or refactor the "Example file references" into relative repository links
- Shorten the README further for a recruiter-friendly one-page view


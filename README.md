# Tierazon

Tierazon is a classic Windows fractal generator originally written by Stephen C. Ferguson.

This repository contains a modernized build of the original Tierazon source, updated so it can be compiled and run with current Visual Studio tools while preserving the original fractal formulas, filters, and behaviour as closely as possible.

## Modernization work

This version includes:

- 64-bit Windows support
- Visual Studio 2022 compatibility
- Conversion of legacy C source files to C++
- Removal of the external `rsx_fv25.dll`
- Static integration of the RSX formula and filter code
- Removal of obsolete DLL loader code
- Removal of old batch build files
- Modernized project settings
- Cleanup of compiler warnings and legacy type issues
- Preservation of original Tierazon formulas and filters for reference and comparison

## Purpose

The main goal is to preserve Tierazon as a working reference implementation.

It is also being used as a comparison baseline for modern fractal rendering work in ManpWIN, including formula behaviour, filters, palettes, and iteration methods.

## Build

The project currently builds with:

- Visual Studio 2022
- x64 Release configuration
- Microsoft Foundation Classes (MFC)
- Windows 10 or later

Open:

```text
Tierazon.sln
```

## Historical note


Tierazon was created by Stephen C. Ferguson and represents an important part of the early Windows fractal-generation era.

The program contains a large collection of fractal formulas, filters, colouring methods, transformations, and experimental rendering techniques developed during a period when much of this work was shared as standalone Windows programs and dynamically loaded formula libraries.

The original Tierazon source reflects the development tools and programming techniques of its time, including older Microsoft Foundation Classes, 32-bit Windows assumptions, C source modules, and the external `rsx_fv25.dll` formula and filter library.

This repository does not attempt to redesign Tierazon or replace its original mathematical behaviour. The aim is to preserve Stephen Ferguson's work while updating the surrounding build infrastructure sufficiently for the program to compile and run on modern 64-bit Windows systems.

Where practical, the original formulas, filters, colouring behaviour, and numerical quirks are retained so that this version can also serve as a historical and mathematical reference.


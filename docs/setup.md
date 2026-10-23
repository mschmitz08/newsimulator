# Setup

## Confirmed toolchain

- Visual Studio 2026 Community 18.11.0
- Unreal Engine 5.8
- Windows development with DirectX 12

Epic's UE 5.8 documentation lists Visual Studio 2026 18.0 or later as supported and recommended for general Windows development.

## Required local software

1. Install Epic Games Launcher.
2. Install the latest Unreal Engine 5.8 hotfix available in the launcher.
3. In Visual Studio Installer, enable `Game development with C++` and the Unreal Engine tooling/components offered by Visual Studio.
4. Ensure a current Windows SDK is installed. Epic recommends Windows SDK 10.0.26100 or newer for UE 5.8.
5. Install Git LFS.

## Opening the project

1. Clone or pull `mschmitz08/newsimulator`.
2. Double-click `NewSimulator.uproject`.
3. If Unreal asks to rebuild missing modules, choose Yes.
4. If project files are needed, right-click `NewSimulator.uproject` in Windows Explorer and choose `Generate Visual Studio project files`, then open the generated solution.
5. Let Unreal compile shaders and build derived data.
6. Open or create an empty level and press Play. The game mode automatically spawns the procedural city, basic sun/skylight, and free-flight pawn for Version 0.1 validation.

## Controls

- W A S D: move
- Mouse: look
- Q / E: descend / ascend
- Left Shift: sprint
- Escape: release cursor
- Left mouse: recapture cursor

## First validation report

Report C++ compile errors first. Also report Unreal Build Tool errors, plugin errors, shader compilation failures, crashes, rendering warnings, input problems, or unexpected blank/black scenes.

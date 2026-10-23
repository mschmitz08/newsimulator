# Setup

## Toolchain gate

Do not select the final Unity or HDRP version until the local Visual Studio version is confirmed. The project requirement is to keep Unity, HDRP, .NET, and C# compatibility explicit rather than silently selecting an incompatible combination.

If the stated IDE is "Visual Studio 2016", clarify whether that means Visual Studio 2015, Visual Studio 2017, or Visual Studio 2026 because Microsoft did not release a Visual Studio 2016 product.

## Intended editor configuration

1. Install the compatible Unity Editor version through Unity Hub.
2. Create or open this repository as a Unity HDRP project.
3. Ensure the High Definition Render Pipeline package is installed.
4. Use Force Text serialization and Visible Meta Files.
5. Run `New Simulator > Generate Version 0.1 Demo Scene`.
6. Run `New Simulator > Validate Project Setup`.
7. Open the generated scene and enter Play Mode.

## Controls

- W A S D: move
- Mouse: look
- Left Shift: sprint
- Q / E: move down/up in free-flight mode
- F: toggle free-flight
- Escape: release mouse cursor
- Left mouse button: recapture mouse cursor

## Git

Install Git LFS before adding large binary assets. Unity generated cache folders are excluded by `.gitignore`.

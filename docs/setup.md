# Setup

## Confirmed toolchain

The local IDE has been confirmed as Visual Studio 2026 Community, stable channel, version 18.11.0.

The project is pinned to Unity 6.3 LTS, editor version 6000.3.27f1. Unity 6.3 is the current long-term-support line and is the preferred baseline for this serious long-term project rather than a shorter-lived Update release.

HDRP is provided as the Unity 6.3 core package line and the project manifest currently requests `com.unity.render-pipelines.high-definition` 17.2.0. Visual Studio integration is provided by `com.unity.ide.visualstudio`.

## Required local software

1. Visual Studio 2026 Community 18.11.0 or newer compatible update.
2. In Visual Studio Installer, enable the `Game development with Unity` workload.
3. Install Unity Hub.
4. Install Unity 6000.3.27f1 through Unity Hub with Windows Build Support if Windows standalone builds are desired.
5. Install Git LFS before adding large binary assets.

## Opening the project

1. Clone or pull `mschmitz08/newsimulator`.
2. In Unity Hub, choose Add project from disk and select the repository root.
3. Open it with Unity 6000.3.27f1.
4. Allow Unity Package Manager to restore the packages from `Packages/manifest.json`.
5. Wait for the initial script and shader import to finish.
6. If Unity prompts to upgrade or repair HDRP project settings, use the HDRP Wizard recommendations and report anything it changes unexpectedly.
7. Set Visual Studio 2026 as the external script editor if Unity does not detect it automatically.
8. Run `New Simulator > Validate Project Setup`.
9. Run `New Simulator > Generate Version 0.1 Demo Scene`.
10. Open `Assets/Scenes/Version01Demo.unity` and enter Play Mode.

## Controls

- W A S D: move
- Mouse: look
- Left Shift: sprint
- Q / E: move down/up in free-flight mode
- F: toggle free-flight
- Escape: release mouse cursor
- Left mouse button: recapture mouse cursor

## First local validation report

Please report any red compiler errors first. Also report package restore failures, HDRP Wizard warnings, magenta materials, missing shaders, broken scene generation, or camera input problems. Unity itself cannot be executed through the GitHub connector, so local Editor validation is the final check for this milestone.

## Git

Unity generated cache folders are excluded by `.gitignore`. Keep `Library`, `Temp`, `Logs`, `obj`, build output, and IDE-generated project files out of source control. Use Git LFS for large textures, models, audio, video, and other appropriate binary assets.

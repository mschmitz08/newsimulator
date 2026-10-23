# Current Status

## Development state

The previous Unity foundation has been intentionally replaced. New Simulator is now an Unreal Engine 5.8 C++ project.

Implemented in the Unreal restart:

- Unreal-specific `.gitignore` and Git LFS patterns
- `NewSimulator.uproject` targeting Unreal Engine 5.8
- C++ runtime module and game/editor targets
- `ANewSimulatorGameModeBase`
- `AFreeFlyPawn` with WASD, mouse look, vertical movement, sprint, and cursor controls
- `AProceduralCityActor` with seeded procedural ground, roads, sidewalks, and varied building massing
- automatic Version 0.1 runtime bootstrap of city, basic sun, skylight, and inspection pawn
- DirectX 12, Lumen GI/reflections, Nanite project support, Virtual Shadow Maps, mesh distance fields, and TSR baseline settings
- PCG plugin enabled for subsequent world-generation work
- architecture, roadmap, setup, graphics, world-generation, limitation, and attribution documentation rewritten for Unreal

## Toolchain

Visual Studio 2026 Community 18.11.0 is confirmed locally. Unreal Engine 5.8 is selected because Epic lists VS 2026 as supported and recommended for general UE 5.8 Windows development.

## Static validation performed

The repository was checked for Unity leftovers in the replacement tree, module naming consistency, Unreal reflection macros, generated-header ordering, Build.cs dependencies, target definitions, input mapping names, and deterministic random-stream use.

The Unreal Editor and Unreal Build Tool cannot be executed through the GitHub connector. Local compilation is therefore the next required validation gate.

## Next step

1. Pull the latest `main` branch.
2. Install the latest Unreal Engine 5.8 hotfix from Epic Games Launcher.
3. Ensure Visual Studio 2026 has Game development with C++ and Unreal tooling installed.
4. Double-click `NewSimulator.uproject` and allow Unreal to rebuild the C++ modules.
5. If requested, generate Visual Studio project files from the `.uproject`.
6. Create or open an empty level and press Play.
7. Verify that the city, sun/skylight, and free-flight pawn spawn automatically.
8. Report any compile or runtime errors.

After local validation passes, continue directly into Version 0.2 roads, curbs, intersections, lanes, parking, and PCG integration.

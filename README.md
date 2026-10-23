# New Simulator

A long-term Unreal Engine C++ project for a photorealistic, explorable, procedurally generated world.

The project restarted from its earlier Unity prototype on October 22, 2026. Unreal Engine 5.8 is now the engine baseline because Epic officially supports Visual Studio 2026 for general UE 5.8 development and because Unreal's large-world and high-fidelity toolset aligns well with the project goal.

## Technology direction

- Unreal Engine 5.8
- C++ as the primary programming language
- Visual Studio 2026 Community 18.11.0
- Lumen global illumination and reflections
- Nanite-ready asset architecture
- Virtual Shadow Maps
- PCG for procedural worldbuilding
- World Partition for future large-world streaming
- Substrate for advanced physically based materials where appropriate

## Current milestone

**Version 0.1 Unreal restart**

The repository contains a compile-oriented C++ foundation, free-flight inspection pawn, deterministic procedural city massing actor, baseline rendering configuration, Unreal-specific Git hygiene, and project documentation.

See `docs/current-status.md` for the exact next step.

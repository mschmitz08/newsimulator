# Architecture

## Principles

New Simulator is organized as a long-lived Unity application rather than a single-scene prototype. Systems are separated by responsibility and communicate through small public APIs and configuration objects.

## Planned namespaces

- `NewSimulator.Core` for application lifecycle and shared services
- `NewSimulator.Player` for first-person and developer camera movement
- `NewSimulator.World` for procedural city generation, roads, buildings, terrain, lots, and props
- `NewSimulator.Rendering` for lighting, reflections, atmosphere, exposure, and HDRP-specific setup
- `NewSimulator.Simulation` for time, weather, traffic, pedestrians, and vehicles
- `NewSimulator.Persistence` for configuration and save data
- `NewSimulator.Multiplayer` for future network abstractions
- `NewSimulator.Editor` for repeatable Unity Editor setup and validation

## World organization

The long-term world will be divided into streamable chunks. Version 0.1 intentionally generates only a small demonstration district, but generation APIs use explicit settings and deterministic seeds so the same concepts can scale later.

## Rendering boundary

Runtime gameplay code should avoid unnecessary direct dependencies on HDRP-only APIs. HDRP setup and validation belongs in the rendering and editor layers. This keeps world logic testable while preserving HDRP as the intended renderer.

## Asset strategy

Source code and lightweight Unity YAML assets remain in Git. Large binary source assets should use Git LFS. Third-party commercial content must not be committed unless redistribution rights permit it.

## Future multiplayer

Simulation state should eventually be separated from presentation so authoritative state can be synchronized without rewriting world generation, traffic, or player systems.

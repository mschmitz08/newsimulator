# Architecture

## Principles

New Simulator is a long-lived Unreal Engine application, not a disposable demo. C++ owns core systems and stable runtime behavior. Blueprints may expose configuration and presentation without becoming the only implementation of critical systems.

## Planned modules and domains

- Core: lifecycle, shared services, configuration
- Player: first-person and developer movement
- World: roads, lots, blocks, buildings, terrain, props, PCG integration
- Rendering: lighting, atmosphere, reflections, material policy, quality tiers
- Simulation: time, weather, traffic, pedestrians, vehicles
- Persistence: configuration and save data
- Multiplayer: future authoritative state and replication boundaries
- Editor tooling: repeatable generation, validation, import, and setup helpers

## Large-world direction

World Partition will become the spatial streaming backbone. Generation must be deterministic and chunk-aware so neighboring cells agree on continuous features such as roads and utilities.

## C++ and Blueprint boundary

C++ defines reusable systems and data contracts. Blueprints are appropriate for asset references, tuning, UI, visualization, and authored exceptions. Avoid burying foundational simulation logic in opaque Blueprint graphs.

## Assets

Large Unreal binary assets use Git LFS. Commercial Marketplace or Fab assets are not committed unless redistribution rights explicitly allow it.

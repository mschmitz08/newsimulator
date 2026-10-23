# World Generation

## Version 0.1

The initial generator creates a deterministic grid-based demonstration district from a `ProceduralCitySettings` asset. It generates ground, orthogonal roads, raised block surfaces, and varied building massing. Building height, footprint width, footprint depth, and material selection vary using a seeded random sequence.

This geometry is intentionally a foundation rather than the final city representation.

## Design direction

Later versions should separate the world pipeline into stages:

1. Road graph generation or import
2. Intersection classification
3. Block polygon derivation
4. Lot subdivision
5. Sidewalk and curb generation
6. Building footprint generation
7. Building grammar and facade generation
8. Parking and service-area generation
9. Street furniture and vegetation placement
10. LOD generation and chunk assignment

## Determinism

A world seed is stored in configuration. Given the same generator version, inputs, and seed, generated layouts should be reproducible. This will support debugging, streaming, save data, and future multiplayer.

## Scalability

Future world chunks should own generation outputs rather than placing an entire city under one monolithic object. Neighboring chunks must share deterministic boundary data for roads and other continuous infrastructure.

## Asset replacement

Procedural massing should expose material and prefab catalogs so higher-quality authored or photogrammetry assets can replace generated pieces without rewriting the road and lot logic.

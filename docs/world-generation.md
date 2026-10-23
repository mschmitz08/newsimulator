# World Generation

## Version 0.1

`AProceduralCityActor` generates a deterministic orthogonal demonstration district at runtime using engine cube geometry. It creates ground, roads, sidewalks, and varied building massing with a seeded `FRandomStream`.

The primitive geometry is intentionally temporary. The generation architecture is the reusable part.

## Long-term pipeline

1. Road graph generation or geographic import
2. Intersection classification
3. Block polygon derivation
4. Lot subdivision
5. Sidewalk, curb, median, and lane topology
6. Building footprint generation
7. Building grammar and facade generation
8. Parking and service areas
9. PCG-driven props, vegetation, utilities, and detail
10. World Partition cell assignment and HLOD preparation

## Determinism

Generation should remain reproducible from a world seed plus generator version. This supports debugging, streaming, save data, and future multiplayer.

## PCG

Epic's PCG framework will be used where its graph model improves iteration and large-scale placement. Core city topology should remain represented by stable C++ data structures so it can be tested, saved, imported, and replicated independently of visual graphs.

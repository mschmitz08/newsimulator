# Known Limitations

## Version 0.1 foundation

- The exact Unity Editor, HDRP package, .NET profile, and C# language version are not pinned because the local Visual Studio version has not yet been confirmed.
- The generated city uses primitive geometry for massing rather than production buildings.
- Road generation is currently an orthogonal grid and does not yet create lane topology, curbs, intersections, traffic signals, parking, or road markings.
- Buildings do not yet generate windows, facade modules, interiors, roofs, doors, nighttime illumination, or true glass.
- The Global Volume object is created but its production HDRP profile is intentionally deferred until the compatible HDRP version is selected.
- No weather, time-of-day cycle, vehicles, pedestrians, streaming, LOD generation, save data, or multiplayer implementation exists yet.
- The camera currently uses Unity's legacy Input API to avoid requiring an input package before the toolchain is pinned.
- The code has been statically reviewed, but Unity Editor compilation and Play Mode behavior still require local validation.

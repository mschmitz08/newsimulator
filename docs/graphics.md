# Graphics Direction

Photorealism is a foundational requirement. The intended renderer is Unity HDRP.

## Baseline goals

- Physically based materials using plausible metallic, smoothness/roughness, normal, ambient-occlusion, and detail values
- Physically plausible sunlight and exposure
- HDRP sky and atmospheric systems
- High quality anti-aliasing
- Screen-space reflections and reflection probes
- Ray-traced reflections and other ray-traced effects where hardware and target performance allow
- Global illumination where practical
- Ambient occlusion
- Volumetric fog
- Realistic glass and polished surfaces
- Wet-surface response after rain
- restrained post-processing rather than exaggerated cinematic grading

## Version 0.1 boundary

The first code milestone provides lighting and scene structure but deliberately does not hard-code a particular HDRP package API before the compatible Unity/HDRP version is selected. Once the Visual Studio version is confirmed, the project manifest, HDRP assets, default Volume Profile, exposure, sky, fog, reflection, and anti-aliasing settings will be pinned and generated.

## Performance philosophy

Visual quality should scale through quality tiers. Expensive features such as ray tracing must have rasterized fallbacks. Distant geometry should transition through LOD and eventually streaming rather than relying on a single enormous scene.

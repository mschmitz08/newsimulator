# Graphics Direction

Photorealism is a foundational requirement.

## Unreal rendering baseline

- Lumen for dynamic global illumination and reflections
- Virtual Shadow Maps for high-detail dynamic shadows
- Nanite-ready geometry and asset policy
- Temporal Super Resolution as the initial anti-aliasing/upscaling baseline
- DirectX 12 on Windows
- physically plausible lighting values
- realistic sky, atmosphere, clouds, fog, exposure, and tone mapping
- Substrate for advanced layered physically based materials where it materially improves realism
- high-quality glass, wet surfaces, vehicle reflections, polished materials, and nighttime emissive detail

## Scalability

High-end rendering features need quality tiers. Hardware ray tracing may be added where it provides a measurable visual benefit, but the project must maintain viable non-ray-traced fallbacks.

## Version 0.1 boundary

Version 0.1 establishes engine rendering defaults and procedural massing. It does not yet claim final photorealistic materials or lighting. Those require authored materials, calibrated environment lighting, higher-quality geometry, and local GPU validation.

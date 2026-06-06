# learning-graphics-cpp

A software ray tracer built from scratch in C++ over ~2 weeks.
No graphics libraries — only the C++ standard library and math.

## What I built

- **Week 1** — Vec3 math library (dot, cross, normalize, length)
- **Week 2** — Tiny ray tracer: camera, rays, ray-sphere intersection, PPM output
- **Week 3** — Lighting: surface normals, diffuse shading, shadows, multiple spheres
- **Week 4** — Anti-aliasing, materials (albedo + reflectivity), reflections, multiple bounces
- **Phase 0 (consolidation)** — Tech debt, architecture cleanup, Mat4, matrix-driven camera

## Result

A ray tracer that renders scenes with:
- Colored materials
- Diffuse and specular lighting
- Hard shadows (with correct light distance occlusion check)
- Multi-bounce reflections
- Anti-aliasing (16 samples/pixel)
- Camera positioned via `lookAt` view matrix

## Architecture

```
Vec3.h       — 3D vector math
Mat4.h       — 4x4 matrix: identity, translate, scale, operator*, lookAt, perspective
Ray.h        — ray origin + direction
Sphere.h     — sphere hit detection (handles ray inside sphere, tMin threshold)
Camera.h     — matrix-driven camera (eye, target, up, fov, aspect, near, far)
Material.h   — albedo + reflectivity
RayTracer.h  — traceRay(), isInShadow()
Renderer.h   — render loop (anti-aliasing, multi-bounce, shading)
Scene.h      — scene configuration struct
```

## Tests

35 unit tests covering Vec3, Mat4, Sphere, Camera, RayTracer:
```bash
./raytracer_tests
```

## Build

```bash
mkdir build && cd build
cmake ..
make
./raytracer          # renders output/image.ppm
./raytracer_tests    # runs unit tests
```

## Tech
- C++17
- CMake
- doctest for unit tests
- GitHub Actions CI

## Background
This is my first project in learning graphics programming
as a side project. This repo is a learning journal —
each phase adds a new concept on top of the previous.
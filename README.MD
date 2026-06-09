# learning-graphics-cpp

A software ray tracer and CPU rasterizer built from scratch in C++.
No graphics libraries — only the C++ standard library and math.

## What I built

- **Week 1** — Vec3 math library (dot, cross, normalize, length)
- **Week 2** — Tiny ray tracer: camera, rays, ray-sphere intersection, PPM output
- **Week 3** — Lighting: surface normals, diffuse shading, shadows, multiple spheres
- **Week 4** — Anti-aliasing, materials (albedo + reflectivity), reflections, multiple bounces
- **Phase 0 (consolidation)** — Tech debt, architecture cleanup, Mat4, matrix-driven camera
- **Phase 1 (rasterizer)** — CPU software rasterizer: triangle rasterization, MVP pipeline, Phong shading

## Ray Tracer Result

A ray tracer that renders scenes with:
- Colored materials
- Diffuse and specular lighting
- Hard shadows (with correct light distance occlusion check)
- Multi-bounce reflections
- Anti-aliasing (16 samples/pixel)
- Camera positioned via `lookAt` view matrix

## Rasterizer Result

A CPU rasterizer that renders a 3D cube with:
- Full MVP transform pipeline (model, view, projection)
- Perspective divide + viewport transform
- Triangle rasterization via bounding box + barycentric coordinates
- Z-buffer depth testing
- Blinn-Phong shading (ambient + diffuse + specular)
- CCW winding order for correct face normals

```
Implemented:
- CPU triangle rasterization
- Barycentric coordinate interpolation
- Depth buffer
- MVP transform pipeline
- Blinn-Phong lighting
- Rotation matrices (X, Y, Z axes)
```

## Architecture

```
Vec3.h         — 3D vector math
Vec4.h         — 4D homogeneous coordinates
Mat4.h         — 4x4 matrix: identity, translate, scale, rotate(X/Y/Z), lookAt, perspective
Ray.h          — ray origin + direction
Sphere.h       — sphere hit detection (handles ray inside sphere, tMin threshold)
Camera.h       — matrix-driven camera (eye, target, up, fov, aspect, near, far)
Material.h     — albedo + reflectivity
RayTracer.h    — traceRay(), isInShadow()
Renderer.h     — render loop (anti-aliasing, multi-bounce, shading)
Scene.h        — scene configuration struct
Framebuffer.h  — pixel buffer + depth buffer with depth testing
Triangle.h     — triangle with auto-computed face normal
Cube.h         — 8 vertices, 12 triangles with correct CCW winding per face
Rasterizer.h   — CPU rasterization pipeline (MVP → NDC → screen → barycentric → shade)
```

## Tests

Unit tests covering Vec3, Vec4, Mat4, Sphere, Camera, RayTracer, Framebuffer, Triangle, Cube:
```bash
./raytracer_tests
```

## Build

```bash
mkdir build && cd build
cmake ..
make
./raytracer            # renders output/image.ppm       (ray tracer)
./raytracer_tests      # runs unit tests
```

Output PPM files are in `output/` — open with any image viewer that supports PPM.

## Tech
- C++17
- CMake
- doctest for unit tests
- GitHub Actions CI

## Background
This is my first project in learning graphics programming
as a side project. This repo is a learning journal —
each phase adds a new concept on top of the previous.

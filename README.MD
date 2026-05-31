# learning-graphics-cpp

A software ray tracer built from scratch in C++ over ~2 weeks.
No graphics libraries — only the C++ standard library and math.

## What I built

- **Week 1** — Vec3 math library (dot, cross, normalize, length)
- **Week 2** — Tiny ray tracer: camera, rays, ray-sphere intersection, PPM output
- **Week 3** — Lighting: surface normals, diffuse shading, shadows, multiple spheres
- **Week 4** — Anti-aliasing, materials (albedo + reflectivity), reflections, multiple bounces

## Result

A ray tracer that renders scenes with:
- Colored materials
- Diffuse and specular lighting
- Hard shadows
- Multi-bounce reflections
- Anti-aliasing (16 samples/pixel)

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
This is my first tutorial in learning graphics programming domain
as a side project. This repo is a learning journal —
each week adds a new concept on top of the previous.
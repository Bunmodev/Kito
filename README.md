# Kito 🛠️

A lightweight, opinionated, declarative and data-driven 2D UI engine built with **C++20**, **SDL3**, and **yaml-cpp** for making cross-platform desktop applications with **C++**.

Kito focuses on a "Logic-Rendering Split" architecture, allowing you to define complex user interfaces entirely through YAML configuration files while maintaining high-performance batch rendering.

## 🚀 Features
* **Declarative UI**: Define your interface structure in `config.yaml`, no C++ recompilation needed for layout changes.
* **Batch Renderer**: Optimized `DrawCommand` system that sorts and flushes geometry to minimize GPU state changes.
* **Recursive Hit-Testing**: Robust parent-child event propagation for complex nested layouts.
* **Retro Aesthetic**: Default styling inspired by the "golden era" of chunky, tactile desktop interfaces (Win7/Win95) as the default styling.
* **Normalized Coordinates**: Support for relative positioning (0.0 - 1.0) for responsive window scaling.

## 🏗️ Architecture
Kito operates on a decoupled, three-stage lifecycle:

* **The Declaration** (Source of Truth): UI state is defined in .yaml and parsed into baseBounds. This represents the intent of the layout.

* **The Layout Pass (Msanifu):** The layout engine performs a non-destructive pass, calculating final screen coordinates (margins, padding, and alignment) without mutating the original intent using our custom layout engine "msanifu".

* **The Execution (Batch Renderer):** The renderer consumes the "baked" layout. Geometry is sorted by Z-index and state, then flushed in optimized batches to minimize GPU draw calls.



# Kito Roadmap

This document outlines the planned development stages for **Kito**, a lightweight C++ UI and rendering framework.

The roadmap is flexible and may evolve as the project grows.

---

# Vision

Kito aims to provide a modular, extensible UI system for applications, tools, and editors.
The framework focuses on simplicity, performance, and developer control.

Core principles:

* Lightweight and minimal
* Clear architecture
* Modern C++ practices
* Easily extensible widgets and layouts
* Cross-platform support

---

# Phase 1 – Core Foundation

Establish the base architecture required for the framework.

### Window and Platform Layer

* SDL window abstraction
* Event polling and dispatch system
* Application loop

### Rendering System

* Renderer abstraction
* Render command queue
* Draw order management
* Basic primitives (rectangles, colors)

### Core Structures

* Rect / geometry utilities
* Widget base class
* UI tree structure

---

# Phase 2 – Basic UI System

Introduce the essential building blocks for user interfaces.

### Widgets

* Button
* Panel / container
* Label / text element

### Event System

* Mouse events
* Hover detection
* Click handling
* Focus handling

### Layout

* Basic layout engine
* Margin and padding support
* Simple stacking layouts

---

# Phase 3 – Advanced Layout System

Improve layout behavior and flexibility.

### Layout Managers

* Vertical layout
* Horizontal layout
* Grid layout

### Layout Features

* Alignment options
* Dynamic resizing
* Constraint-based positioning

---

# Phase 4 – Rendering Improvements

Enhance rendering performance and capabilities.

### Rendering

* Batching improvements
* Clipping support
* Z-index and layering

### Graphics

* Font rendering
* Texture support
* Image widgets

---

# Phase 5 – Styling System

Allow UI appearance to be customized.

### Style Features

* Theme system
* Style properties (colors, borders, spacing)
* Reusable style classes

### Goals

* Decouple style from logic
* Allow theme switching

---

# Phase 6 – Input and Interaction

Improve interaction and usability.

### Input Features

* Keyboard input
* Focus navigation
* Drag and drop
* Scroll containers

---

# Phase 7 – Developer Experience

Make the framework easier to use and integrate.

### Tooling

* Example applications
* Widget showcase
* Documentation

### Build System

* Improved CMake configuration
* Optional modules

---

# Future Ideas

These are exploratory ideas that may or may not be implemented.

* GPU accelerated rendering
* Animation system
* UI editor / visual builder
* Reactive UI state system
* Plugin system for widgets

---

# Long-Term Goal

Kito should be capable of powering:

* Game editors
* Developer tools
* Desktop applications
* Custom GUI systems

The long-term objective is to provide a clean alternative to heavyweight GUI frameworks while keeping full control in the hands of developers.

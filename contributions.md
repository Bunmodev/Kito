# Contributing to Kito

First off, thank you for taking the time to contribute to **Kito**.

Kito is an experimental UI and rendering framework written in C++. The goal of the project is to provide a lightweight, extensible system for building user interfaces and tooling.

This document outlines the guidelines for contributing to the project.

---

## Code of Conduct

Be respectful and constructive when interacting with others in the project.
Harassment, discrimination, or toxic behavior will not be tolerated.

---

## How to Contribute

There are several ways you can contribute:

* Fixing bugs
* Improving documentation
* Adding tests
* Suggesting new features
* Improving performance
* Refactoring code

If you're unsure whether something should be contributed, open an issue first to discuss it.

---

## Reporting Bugs

When reporting a bug, please include:

* A clear description of the issue
* Steps to reproduce the bug
* Expected behavior
* Actual behavior
* OS and compiler information
* Relevant logs or screenshots

This helps maintainers reproduce and fix the problem faster.

---

## Suggesting Features

Feature suggestions are welcome.

Before opening a feature request:

1. Check if the feature already exists or has been requested.
2. Explain the problem your feature solves.
3. Provide a clear explanation of the proposed solution.

Large features should be discussed before implementation.

---

## Development Setup

1. Clone the repository

```
git clone https://github.com/<username>/kito.git
cd kito
```

2. Configure the project using CMake

```
cmake -B build
```

3. Build the project

```
cmake --build build
```

Make sure the project builds successfully before making changes.

---

## Branching

Use descriptive branch names.

Examples:

```
feature/widget-layout-system
fix/button-hover-state
refactor/render-command-queue
```

Avoid committing directly to the main branch.

---

## Coding Style

General guidelines:

* Use modern C++ practices
* Prefer clarity over cleverness
* Keep functions small and focused
* Use meaningful variable and function names
* Avoid unnecessary dependencies

Formatting:

* 4 spaces for indentation
* Consistent brace style
* Header files should be minimal and clean

---

## Pull Requests

When submitting a pull request:

1. Ensure the project builds successfully.
2. Keep pull requests focused on a single change.
3. Provide a clear description of what the PR does.
4. Reference any related issues.

Pull requests may be reviewed before merging.

---

## Documentation

If your change affects public APIs or functionality, please update the documentation accordingly.

Good documentation helps others understand and use the project.

---

## Areas Where Contributions Are Welcome

Current areas of interest include:

* UI widget improvements
* Layout systems
* Rendering optimizations
* Event handling
* Cross-platform improvements
* Examples and documentation

---

## Questions

If you have questions about contributing, feel free to open a discussion or issue.

Thanks for helping improve Kito.

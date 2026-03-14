# Installation

Kito is currently under active development and **no prebuilt binaries are available yet**.

There are currently two ways to use Kito:

1. **Build from source** (recommended for now)
2. **Link against prebuilt binaries** (coming soon)

---

# 🛠️ Build Requirements

Before building Kito, ensure you have the following installed:

**Compiler**

* GCC 15.2.0+ (MinGW-w64)

**Build System**

* CMake 3.20+
* Ninja

**Dependencies**

* SDL3
* yaml-cpp
* mini-audio
* stb_image

---

# Option 1 — Build From Source

### 1. Clone the Repository

```
git clone --recurse-submodules https://github.com/Bunmodev/kito.git
cd kito
```

### 2. Configure the Build

```
cmake -B build -G Ninja
```

### 3. Build the Project

```
cmake --build build
```

After building, the compiled binaries will appear inside the `build` directory.

---

# Option 2 — Link Against Prebuilt Binaries (Coming Soon)

Prebuilt binaries will be provided in future releases.

Once available, developers will be able to:

* Download compiled Kito binaries
* Link the library into their projects
* Include the Kito headers

This will make integration faster and remove the need to build the engine manually.

---

# Notes

Since the project is still evolving:

* APIs may change
* Build steps may be updated
* Some components may still be experimental

Developers using Kito at this stage should expect breaking changes.

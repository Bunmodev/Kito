# No includes needed! The parent (Root) already loaded them.

# 1. Build the App
kito_build_project(calculator EXECUTABLE SOURCES main.cpp)

# 2. Register ViewModels
kito_register_vms("${CMAKE_CURRENT_SOURCE_DIR}/src/viewModels" calculator)

# 3. Copy Assets
kito_configure_assets(calculator)
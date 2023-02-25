#Compiler command line
# $ cmake -DCMAKE_C_COMPILER="C:/MinGW/bin/gcc.exe" -DCMAKE_CXX_COMPILER="C:/MinGW/bin/g++.exe" -G "MinGW Makefiles" ..

cmake_minimum_required(VERSION 3.10)
project(Sim)

set(CMAKE_CXX_STANDARD 11)

# SDL2 directories
include_directories(${SDL2_INCLUDE_DIRS} )


# Set files names
set(SOURCE_FILES src/main.cpp src/Simulation.cpp src/Fly3D.cpp src/Arena3D.cpp src/Wall.cpp src/Entrance.cpp src/Food.cpp src/Cuboid.cpp src/Egg.cpp src/FliesConfig.cpp src/Utility.cpp)
set(DRAW_FILES src/DrawArena.cpp src/Simulation.cpp src/Fly3D.cpp src/Arena3D.cpp src/Wall.cpp  src/Entrance.cpp src/Food.cpp src/Utility_SDL.cpp src/Cuboid.cpp src/Egg.cpp src/FliesConfig.cpp src/Utility.cpp)
set(FLIES_GENERATOR_FILES src/FliesConfigGenerator.cpp src/Fly3D.cpp src/Arena3D.cpp src/Wall.cpp src/Entrance.cpp src/Food.cpp src/Cuboid.cpp src/Egg.cpp src/FliesConfig.cpp src/Utility.cpp )

# SDL2 search command, REQUIRES SLD2 to be installed
find_package(SDL2 REQUIRED)

# Create SimData directory for data storage
file(MAKE_DIRECTORY build/SimData)
file(MAKE_DIRECTORY build/SimConfig)
file(MAKE_DIRECTORY build/FliesConfig)
file(MAKE_DIRECTORY build/SimSummary)

# Create executables
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_executable(DrawArena ${DRAW_FILES})
add_executable(FliesConfigGenerate ${FLIES_GENERATOR_FILES})

# Link SDL2 directory to project
target_include_directories(DrawArena PUBLIC ${SDL2_INCLUDE_DIRS})

# Link SDL2 library to project
target_link_libraries(DrawArena ${SDL2_LIBRARIES})


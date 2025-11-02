cmake_minimum_required(VERSION 3.16)
project(chronos_host C)

# Build the platform lib from platform/host
add_subdirectory(platform/host)

# Your app
add_executable(chronos_host
    test/main.c
    src/sch.c
)

# Threads (if you need them)
find_package(Threads REQUIRED)
target_link_libraries(chronos_host PRIVATE platform_host Threads::Threads)

# Add include dirs if your app needs headers from platform/host
target_include_directories(chronos_host PRIVATE ${CMAKE_SOURCE_DIR}/platform/host)

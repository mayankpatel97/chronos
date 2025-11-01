cmake_minimum_required(VERSION 3.28)

project(chronos_host LANGUAGES C)

find_package(Threads REQUIRED)

add_executable(chronos_host
    src/chronos.c
    src/main.c
)

add_subdirectory(platform/host)

target_link_libraries(chronos_host
    PRIVATE
        platform_host        # Replace with actual library name from platform/host
        Threads::Threads
)

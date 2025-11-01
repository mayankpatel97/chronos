
target_sources(chronos_host PRIVATE
    pal.c
    console.c
)

target_include_directories(chronos_host PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(chronos_host PRIVATE
    HOST_BUILD
)
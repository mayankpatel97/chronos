# Create the library that your app will link to
add_library(platform_host STATIC
    console.c
    pal.c
)

# Public includes for anything that uses this lib
target_include_directories(platform_host PUBLIC ${CMAKE_CURRENT_LIST_DIR})

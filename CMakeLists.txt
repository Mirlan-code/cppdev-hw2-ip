cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{RUN_NUMBER})
    set(PATCH_VERSION $ENV{RUN_NUMBER} CACHE INTERNAL "Patch version")
else()
    set(PATCH_VERSION 1)
endif()

configure_file(version.h.in version.h)

set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip VERSION ${PROJECT_VESRION})

add_library(ip_filter ip_filter.h ip_filter.cpp)
add_executable(ip main.cpp)

target_include_directories(ip
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip PRIVATE
    ip_filter
)

if (MSVC)
    target_compile_options(ip PRIVATE
        /W4
    )
else ()
    target_compile_options(ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

set_target_properties(ip PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)

install(TARGETS ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

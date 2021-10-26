cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{RUN_NUMBER})
    set(PATCH_VERSION $ENV{RUN_NUMBER} CACHE INTERNAL "Patch version")
else()
    set(PATCH_VERSION 1)
endif()

configure_file(version.h.in version.h)

set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip VERSION ${PROJECT_VESRION})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_library(ip_filter ip_filter.h ip_filter.cpp)
add_executable(ip main.cpp)
add_executable(tests tests.cpp)

target_include_directories(ip
    PRIVATE "${CMAKE_BINARY_DIR}"
)
target_link_libraries(ip
    PRIVATE ip_filter
)

set_target_properties(tests PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(tests
    ${Boost_LIBRARIES}
    ip_filter
)

if (MSVC)
    target_compile_options(ip PRIVATE
        /W4
    )
    target_compile_options(tests PRIVATE
        /W4
    )
else ()
    target_compile_options(ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(tests PRIVATE
        -Werror -Wall -pedantic-errors
    )
endif()

set_target_properties(ip tests ip_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)

install(TARGETS ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)


enable_testing()
add_test(tests tests)
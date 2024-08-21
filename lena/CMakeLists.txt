cmake_minimum_required(VERSION 3.10)
project(LenaCompiler)

# add specific "-municode" flag
if(WIN32)
    add_compile_options(-municode)
    add_link_options(-municode)
endif()

# define build time in Macros
execute_process(
    COMMAND ${CMAKE_COMMAND} -E echo_append
    COMMAND date "+%Y-%m-%d %H:%M:%S"
    OUTPUT_VARIABLE BUILD_TIME
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_definitions("-DLENA_BUILD_OS_STR=\"${CMAKE_SYSTEM_NAME}\"")
add_definitions("-DLENA_BUILD_ARCH_STR=\"${CMAKE_SYSTEM_PROCESSOR}\"")
add_definitions("-DLENA_BUILD_TIME_STR=\"${BUILD_TIME}\"")

# add Llibs as submodule
add_subdirectory(external/llibs)

# Build Lena Compiler
include_directories(include)
file(GLOB_RECURSE LENA_SRC_FILES "src/*.c")
add_executable(lena ${LENA_SRC_FILES})

target_link_libraries(lena PRIVATE llibs)

target_include_directories(lena PRIVATE
    ${CMAKE_SOURCE_DIR}/external/llibs/cross/include
    ${CMAKE_SOURCE_DIR}/external/llibs/lingua/include
)

add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/main.s
    COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} -S -I${CMAKE_SOURCE_DIR}/external/llibs/include -I${CMAKE_SOURCE_DIR}/external/llibs/cross/include -I${CMAKE_SOURCE_DIR}/external/llibs/lingua/include ${CMAKE_SOURCE_DIR}/src/main.c -o ${CMAKE_SOURCE_DIR}/asm/lena.s
    DEPENDS ${CMAKE_SOURCE_DIR}/src/main.c
    COMMENT "Generating assembly for main.c"
)

add_custom_target(Generate_assembly DEPENDS ${CMAKE_BINARY_DIR}/main.s)
cmake_minimum_required(VERSION 3.20)

project(embedded_proto_framing)

add_library(${PROJECT_NAME} STATIC)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

file(GLOB src_files
    "src/*.cpp"
)

target_sources(${PROJECT_NAME}
    PUBLIC
    ${src_files}
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

if(MSVC)
    message(STATUS "Compiling with MSVC")
    target_compile_options(${PROJECT_NAME} PUBLIC "/Zc:__cplusplus")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20 /Za")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC src)
message(STATUS "Configuring ${PROJECT_NAME}")

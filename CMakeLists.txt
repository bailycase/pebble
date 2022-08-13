cmake_minimum_required(VERSION 3.7.0)
project(pebble VERSION 0.1.0)


find_package(Vulkan REQUIRED)
# target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES})

find_package(glfw3)
# target_link_libraries(${PROJECT_NAME} glfw)

include_directories(src/)
file(GLOB_RECURSE "engine" SRC_FILES src/*.c src/*.h)

add_library(${PROJECT_NAME} STATIC ${engine})

target_link_libraries(${PROJECT_NAME} "${Vulkan_LIBRARIES}" glfw)
include_directories(${Vulkan_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})

# demo
file(GLOB_RECURSE "pb-demo" SRC "demo/*.c" "demo/*.h")
include_directories(demo/)
add_executable(pb-demo ${pb-demo})
target_link_libraries(pb-demo LINK_PRIVATE ${PROJECT_NAME})
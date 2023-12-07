cmake_minimum_required(VERSION 3.13)
project(newfltk)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES BC1.cxx)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(FLTK_SKIP_FLUID true)
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${FLTK_BASE_LIBRARY} ${FLTK_PLATFORM_DEPENDENT_LIBS})

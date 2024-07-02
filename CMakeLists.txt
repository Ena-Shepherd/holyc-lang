
cmake_minimum_required(VERSION 3.26)

project(hcc C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

file(
  GLOB SOURCES
  "src/*.c"
)

#if system is linux, create a new variable
if(APPLE)
  # for MacOS X or iOS, watchOS, tvOS (since 3.10.3)
  set(PLATFORM APPLE)
elseif(UNIX AND NOT APPLE)
  # for Linux, BSD, Solaris, Minix
  set(PLATFORM UNIX)
elseif(MSVC)
  # for Windows operating system in general
  set(PLATFORM MSVC)
elseif(MSYS OR MINGW)
  # for detecting Windows compilers
  set(PLATFORM MINGW)
endif()


set(LIB_SRC ./holyc-lib)
set(SYNTAX ./syntax-highlighting)
set(PREFIX /usr/local)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake-config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/cmake-config.h)

option(INSTALL "Install the project" ON)

if(INSTALL)
  add_custom_target(install_hcc ALL
    COMMAND cd ../src/ && make install
    COMMENT "Running make install in src directory"
  )
endif()

add_compile_options(
  -Wall
  -Werror
  -ggdb
  -DDEBUG
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(
  ${PROJECT_NAME}
  m
)

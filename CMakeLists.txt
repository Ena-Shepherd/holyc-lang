
cmake_minimum_required(VERSION 3.26)

project(hcc C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

file(
  GLOB SOURCES
  "src/*.c"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# set PLATFORM variable
if(APPLE)
  # for MacOS X or iOS, watchOS, tvOS (since 3.10.3)
  set(PLATFORM IS_MACOS)
elseif(UNIX AND NOT APPLE)
  # for Linux, BSD, Solaris, Minix
  set(PLATFORM IS_LINUX)
elseif(MSVC)
  # for Windows operating system in general
  set(PLATFORM IS_WINDOWS)
else(MSYS OR MINGW)
  # for detecting Windows compilers
  set(PLATFORM IS_MINGW)
endif()

EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
message( STATUS "Architecture: ${ARCHITECTURE}" )

set(LIB_SRC ./holyc-lib)
set(SYNTAX ./syntax-highlighting)
set(PREFIX /usr/local)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake-config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/cmake-config.h)

option(INSTALL "Install the project" ON)

if(INSTALL AND NOT PLATFORM STREQUAL IS_MINGW)
  add_custom_target(install_hcc ALL
    COMMAND cd ../src/ && make install
    COMMENT "Running make install in src directory"
  )
else()
  add_custom_target(install_hcc ALL
    COMMAND echo "Installation not supported on this platform"
    COMMENT "Installation not supported on this platform"
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

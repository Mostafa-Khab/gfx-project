cmake_minimum_required(VERSION 3.25)
project(GFX_PROJ
        VERSION 1.0
        LANGUAGES CXX C
      )

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(DEPS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps")

if(UNIX)
  find_package(glfw3 3.3 REQUIRED)
  find_package(OpenGL REQUIRED)
  message(STATUS "compiling GFX for Unix")
elseif(WIN32)
  include_directories(/usr/lib/gcc/x86_64-w64-mingw32/12-win32/include/c++_)
  include_directories(/usr/i686-w64-mingw32/include)
  include_directories(/usr/i686-w64-mingw32/local/include)
  link_directories(/usr/i686-w64-mingw32/lib)
  link_directories(/usr/i686-w64-mingw32/local/lib)

  set(CMAKE_INSTALL_PREFIX /usr/i686-w64-mingw32/local/)
  message(STATUS "compiling GFX for WIN32")
endif()

include_directories(graphics system ${DEPS_PATH})
link_directories(graphics system ${DEPS_PATH})

#compile all sources
file(GLOB SOURCES graphics/*.cpp  system/*.cpp)


add_library(glx STATIC ${SOURCES})
target_link_libraries(glx PUBLIC logger)

add_executable(main ${DEPS_PATH}/glad_gl.c main.cpp)

if(UNIX)
  target_link_libraries(main
      glx            #before every other library when compiling source;
      glfw
      OpenGL::GL
      Xrandr
      Xi
      X11
      pthread
      dl
      Xinerama
      Xcursor
  )
endif(UNIX)

if(WIN32)
  target_link_libraries(main PUBLIC
    glx
    glfw3
    opengl32
    gdi32
  )

  target_compile_options(main PUBLIC -static-libgcc -static-libstdc++ -static)
endif(WIN32)

install(
  TARGETS glx DESTINATION lib
)

install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/graphics"
  DESTINATION include/GFX
  FILES_MATCHING 
  PATTERN "*.hpp"
)

install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/system"
  DESTINATION include/GFX
  FILES_MATCHING 
  PATTERN "*.hpp"
)

install(
  FILES graphics.hpp system.hpp
  DESTINATION include/GFX
)

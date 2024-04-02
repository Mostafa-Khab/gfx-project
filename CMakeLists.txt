cmake_minimum_required(VERSION 3.25)
project(MY_MAIN_PROJ)

#set(CMAKE_CXX_STANDARD 11)
set(DEPS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/deps/)

if(UNIX)
  find_package(glfw3 3.3 REQUIRED)
  find_package(OpenGL REQUIRED)
  message(STATUS "compiling GFX for Unix")
elseif(WIN32)
# NOTE: this is cross-compiling on linux for windows.
# make sure to specify the GLFW dir in the following functions
# /usr/i686-w64-mingw32/local/ is the folder Where GFX include, lib are stored.
  set(CMAKE_INSTALL_PREFIX /usr/i686-w64-mingw32/local/)

  include_directories(/usr/i686-w64-mingw32/local/include/)
  link_directories(/usr/i686-w64-mingw32/local/lib/)

  message(STATUS "compiling GFX for WIN32")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(SOURCES
    graphics/context.cpp
    graphics/vertex.cpp
    graphics/buffer.cpp 
    graphics/shader.cpp 
    graphics/program.cpp 
    graphics/polygon.cpp
    graphics/view.cpp
    system/color.cpp
    system/vectors.cpp
    system/callbacks.cpp
    system/debug.cpp
    system/clock.cpp
    system/stb_image.cpp
  
    graphics/context.hpp
    graphics/vertex.hpp
    graphics/buffer.hpp 
    graphics/shader.hpp 
    graphics/program.hpp 
    graphics/polygon.hpp
    graphics/view.hpp
    system/color.hpp
    system/vectors.hpp
    system/callbacks.hpp
    system/debug.hpp
    system/clock.hpp
)

include_directories(graphics system ${DEPS_PATH})

add_library(gfx STATIC ${SOURCES})

add_executable(main ${DEPS_PATH}/glad_gl.c main.cpp)

if(UNIX)
  target_link_libraries(main
      gfx            #before every other library when compiling source;
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
    gfx
    glfw3
    opengl32
    gdi32
  )

  target_compile_options(main PUBLIC -static-libgcc -static-libstdc++ -static)
endif(WIN32)

install(
  TARGETS gfx DESTINATION lib
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

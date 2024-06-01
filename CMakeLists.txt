cmake_minimum_required(VERSION 3.15..3.28)
project(GFX_PROJ
        VERSION 1.0
        LANGUAGES CXX C
      )

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(DEPS_PATH deps/)

if(UNIX)
  find_package(glfw3 3.3 REQUIRED)
  find_package(OpenGL REQUIRED)
  message(STATUS "compiling GFX for Unix")
elseif(WIN32)

  set(CMAKE_INSTALL_PREFIX /usr/i686-w64-mingw32/local/)
  message(STATUS "compiling GFX for WIN32")
endif()

include_directories(graphics system ${DEPS_PATH})
link_directories(graphics system ${DEPS_PATH})

#compile all sources
file(GLOB SOURCES graphics/*.cpp  system/*.cpp)


add_library(gfx STATIC ${SOURCES})
target_link_libraries(gfx PUBLIC logger)

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
      logger
  )
endif(UNIX)

if(WIN32)
  #if on windows compile logger to a lib which is found in deps folder
  target_link_libraries(main PUBLIC
    gfx
    glfw3
    opengl32
    gdi32
    #logger
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

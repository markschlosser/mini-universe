cmake_minimum_required(VERSION 3.25)

project(mini-universe)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_executable (mini-universe-gl ../args.c ../args.h ../file.c ../file.h main.c render.c ../render.h ../simulation.c ../simulation.h ../version.h ../xymath.h)

target_link_libraries(mini-universe-gl ${OPENGL_LIBRARIES} GLUT::GLUT )

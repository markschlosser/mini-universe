cmake_minimum_required(VERSION 3.25)

project(mini-universe)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_executable (mini-universe-gl ../file.c ../file.h main_glut.c render_gl.c ../render.h ../simulation.c ../simulation.h ../version.h ../xymath.h)

target_link_libraries(mini-universe-gl ${OPENGL_LIBRARIES} GLUT::GLUT )

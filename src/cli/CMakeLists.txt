cmake_minimum_required(VERSION 3.25)

project(mini-universe)

add_executable (mini-universe-cli ../file.c ../file.h main.c render.c ../render.h ../simulation.c ../simulation.h ../version.h ../xymath.h)

cmake_minimum_required(VERSION 3.25)

project(mini-universe)

add_executable (mini-universe-cli ../args.c ../args.h ../file.c ../file.h main.c render.c screen.c screen.h ../render.h ../simulation.c ../simulation.h ../version.h ../xymath.h)

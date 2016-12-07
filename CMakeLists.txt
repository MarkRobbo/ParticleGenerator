cmake_minimum_required(VERSION 3.6)

# Project Setup
project(ParticleGenerator)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp Particle.cpp Particle.h ParticleManager.cpp ParticleManager.h Physics/Physics.h Physics/LorenzAttractor.cpp Physics/LorenzAttractor.h Physics/Newtonian.cpp Physics/Newtonian.h Emitters/Emitter.cpp Emitters/Emitter.h Emitters/FountainEmitter.cpp Emitters/FountainEmitter.h)
add_executable(ParticleGenerator ${SOURCE_FILES})

# OpenGL/GLUT include
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(ParticleGenerator ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
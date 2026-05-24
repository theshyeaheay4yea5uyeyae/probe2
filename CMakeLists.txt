cmake_minimum_required(VERSION 3.5)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK or pass -DCMAKE_TOOLCHAIN_FILE")
  endif()
endif()

project(probe2 C)

include("$ENV{VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "probe2")
set(VITA_TITLEID  "PROBE2000")
set(VITA_VERSION  "01.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2 -std=gnu99")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-z,nocopyreloc -nostdlib")

add_executable(probe2
  src/probe2.c
)

target_link_libraries(probe2
  SceLibKernel_stub
  k
  gcc
)

vita_create_self(probe2.suprx probe2 CONFIG probe2.yml)

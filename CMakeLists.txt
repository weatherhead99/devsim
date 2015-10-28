PROJECT (DEVSIM C CXX)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#policy settings
cmake_policy(SET CMP0005 OLD)

find_library(superlu superlu)
find_library(cgns cgns)
find_library(sqlite3 sqlite3)

find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
find_package(TCL)
find_package(PythonLibs)
find_package(ZLIB)

find_package(HDF5 REQUIRED)

find_program(FLEX flex)
find_program(BISON bison)

#symdiff include
find_library(symdiff symdiff)
include_directories("/usr/local/include/symdiff/")

message(WARNING "symdiff: ${symdiff}")


include_directories(${PYTHON_INCLUDE_DIR})

#set -fPIC by default because we're using a lot of OBJECT libs
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

include(cmake/generate.cmake)



ADD_DEFINITIONS(-DDEVSIM_VERSION_STRING="\\"Beta 0.01\\"")
ADD_DEFINITIONS(-DDEVSIM_COPYRIGHT_YEAR="\\"2009-2015\\"")

SET (SUBDIRS
    src
    testing
)

SITE_NAME(HOSTNAME)
MESSAGE("Hostname: ${HOSTNAME}")

ENABLE_TESTING()
FOREACH (SUB ${SUBDIRS})
    ADD_SUBDIRECTORY(${SUB})
ENDFOREACH (SUB ${SUBDIRS})

install(FILES include/EngineAPI.hh import.hh parseexr.hh
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/symdiff)

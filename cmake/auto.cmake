find_library(superlu superlu)
find_library(cgns cgns)



find_package(TCL)
find_package(PythonLibs)
find_package(ZLIB)

find_program(FLEX flex)
find_program(BISON bison)

#symdiff include
set(SYMDIFF_DIR "${CMAKE_SOURCE_DIR}/../symdiff")
include_directories(${SYMDIFF_DIR}/include)

include_directories(${PYTHON_INCLUDE_DIR})

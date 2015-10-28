SET (SUBDIRS
    Geometry
    models
    math
    adiff
    AutoEquation
    Equation
    GeomModels
    meshing
    Data
    Circuit
    MathEval
    tclapi
    errorSystem
    myThread
    utility
    commands
    pythonapi
    main
)

include_directories(common_api)
include_directories(${CMAKE_SOURCE_DIR}/src/Circuit/data)



foreach(sub ${SUBDIRS})
  include_directories(${sub})

endforeach()


FOREACH (SUB ${SUBDIRS})
    ADD_SUBDIRECTORY(${SUB})

ENDFOREACH (SUB ${SUBDIRS})



add_library(devsim SHARED $<TARGET_OBJECTS:Geometry> $<TARGET_OBJECTS:models> 
  $<TARGET_OBJECTS:math> $<TARGET_OBJECTS:MathEval> $<TARGET_OBJECTS:AutoEquation>
$<TARGET_OBJECTS:Equation> $<TARGET_OBJECTS:GeomModels> $<TARGET_OBJECTS:meshing>
$<TARGET_OBJECTS:Data> $<TARGET_OBJECTS:circuitData> $<TARGET_OBJECTS:circuitIdeal> $<TARGET_OBJECTS:circuitSources> $<TARGET_OBJECTS:errorSystem> $<TARGET_OBJECTS:myThread> $<TARGET_OBJECTS:commands> $<TARGET_OBJECTS:utility>)

message(WARNING "superlu: ${superlu}")
message(WARNING "BLAS: ${BLAS_LIBRARIES}")
message(WARNING "LAPACK: ${LAPACK_LIBRARIES}")
message(WARNING "BLAS_FOUND :${BLAS_FOUND}")

target_link_libraries(devsim ${superlu} ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})


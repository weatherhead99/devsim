INCLUDE_DIRECTORIES (
    ../utility
    ../Geometry
    ../models
    ../math
    ../AutoEquation
    ../GeomModels
    ../Equation
    ../tclapi
    ../errorSystem
    ../Circuit/data
    ../Data
    ../meshing
    ../MathEval
    ../common_api
    ../pythonapi
    ${TCL_INCLUDE}
    ${PYTHON_INCLUDE}
)

SET (LIBRARIES
    tclapi_interpreter
#    commands
#    Data
  #  AutoEquation
  #  meshing
 #   GeomModels
#    Equation
#    Geometry
#    math
#    MathEval
#    models
#    myThread
 #   circuitSources
 #   circuitIdeal
 #   circuitData
 #   errorSystem
    tclapi_api
 #   utility
)

SET (PYLIBRARIES
 #   commands
    pythonapi_interpreter
 #   Data
 #   AutoEquation
 #   meshing
 #   GeomModels
#    Equation
#    Geometry
#    math
#    MathEval
 #   models
 #   myThread
 #   circuitSources
 #   circuitIdeal
#    circuitData
 #   errorSystem
    pythonapi_api
#    utility
)


ADD_EXECUTABLE (devsim_tcl devsim_tcl.cc)
#TARGET_LINK_LIBRARIES(devsim_tcl ${LIBRARIES} ${TCL_ARCHIVE} ${ZLIB_ARCHIVE} ${SUPERLU_ARCHIVE} ${BLAS_ARCHIVE} ${SQLITE3_ARCHIVE} ${SYMDIFF_ARCHIVE} ${CGNS_ARCHIVE} ${PTHREAD_LIB} ${DLOPEN_LIB})

set(COMMON_LIBS devsim ${superlu} ${symdiff} ${sqlite3} ${cgns} ${HDF5_LIBRARIES})


target_link_libraries(devsim_tcl ${TCL_LIBRARY} tclapi_api tclapi_interpreter ${COMMON_LIBS})


add_executable(devsim_py devsim_py.cc)
target_link_libraries(devsim_py ${PYTHON_LIBRARIES} devsim ${ZLIB_LIBRARIES}  pythonapi_api pythonapi_interpreter ${COMMON_LIBS})


#ADD_EXECUTABLE (devsim_py devsim_py.cc)
#TARGET_LINK_LIBRARIES(devsim_py ${PYLIBRARIES} ${PYTHON_ARCHIVE} ${ZLIB_ARCHIVE} ${SUPERLU_ARCHIVE} ${BLAS_ARCHIVE} ${SQLITE3_ARCHIVE} ${TCL_STUB} ${SYMDIFF_ARCHIVE} ${CGNS_ARCHIVE} ${PTHREAD_LIB} ${DLOPEN_LIB})

#IF (WIN32)
#SET_TARGET_PROPERTIES(devsim_tcl PROPERTIES
#        LINK_FLAGS " /NODEFAULTLIB:LIBMSVCRT"
#        )
#ENDIF (WIN32)



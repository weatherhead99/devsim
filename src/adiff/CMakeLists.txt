INCLUDE_DIRECTORIES (
    ../errorSystem
)

SET (MC_SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/mcParser.cc
    ${CMAKE_CURRENT_BINARY_DIR}/mcScanner.cc
    mcModelCompiler.cc
    mcTest.cc
    mcModel.cc
)

SET (CXX_SRCS
    EquationObject.cc
    UserFunc.cc
    LogicalFunc.cc
)

SET (MC_CXX_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/mcParser.cc
    ${CMAKE_CURRENT_BINARY_DIR}/mcScanner.cc
)


INCLUDE_DIRECTORIES (
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../utility
)

#ADD_LIBRARY (adiff ${DS_SRCS} ${CXX_SRCS})
ADD_EXECUTABLE (modelcomp ${MC_SRCS} ${CXX_SRCS})

message(ERROR "modelcomp: ")

flex_generate(mcScanner ${CMAKE_CURRENT_BINARY_DIR}/mcParser.hh mc)
bison_generate(mcParser mc)

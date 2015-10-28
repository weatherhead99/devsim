SET (CXX_SRCS
    GeometryCommands.cc
    MaterialCommands.cc
    ModelCommands.cc
    EquationCommands.cc
    MathCommands.cc
    MeshingCommands.cc
    CircuitCommands.cc
    Validate.cc
    CheckFunctions.cc
)

include_directories(${CMAKE_SOURCE_DIR}/src/Circuit/models/sources)
include_directories(${CMAKE_SOURCE_DIR}/src/Circuit/models/ideal)

ADD_LIBRARY (commands OBJECT ${CXX_SRCS})



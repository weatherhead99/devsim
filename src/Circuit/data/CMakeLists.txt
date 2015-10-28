SET (CXX_SRCS
    CircuitNode.cc
    InstanceKeeper.cc
    InstanceModel.cc
    NodeKeeper.cc
)

include_directories(${CMAKE_SOURCE_DIR}/src/Circuit/models/sources)

ADD_LIBRARY (circuitData OBJECT ${CXX_SRCS})

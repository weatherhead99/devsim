SET (CXX_SRCS
    IdealCurrent.cc
    IdealVoltage.cc
    Signal.cc
)

INCLUDE_DIRECTORIES (
    ../../../utility
    ../../../math
    ../../data
)

#ADD_SUBDIRECTORY(data)
ADD_LIBRARY (circuitSources OBJECT ${CXX_SRCS})

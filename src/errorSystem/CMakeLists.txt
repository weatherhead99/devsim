SET (CXX_SRCS
  GeneralErrors.cc
  EquationErrors.cc
  ErrorHelpers.cc
  ModelErrors.cc
)

INCLUDE_DIRECTORIES (
  ../utility
  ../Geometry
  ../Equation
  ../math
  ../Data
  ../common_api
)

ADD_LIBRARY (errorSystem OBJECT ${CXX_SRCS})


SET (CXX_SRCS
    Bernoulli.cc
    Fermi.cc
    MathEval.cc
    MiscMathFunc.cc
    MathWrapper.cc
    MathPacket.cc
)



ADD_LIBRARY (MathEval OBJECT  ${CXX_SRCS})


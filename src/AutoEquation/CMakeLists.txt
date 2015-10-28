SET (CXX_SRCS
    ModelExprEval.cc
    ModelExprData.cc
    InterfaceNodeExprModel.cc
    NodeExprModel.cc
    EdgeExprModel.cc
    ExprEquation.cc
    ExprContactEquation.cc
    InterfaceModelExprEval.cc
    InterfaceExprEquation.cc
    InterfaceModelExprData.cc
    DefaultDerivatives.cc
    TriangleEdgeExprModel.cc
    TetrahedronEdgeExprModel.cc
    EquationFunctions.cc
)



ADD_LIBRARY (AutoEquation OBJECT ${CXX_SRCS})

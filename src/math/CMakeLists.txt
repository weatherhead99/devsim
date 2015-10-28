SET (CXX_SRCS
    TimeData.cc
    DenseMatrix.cc
    SuperLUPreconditioner.cc
    LinearSolver.cc
    DirectLinearSolver.cc
    IterativeLinearSolver.cc
    Matrix.cc
    CompressedMatrix.cc
    Newton.cc
    Preconditioner.cc
    SuperLUData.cc
    SuperLUDataZ.cc
    BlockPreconditioner.cc
    gmres.cc
    MathEnum.cc
)

include_directories(${CMAKE_SOURCE_DIR}/src/Circuit/data/)
ADD_LIBRARY (math OBJECT ${CXX_SRCS})

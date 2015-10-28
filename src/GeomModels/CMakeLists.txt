SET (CXX_SRCS
    NodePosition.cc
    NodeVolume.cc
    EdgeCouple.cc
    EdgeLength.cc
    EdgeIndex.cc
    EdgeInverseLength.cc
    ModelCreate.cc
    AtContactNode.cc
    SurfaceArea.cc
    UnitVec.cc
    VectorGradient.cc
    TriangleEdgeCouple.cc
    TriangleNodeVolume.cc
    TetrahedronEdgeCouple.cc
    TetrahedronNodeVolume.cc
    InterfaceNormal.cc
    TriangleCylindricalEdgeCouple.cc
    TriangleCylindricalNodeVolume.cc
    CylindricalEdgeCouple.cc
    CylindricalNodeVolume.cc
    CylindricalEdgeNodeVolume.cc
    CylindricalSurfaceArea.cc
    AverageEdgeModel.cc
)


ADD_LIBRARY (GeomModels OBJECT ${CXX_SRCS})


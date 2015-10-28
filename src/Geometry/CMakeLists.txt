SET (CXX_SRCS
    Device.cc
    Region.cc
    Edge.cc
    Node.cc
    Coordinate.cc
    Triangle.cc
    Contact.cc
    Permutation.cc
    Interface.cc
    GradientField.cc
    TriangleElementField.cc
    Tetrahedron.cc
    TetrahedronElementField.cc
    GeometryStream.cc
)

ADD_LIBRARY (Geometry OBJECT ${CXX_SRCS})

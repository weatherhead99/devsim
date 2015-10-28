SET (CXX_SRCS
    MeshLoaderStructs.cc
    MeshLoaderUtility.cc
    DevsimRestartWriter.cc
    DevsimReader.cc
    DevsimParser.cc
    DevsimScanner.cc
    DevsimLoader.cc
    DevsimWriter.cc
    GmshLoader.cc
    GmshReader.cc
    GmshParser.cc
    GmshScanner.cc
    GeniusLoader.cc
    GeniusReader.cc
    MeshKeeper.cc
    Mesh.cc
    MeshWriter.cc
    FloodsWriter.cc
    MeshUtil.cc
    Mesh1d.cc
    Mesh1dStructs.cc
    Mesh2d.cc
    Mesh2dStructs.cc
    VTKWriter.cc
    TecplotWriter.cc
)


flex_generate(DevsimScanner ${CMAKE_CURRENT_BINARY_DIR}/DevsimParser.hh Devsim)
bison_generate(DevsimParser Devsim)

flex_generate(GmshScanner ${CMAKE_CURRENT_BINARY_DIR}/GmshParser.hh Gmsh)
bison_generate(GmshParser Gmsh)

ADD_LIBRARY (meshing OBJECT ${CXX_SRCS})


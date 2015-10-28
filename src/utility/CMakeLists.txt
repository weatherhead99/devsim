SET (CXX_SRCS
    base64.cc
    FPECheck.cc
    dsAssert.cc
    dsException.cc
    GetGlobalParameter.cc
)


ADD_LIBRARY (utility OBJECT ${CXX_SRCS})
#ADD_EXECUTABLE (test_base64 test_base64.cc)
#TARGET_LINK_LIBRARIES(test_base64 utility ${ZLIB_ARCHIVE})


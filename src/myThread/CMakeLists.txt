SET (CXX_SRCS
  myqueue.cc
  myworker.cc
  mypacket.cc
  myThreadPool.cc
)


ADD_LIBRARY (myThread OBJECT ${CXX_SRCS})


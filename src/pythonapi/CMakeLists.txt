SET (CXX_SRCS1
   GetArgs.cc
   PythonAppInit.cc
   PythonCommands.cc
   CommandHandler.cc
)

SET (CXX_SRCS2
    ObjectHolder.cc
    OutputStream.cc
    Interpreter.cc
    dsTimer.cc
    mycondition.cc
    mymutex.cc
    threadBaseClass.cc
)

include_directories(${PYTHON_INCLUDE_DIR})

ADD_LIBRARY (pythonapi_interpreter SHARED ${CXX_SRCS1})
ADD_LIBRARY (pythonapi_api SHARED ${CXX_SRCS2})



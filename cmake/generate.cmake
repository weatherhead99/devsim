#macros for flex and bison
macro(flex_generate file_basename manual_depends projname)
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${file_basename}.cc 
  COMMAND ${FLEX} 
  ARGS -P${projname} -o${file_basename}.cc ${CMAKE_CURRENT_SOURCE_DIR}/${file_basename}.l
  DEPENDS ${manual_depends} ${CMAKE_CURRENT_SOURCE_DIR}/${file_basename}.l )

  set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/${file_basename}.cc
    PROPERTIES GENERATED TRUE )

if(NOT WIN32)
    set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/${file_basename}.cc
    COMPILE_FLAGS "-Wno-unused-function -Wno-sign-compare")
endif(NOT WIN32)

endmacro(flex_generate)

macro(bison_generate file_basename projname)
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${file_basename}.cc ${CMAKE_CURRENT_BINARY_DIR}/${file_basename}.hh
    COMMAND ${BISON}
    ARGS -p${projname} --debug -v -d -o ${file_basename}.cc ${CMAKE_CURRENT_SOURCE_DIR}/${file_basename}.y
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${file_basename}.y
)

endmacro(bison_generate)

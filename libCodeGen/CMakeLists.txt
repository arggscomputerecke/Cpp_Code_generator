file(GLOB src_files  "src/*.cpp" "src/*.cc")



add_library(libCodeGen SHARED ${src_files})

target_link_libraries(libCodeGen ${EXTERNAL_LIB_QT})
INCLUDE_DIRECTORIES(include/)

INSTALL(TARGETS libCodeGen  
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
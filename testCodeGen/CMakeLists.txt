file(GLOB src_files  "src/*.cpp" "src/*.cc" "src/*.cxx")

find_package(Qt5Test REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

MESSAGE(STATUS "<${libCodeGen}>")
MESSAGE(STATUS ${libCodeGen})
MESSAGE(STATUS "</${libCodeGen}>")
  set(EXTERNAL_LIB_QT ${Qt5Test_LIBRARIES} ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES})

  file(GLOB headers_files  "include/testCodeGen/*.hh")
qt5_wrap_cpp(MOCSrcs ${headers_files})
add_executable(codegend_tests  ${src_files} ${MOCSrcs})
include_directories(${Qt5Test_INCLUDE_DIRS})
  include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(include/)
include_directories(../libCodeGen/include/)

target_link_libraries(codegend_tests ${EXTERNAL_LIB_QT}  libCodeGen)


INSTALL(TARGETS codegend_tests  
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
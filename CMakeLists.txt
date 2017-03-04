# project name
PROJECT( CPP_Code_gen)

# project version
SET( ${PROJECT_NAME}_VERSION_MAJOR 1 )
SET( ${PROJECT_NAME}_VERSION_MINOR 0 )
SET( ${PROJECT_NAME}_VERSION_PATCH 0 )

 cmake_minimum_required(VERSION 3.7)
 
 

  
  
ADD_SUBDIRECTORY(libCodeGen)


ADD_SUBDIRECTORY(testCodeGen)
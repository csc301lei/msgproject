ZZ_PROJECT(msgproject)

include(toolchain/arm)
include(sdk/nanomsg)

set(CMAKE_CXX_STANDARD 11)

set(MSGPROJECT_ROOT  ${CMAKE_CURRENT_LIST_DIR})

ZZ_MODULE(
  NAME zzmsg
  TYPE SHARED
  VERSION ${ZZMSG_VERSION}
  SOURCES 
  		${MSGPROJECT_ROOT}/src/msg_pub
  		${MSGPROJECT_ROOT}/src/msg_sub
  		${MSGPROJECT_ROOT}/src/fatal
  INTERFACES ${MSGPROJECT_ROOT}/include
  PKG zzmsg
)

ZZ_MODULE(
  NAME msg_router
  TYPE APP
  SOURCES
    ${MSGPROJECT_ROOT}/src/msg_router
    ${MSGPROJECT_ROOT}/src/fatal
  INCS ${MSGPROJECT_ROOT}/include/
  IDL  $ENV{HOVER_REPO_ROOT}/src/drone_platform/interface_definition/proto/configuration.proto
  PKG  msg_router
)

ZZ_MODULE(
  NAME testsub
  TYPE APP
  SOURCES
    ${MSGPROJECT_ROOT}/src/testsub/testsub.cpp
    ${MSGPROJECT_ROOT}/src/msg_sub/msg_sub.cpp
    ${MSGPROJECT_ROOT}/src/fatal
  INCS 
  	${MSGPROJECT_ROOT}/include/
  IDL  
  		$ENV{HOVER_REPO_ROOT}/src/drone_platform/interface_definition/proto/configuration.proto
  		$ENV{HOVER_REPO_ROOT}/src/drone_platform/interface_definition/proto/sensor.proto
        $ENV{HOVER_REPO_ROOT}/src/drone_platform/interface_definition/proto/drone.proto
        $ENV{HOVER_REPO_ROOT}/src/drone_platform/interface_definition/proto/base.proto
  PKG  testsub
)




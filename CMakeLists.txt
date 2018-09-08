ZZ_PROJECT(msgproject)

include(toolchain/arm)
include(sdk/nanomsg)

set(CMAKE_CXX_STANDARD 11)

set(MSGPROJECT_ROOT  ${CMAKE_CURRENT_LIST_DIR})

ZZ_MODULE(
  NAME zzmsg
  TYPE SHARED
  VERSION ${ZZMSG_VERSION}
  SOURCES ${MSGPROJECT_ROOT}/src/msg_pub
  INTERFACES ${MSGPROJECT_ROOT}/include
  PKG zzmsg
)

ZZ_MODULE(
  NAME msg_router
  TYPE APP
  SOURCES
    ${MSGPROJECT_ROOT}/src/msg_router
  INCS ${MSGPROJECT_ROOT}/include/
  IDL  $ENV{HOVER_REPO_ROOT}/src/drone_platform/interface_definition/proto/configuration.proto
  PKG  msg_router
)

ZZ_MODULE(
  NAME msg_sub
  TYPE APP
  SOURCES
    ${MSGPROJECT_ROOT}/src/msg_sub
  INCS ${MSGPROJECT_ROOT}/include/
  IDL  $ENV{HOVER_REPO_ROOT}/src/drone_platform/interface_definition/proto/configuration.proto
  PKG  msg_sub
)


#####
# Contains variables and settings used
# by the CMake build system in order to
# build binary installers.
#####

SET(CPACK_PACKAGE_VENDOR "Unidata")

##
# Declare exclusions list used when building a source file.
# NOTE!! This list uses regular expressions, NOT wildcards!!
##
SET(CPACK_SOURCE_IGNORE_FILES "${CPACK_SOURCE_IGNORE_FILES}"
  "/expecttds3/"
  "/nocacheremote3/"
  "/nocacheremote4/"
  "/special3/"
  "${CMAKE_BINARY_DIR}/*"
  "/myhtml/*"
  "/.svn/"
  "my.*\\\\.sh"
  "/.deps/"
  "/.libs"
  "/html/"
  ".*\\\\.jar"
  ".*\\\\.jdl"
  ".*\\\\.sed"
  ".*\\\\.proto"
  ".*\\\\.texi"
  ".*\\\\.example"
  "Make0"
  "/obsolete/"
  "/unknown/"
  ".*~"
  )

SET(CPACK_PACKAGE_CONTACT "NCHDF4 on Github https://github.com/DennisHeimbigner/nchdf4.git")

IF(NOT CPACK_PACK_VERSION)
  SET(CPACK_PACKAGE_VERSION ${VERSION})
ENDIF()

IF(UNIX)
  SET(CPACK_GENERATOR "TGZ" "ZIP")
ENDIF()

IF(APPLE)
  SET(CPACK_SOURCE_GENERATOR "TGZ")
  SET(CPACK_GENERATOR "PackageMaker" "TGZ" "ZIP")
ENDIF()

INCLUDE(CPack)

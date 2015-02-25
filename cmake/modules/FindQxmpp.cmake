#
#  FindQxmpp.cmake
# 
#  Try to find the qxmpp library
#
#  You can provide a QXMPP_ROOT_DIR which contains lib and include directories
#
#  Once done this will define
#
#  QXMPP_FOUND - system found qxmpp
#  QXMPP_INCLUDE_DIRS - the qxmpp include directory
#  QXMPP_LIBRARIES - Link this to use qxmpp
#
#  Created on 3/10/2014 by Stephen Birarda
#  Copyright 2014 High Fidelity, Inc.
#
#  Distributed under the Apache License, Version 2.0.
#  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
# 

include("${MACRO_DIR}/HifiLibrarySearchHints.cmake")
hifi_library_search_hints("qxmpp")

find_path(QXMPP_INCLUDE_DIRS qxmpp/QXmppClient.h PATH_SUFFIXES include HINTS ${QXMPP_SEARCH_DIRS})

find_library(QXMPP_LIBRARY_RELEASE NAMES qxmpp PATH_SUFFIXES lib HINTS ${QXMPP_SEARCH_DIRS})
find_library(QXMPP_LIBRARY_DEBUG NAMES qxmpp_d PATH_SUFFIXES lib HINTS ${QXMPP_SEARCH_DIRS})

if (WIN32)
  find_path(QXMPP_DLL_PATH NAMES qxmpp.dll PATH_SUFFIXES lib HINTS ${QXMPP_SEARCH_DIRS})
endif ()

find_package(Qt5 COMPONENTS Xml REQUIRED)

include(SelectLibraryConfigurations)
select_library_configurations(QXMPP)

set(QXMPP_LIBRARIES "${QXMPP_LIBRARY}" Qt5::Xml)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QXmpp DEFAULT_MSG QXMPP_INCLUDE_DIRS QXMPP_LIBRARIES QXMPP_LIBRARY)

if (QXMPP_DLL_PATH)
  add_paths_to_fixup_libs(${QXMPP_DLL_PATH})
endif ()
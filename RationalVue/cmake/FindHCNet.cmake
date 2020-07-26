# - Try to find HCNetSDK
#
# The following variables are optionally searched for defaults
#  HCNET_ROOT_DIR:            Base directory where all HCNET components are found
#
# The following are set after configuration is done:
#  HCNET_FOUND
#  HCNET_INCLUDE_DIRS
#  HCNET_LIBRARIES
#  HCNET_LIBRARYRARY_DIRS

include(FindPackageHandleStandardArgs)

set(HCNET_ROOT_DIR "" CACHE PATH "Folder contains HCNetSDK")


find_path(HCNET_INCLUDE_DIR HCNetSDK.h HINTS ${HCNET_ROOT_DIR} PATH_SUFFIXES include HCNetSDK/include)

        
find_library(HCNET_LIBRARY      HCNetSDK        HINTS ${HCNET_ROOT_DIR} PATH_SUFFIXES lib lib64)
find_library(PlayCtrl_LIBRARY   PlayCtrl        HINTS ${HCNET_ROOT_DIR} PATH_SUFFIXES lib lib64)
find_library(GDIPLUS_LIBRARY    GdiPlus         HINTS ${HCNET_ROOT_DIR} PATH_SUFFIXES lib lib64)



find_package_handle_standard_args(HCNET DEFAULT_MSG HCNET_INCLUDE_DIR HCNET_LIBRARY)

if(HCNET_FOUND)
  set(HCNET_INCLUDE_DIRS ${HCNET_INCLUDE_DIR})
  set(HCNET_LIBRARIES ${HCNET_LIBRARY} ${PlayCtrl_LIBRARY} ${GDIPLUS_LIBRARY})
  message(STATUS "Found HCNetSDK    (include: ${HCNET_INCLUDE_DIR}, library: ${HCNET_LIBRARIES})")
  mark_as_advanced(HCNET_ROOT_DIR HCNET_LIBRARY_RELEASE HCNET_LIBRARY_DEBUG
                                 HCNET_LIBRARY HCNET_INCLUDE_DIR)
endif()

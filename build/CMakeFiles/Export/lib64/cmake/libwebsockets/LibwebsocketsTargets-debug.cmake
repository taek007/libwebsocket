#----------------------------------------------------------------
# Generated CMake target import file for configuration "DEBUG".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "websockets" for configuration "DEBUG"
set_property(TARGET websockets APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(websockets PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "/usr/lib64/libz.so;/usr/lib64/libssl.so;/usr/lib64/libcrypto.so;/usr/local/lib/libev.so;m"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib64/libwebsockets.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS websockets )
list(APPEND _IMPORT_CHECK_FILES_FOR_websockets "${_IMPORT_PREFIX}/lib64/libwebsockets.a" )

# Import target "websockets_shared" for configuration "DEBUG"
set_property(TARGET websockets_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(websockets_shared PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "/usr/lib64/libz.so;/usr/lib64/libssl.so;/usr/lib64/libcrypto.so;/usr/local/lib/libev.so;m"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib64/libwebsockets.so.8"
  IMPORTED_SONAME_DEBUG "libwebsockets.so.8"
  )

list(APPEND _IMPORT_CHECK_TARGETS websockets_shared )
list(APPEND _IMPORT_CHECK_FILES_FOR_websockets_shared "${_IMPORT_PREFIX}/lib64/libwebsockets.so.8" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

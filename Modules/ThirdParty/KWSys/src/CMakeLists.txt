set(KWSYS_NAMESPACE itksys)
set(KWSYS_USE_SystemTools 1)
set(KWSYS_USE_RegularExpression 1)
set(KWSYS_USE_Directory 1)
set(KWSYS_USE_Base64 1)
set(KWSYS_USE_MD5 1 )
set(KWSYS_USE_CommandLineArguments 1)
set(KWSYS_USE_Process 1)
if(ITK_DYNAMIC_LOADING)
  set(KWSYS_USE_DynamicLoader 1)
else()
  set(KWSYS_USE_DynamicLoader 0)
endif()
set(KWSYS_USE_Glob 1)
set(KWSYS_USE_Registry 1)
set(KWSYS_USE_SystemInformation 1)
set(KWSYS_INSTALL_INCLUDE_DIR ${ITKKWSys_INSTALL_INCLUDE_DIR})
set(KWSYS_INSTALL_LIB_DIR ${ITKKWSys_INSTALL_LIBRARY_DIR})
set(KWSYS_INSTALL_BIN_DIR ${ITKKWSys_INSTALL_RUNTIME_DIR})
set(KWSYS_INSTALL_DOC_DIR ${ITK_INSTALL_DOC_DIR})
set(KWSYS_INSTALL_EXPORT_NAME ${ITKKWSys-targets})
set(KWSYS_INSTALL_COMPONENT_NAME_RUNTIME RuntimeLibraries)
set(KWSYS_INSTALL_COMPONENT_NAME_DEVELOPMENT Development)
set(KWSYS_PROPERTIES_C WINDOWS_EXPORT_ALL_SYMBOLS FALSE)
set( _macosx_rpath 1)
if(DEFINED CMAKE_MACOSX_RPATH AND NOT "${CMAKE_MACOSX_RPATH}" STREQUAL "")
  set(_macosx_rpath ${CMAKE_MACOSX_RPATH})
endif()
set(KWSYS_PROPERTIES_CXX MACOSX_RPATH ${_macosx_rpath} WINDOWS_EXPORT_ALL_SYMBOLS FALSE)

add_subdirectory(KWSys)
itk_module_target(${KWSYS_NAMESPACE} NO_INSTALL)

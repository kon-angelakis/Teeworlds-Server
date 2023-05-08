# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_ARCHIVE_COMPONENT_INSTALL "ON")
set(CPACK_ARCHIVE_PORTABLE_FILE_NAME "teeworlds-0.6.5-linux_x86_64")
set(CPACK_BUILD_SOURCE_DIRS "/home/kostas/Desktop/Teeworlds;/home/kostas/Desktop/Teeworlds/build")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENTS_ALL "portable")
set(CPACK_COMPONENTS_ALL_SET_BY_USER "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.22/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "teeworlds built using CMake")
set(CPACK_GENERATOR "TGZ;TXZ")
set(CPACK_INSTALL_CMAKE_PROJECTS "/home/kostas/Desktop/Teeworlds/build;teeworlds;ALL;/")
set(CPACK_INSTALL_PREFIX "/usr/local")
set(CPACK_MODULE_PATH "/home/kostas/Desktop/Teeworlds/cmake")
set(CPACK_NSIS_DISPLAY_NAME "teeworlds 0.6.5")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "teeworlds 0.6.5")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "/home/kostas/Desktop/Teeworlds/build/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.22/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "teeworlds built using CMake")
set(CPACK_PACKAGE_FILE_NAME "teeworlds-0.6.5-linux_x86_64")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "teeworlds 0.6.5")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "teeworlds 0.6.5")
set(CPACK_PACKAGE_NAME "teeworlds")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Humanity")
set(CPACK_PACKAGE_VERSION "0.6.5")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "6")
set(CPACK_PACKAGE_VERSION_PATCH "5")
set(CPACK_RESOURCE_FILE_LICENSE "/usr/share/cmake-3.22/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "/usr/share/cmake-3.22/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-3.22/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ;TBZ2;TXZ")
set(CPACK_SOURCE_IGNORE_FILES "\\.o$;\\.pyc$;/\\.git;/__pycache__/;/home/kostas/Desktop/Teeworlds/([^Cbccdddloorsss]|$);/home/kostas/Desktop/Teeworlds/C([^M]|$);/home/kostas/Desktop/Teeworlds/b([^a]|$);/home/kostas/Desktop/Teeworlds/c([^mo]|$);/home/kostas/Desktop/Teeworlds/d([^aao]|$);/home/kostas/Desktop/Teeworlds/l([^i]|$);/home/kostas/Desktop/Teeworlds/o([^bt]|$);/home/kostas/Desktop/Teeworlds/r([^e]|$);/home/kostas/Desktop/Teeworlds/s([^crt]|$);/home/kostas/Desktop/Teeworlds/CM([^a]|$);/home/kostas/Desktop/Teeworlds/ba([^m]|$);/home/kostas/Desktop/Teeworlds/cm([^a]|$);/home/kostas/Desktop/Teeworlds/co([^n]|$);/home/kostas/Desktop/Teeworlds/da([^tt]|$);/home/kostas/Desktop/Teeworlds/do([^c]|$);/home/kostas/Desktop/Teeworlds/li([^c]|$);/home/kostas/Desktop/Teeworlds/ob([^j]|$);/home/kostas/Desktop/Teeworlds/ot([^h]|$);/home/kostas/Desktop/Teeworlds/re([^a]|$);/home/kostas/Desktop/Teeworlds/sc([^r]|$);/home/kostas/Desktop/Teeworlds/sr([^c]|$);/home/kostas/Desktop/Teeworlds/st([^o]|$);/home/kostas/Desktop/Teeworlds/CMa([^k]|$);/home/kostas/Desktop/Teeworlds/bam([^.]|$);/home/kostas/Desktop/Teeworlds/cma([^k]|$);/home/kostas/Desktop/Teeworlds/con([^f]|$);/home/kostas/Desktop/Teeworlds/dat([^aa]|$);/home/kostas/Desktop/Teeworlds/doc([^s]|$);/home/kostas/Desktop/Teeworlds/lic([^e]|$);/home/kostas/Desktop/Teeworlds/obj([^s]|$);/home/kostas/Desktop/Teeworlds/oth([^e]|$);/home/kostas/Desktop/Teeworlds/rea([^d]|$);/home/kostas/Desktop/Teeworlds/scr([^i]|$);/home/kostas/Desktop/Teeworlds/src([^/]|$);/home/kostas/Desktop/Teeworlds/sto([^r]|$);/home/kostas/Desktop/Teeworlds/CMak([^e]|$);/home/kostas/Desktop/Teeworlds/bam\\.([^l]|$);/home/kostas/Desktop/Teeworlds/cmak([^e]|$);/home/kostas/Desktop/Teeworlds/conf([^i]|$);/home/kostas/Desktop/Teeworlds/data([^/s]|$);/home/kostas/Desktop/Teeworlds/docs([^/]|$);/home/kostas/Desktop/Teeworlds/lice([^n]|$);/home/kostas/Desktop/Teeworlds/objs([^/]|$);/home/kostas/Desktop/Teeworlds/othe([^r]|$);/home/kostas/Desktop/Teeworlds/read([^m]|$);/home/kostas/Desktop/Teeworlds/scri([^p]|$);/home/kostas/Desktop/Teeworlds/stor([^a]|$);/home/kostas/Desktop/Teeworlds/CMake([^L]|$);/home/kostas/Desktop/Teeworlds/bam\\.l([^u]|$);/home/kostas/Desktop/Teeworlds/cmake([^/]|$);/home/kostas/Desktop/Teeworlds/confi([^g]|$);/home/kostas/Desktop/Teeworlds/datas([^r]|$);/home/kostas/Desktop/Teeworlds/licen([^s]|$);/home/kostas/Desktop/Teeworlds/other([^/]|$);/home/kostas/Desktop/Teeworlds/readm([^e]|$);/home/kostas/Desktop/Teeworlds/scrip([^t]|$);/home/kostas/Desktop/Teeworlds/stora([^g]|$);/home/kostas/Desktop/Teeworlds/CMakeL([^i]|$);/home/kostas/Desktop/Teeworlds/bam\\.lu([^a]|$);/home/kostas/Desktop/Teeworlds/config([^u]|$);/home/kostas/Desktop/Teeworlds/datasr([^c]|$);/home/kostas/Desktop/Teeworlds/licens([^e]|$);/home/kostas/Desktop/Teeworlds/readme([^.]|$);/home/kostas/Desktop/Teeworlds/script([^s]|$);/home/kostas/Desktop/Teeworlds/storag([^e]|$);/home/kostas/Desktop/Teeworlds/CMakeLi([^s]|$);/home/kostas/Desktop/Teeworlds/configu([^r]|$);/home/kostas/Desktop/Teeworlds/datasrc([^/]|$);/home/kostas/Desktop/Teeworlds/license([^.]|$);/home/kostas/Desktop/Teeworlds/readme\\.([^t]|$);/home/kostas/Desktop/Teeworlds/scripts([^/]|$);/home/kostas/Desktop/Teeworlds/storage([^.]|$);/home/kostas/Desktop/Teeworlds/CMakeLis([^t]|$);/home/kostas/Desktop/Teeworlds/configur([^e]|$);/home/kostas/Desktop/Teeworlds/license\\.([^t]|$);/home/kostas/Desktop/Teeworlds/readme\\.t([^x]|$);/home/kostas/Desktop/Teeworlds/storage\\.([^c]|$);/home/kostas/Desktop/Teeworlds/CMakeList([^s]|$);/home/kostas/Desktop/Teeworlds/configure([^.]|$);/home/kostas/Desktop/Teeworlds/license\\.t([^x]|$);/home/kostas/Desktop/Teeworlds/readme\\.tx([^t]|$);/home/kostas/Desktop/Teeworlds/storage\\.c([^f]|$);/home/kostas/Desktop/Teeworlds/CMakeLists([^.]|$);/home/kostas/Desktop/Teeworlds/configure\\.([^l]|$);/home/kostas/Desktop/Teeworlds/license\\.tx([^t]|$);/home/kostas/Desktop/Teeworlds/storage\\.cf([^g]|$);/home/kostas/Desktop/Teeworlds/CMakeLists\\.([^t]|$);/home/kostas/Desktop/Teeworlds/configure\\.l([^u]|$);/home/kostas/Desktop/Teeworlds/CMakeLists\\.t([^x]|$);/home/kostas/Desktop/Teeworlds/configure\\.lu([^a]|$);/home/kostas/Desktop/Teeworlds/CMakeLists\\.tx([^t]|$)")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/kostas/Desktop/Teeworlds/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "teeworlds-0.6.5-src")
set(CPACK_STRIP_FILES "TRUE")
set(CPACK_SYSTEM_NAME "linux_x86_64")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "linux_x86_64")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/kostas/Desktop/Teeworlds/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()

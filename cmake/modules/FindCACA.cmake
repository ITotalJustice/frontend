
if(CMAKE_VERSION VERSION_LESS 2.8.12)
    message(FATAL_ERROR "CMake 2.8.12 is required by Fidncaca.cmake")
endif()
if(CMAKE_MINIMUM_REQUIRED_VERSION VERSION_LESS 2.8.12)
    message(AUTHOR_WARNING "Your project should require at least CMake 2.8.12 to use Fidncaca.cmake")
endif()
# Use pkg-config to get the directories and then use these values
# in the FIND_PATH() and FIND_LIBRARY() calls
find_package(PkgConfig)
pkg_check_modules(PKG_caca QUIET caca)
set(caca_DEFINITIONS ${PKG_caca_CFLAGS_OTHER})
set(caca_VERSION ${PKG_caca_VERSION})

find_path(caca_INCLUDE_DIR
    NAMES
        caca.h
    HINTS
        ${PKG_caca_INCLUDE_DIRS}
)
find_library(caca_LIBRARY
    NAMES
        caca
    HINTS
        ${PKG_caca_LIBRARY_DIRS}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(caca
    FOUND_VAR
        caca_FOUND
    REQUIRED_VARS
        caca_LIBRARY
        caca_INCLUDE_DIR
    VERSION_VAR
        caca_VERSION
)

if(caca_FOUND AND NOT TARGET caca::caca)
    set(GBM_LIBRARIES ${CACA_LIBRARY})
    set(GBM_INCLUDE_DIRS ${CACA_INCLUDE_DIR})
    # set(GBM_DEFINITIONS -DHAVE_GBM=1)
    
    add_library(caca::caca UNKNOWN IMPORTED)
    set_target_properties(caca::caca PROPERTIES
        IMPORTED_LOCATION "${caca_LIBRARY}"
        INTERFACE_COMPILE_OPTIONS "${caca_DEFINITIONS}"
        INTERFACE_INCLUDE_DIRECTORIES "${caca_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(caca_LIBRARY caca_INCLUDE_DIR)

include(FeatureSummary)
set_package_properties(caca PROPERTIES
    URL "http://caca.zoy.org/wiki/libcaca"
    DESCRIPTION "libcaca is the Colour AsCii Art library."
)

include(ExternalProject)

set(SKIA_LIB_NAME skia)
set(SKIA_LIB ${CMAKE_STATIC_LIBRARY_PREFIX}${SKIA_LIB_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX})

find_program(PYTHON NAMES python3 python python2)
find_program(NINJA NAMES ninja)

ExternalProject_Add(skia_build
        PREFIX skia
        SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src
        PATCH_COMMAND ${PYTHON} <SOURCE_DIR>/tools/git-sync-deps
        CONFIGURE_COMMAND <SOURCE_DIR>/bin/gn gen --root=<SOURCE_DIR> <BINARY_DIR> "--args=is_official_build=true"
        BUILD_COMMAND ${NINJA} -C <BINARY_DIR>
        BUILD_BYPRODUCTS <BINARY_DIR>/${SKIA_LIB}
        INSTALL_COMMAND ""
        )
ExternalProject_Get_Property(skia_build SOURCE_DIR BINARY_DIR)

set(SYS_DEP_NAMES
        "pthread"
        "fontconfig"
        "dl"
        "freetype"
        "expat"
        "GL"
        "z"
        "harfbuzz"
        "harfbuzz-subset"
        "jpeg"
        "png"
        "webp"
        "webpdemux"
        "webpmux"
        )

set(MOD_DEP_NAMES
        "skparagraph"
        )

foreach (DEP_NAME IN LISTS SYS_DEP_NAMES)
    find_library(LIB${DEP_NAME} ${DEP_NAME} REQUIRED)
    set(DEPS ${DEPS} ${LIB${DEP_NAME}})
endforeach ()

foreach (DEP_NAME IN LISTS MOD_DEP_NAMES)
    set(DEPS ${DEPS} ${BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${DEP_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX})
endforeach ()

set(HEADERS
        ${SOURCE_DIR}/include/c
        ${SOURCE_DIR}/include/codec
        ${SOURCE_DIR}/include/config
        ${SOURCE_DIR}/include/core
        ${SOURCE_DIR}/include/effects
        ${SOURCE_DIR}/include/gpu
        ${SOURCE_DIR}/include/gpu/gl
        ${SOURCE_DIR}/include/pathops
        ${SOURCE_DIR}/include/ports
        ${SOURCE_DIR}/include/svg
        ${SOURCE_DIR}/include/utils
        ${SOURCE_DIR}/modules/skparagraph/include
        ${SOURCE_DIR}/modules/skparagraph/utils # TODO: remove
        )

set(DEFINITIONS
        #"NDEBUG"
        "SK_R32_SHIFT=16"
        "SK_ENABLE_SKSL"
        "SK_GAMMA_APPLY_TO_A8"
        "SKIA_IMPLEMENTATION=1"
        "SK_GL"
        )

add_library(skia STATIC IMPORTED GLOBAL)
set_target_properties(skia PROPERTIES
        IMPORTED_LOCATION "${BINARY_DIR}/${SKIA_LIB}"
        INTERFACE_COMPILE_DEFINITIONS "${DEFINITIONS}"
        INTERFACE_LINK_LIBRARIES "${DEPS}"
        INTERFACE_INCLUDE_DIRECTORIES "${HEADERS};${SOURCE_DIR}"
        )
add_dependencies(skia skia_build)

include(ExternalProject)

set(SKIA_LIB_NAME skia)
set(SKIA_LIB ${CMAKE_STATIC_LIBRARY_PREFIX}${SKIA_LIB_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX})

find_program(PYTHON NAMES python3 python python2)
find_program(NINJA NAMES ninja)
if (APPLE)
    set(CONFIGURE_COMMAND <SOURCE_DIR>/bin/gn gen --root=<SOURCE_DIR> <BINARY_DIR> "--args=is_official_build=true \
        skia_use_system_icu=false \
        skia_use_system_harfbuzz=false \
        skia_use_system_libjpeg_turbo=false \
        skia_use_system_libpng=false \
        skia_use_system_libwebp=false")
else ()
    set(CONFIGURE_COMMAND <SOURCE_DIR>/bin/gn gen --root=<SOURCE_DIR> <BINARY_DIR> "--args=is_official_build=true")
endif ()
ExternalProject_Add(skia_build
        PREFIX skia
        SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src
        PATCH_COMMAND ${PYTHON} <SOURCE_DIR>/tools/git-sync-deps
        CONFIGURE_COMMAND ${CONFIGURE_COMMAND}
        BUILD_COMMAND ${NINJA} -C <BINARY_DIR>
        BUILD_BYPRODUCTS <BINARY_DIR>/${SKIA_LIB}
        INSTALL_COMMAND ""
        )
ExternalProject_Get_Property(skia_build SOURCE_DIR BINARY_DIR)

# Compile definitions (not for Skia compilation: only for included Skia headers)
set(DEFINITIONS
        "SK_GL"
        )

# Link libraries
set(SYS_DEP_NAMES
        "pthread"
        "fontconfig"
        "dl"
        "freetype"
        "expat"
        "z"
        "harfbuzz"
        "harfbuzz-subset"
        "jpeg"
        "png"
        "webp"
        "webpdemux"
        "webpmux"
        )
if (APPLE)
    list(APPEND SYS_DEP_NAMES
            "CoreGraphics"
            "CoreServices"
            "CoreText"
            )
endif ()
foreach (DEP_NAME IN LISTS SYS_DEP_NAMES)
    find_library(LIB${DEP_NAME} ${DEP_NAME} REQUIRED)
    list(APPEND DEPS ${LIB${DEP_NAME}})
endforeach ()
find_package(OpenGL REQUIRED)
list(APPEND DEPS ${OPENGL_LIBRARIES})

# Include directories
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
        # TODO: check on Linux
        ${OPENGL_INCLUDE_DIR}/Headers
        )

add_library(skia STATIC IMPORTED GLOBAL)
set_target_properties(skia PROPERTIES
        IMPORTED_LOCATION "${BINARY_DIR}/${SKIA_LIB}"
        INTERFACE_COMPILE_DEFINITIONS "${DEFINITIONS}"
        INTERFACE_LINK_LIBRARIES "${DEPS}"
        INTERFACE_INCLUDE_DIRECTORIES "${HEADERS};${SOURCE_DIR}"
        )
add_dependencies(skia skia_build)

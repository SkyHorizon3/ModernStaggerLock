add_library("${PROJECT_NAME}" SHARED)

# Set C++ standard and enable folder organization
target_compile_features("${PROJECT_NAME}" PRIVATE cxx_std_23)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Include C++ and header files from source directories
include(AddCXXFiles)
add_cxx_files("${PROJECT_NAME}")

# Generate configuration files
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Plugin.h.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake/Plugin.h" @ONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.rc.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake/version.rc" @ONLY)

# Add generated files to the target
target_sources("${PROJECT_NAME}" PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/cmake/Plugin.h ${CMAKE_CURRENT_BINARY_DIR}/cmake/version.rc)

# Precompile headers
target_precompile_headers("${PROJECT_NAME}" PRIVATE include/PCH.h)

# Enable interprocedural optimization
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF)

# Set Boost options
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)

#pdb
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

# MSVC-specific settings
if (CMAKE_GENERATOR MATCHES "Visual Studio")
    add_compile_definitions(_UNICODE)

    # Set compiler definitions for debug and release builds
    target_compile_definitions("${PROJECT_NAME}" PRIVATE "$<$<CONFIG:DEBUG>:DEBUG>")
    
    # Compiler and linker options
    set(SC_RELEASE_OPTS "/Zi;/fp:fast;/GL;/Gy-;/Gm-;/Gw;/sdl-;/GS-;/guard:cf-;/O2;/Ob2;/Oi;/Ot;/Oy;/fp:except-")
    
    target_compile_options("${PROJECT_NAME}" PRIVATE
        /MP /await /W4 /WX /permissive- /Zc:alignedNew /Zc:auto /Zc:__cplusplus /Zc:externC /Zc:externConstexpr
        /Zc:forScope /Zc:hiddenFriend /Zc:implicitNoexcept /Zc:lambda /Zc:noexceptTypes /Zc:preprocessor /Zc:referenceBinding
        /Zc:rvalueCast /Zc:sizedDealloc /Zc:strictStrings /Zc:ternary /Zc:threadSafeInit /Zc:trigraphs /Zc:wchar_t
        /wd4200 # nonstandard extension used: zero-sized array in struct/union
    )
    
    target_compile_options("${PROJECT_NAME}" PUBLIC "$<$<CONFIG:DEBUG>:/fp:strict>")
    target_compile_options("${PROJECT_NAME}" PUBLIC "$<$<CONFIG:DEBUG>:/ZI>")
    target_compile_options("${PROJECT_NAME}" PUBLIC "$<$<CONFIG:DEBUG>:/Od>")
    target_compile_options("${PROJECT_NAME}" PUBLIC "$<$<CONFIG:DEBUG>:/Gy>")
    target_compile_options("${PROJECT_NAME}" PUBLIC "$<$<CONFIG:RELEASE>:${SC_RELEASE_OPTS}>")
    
    target_link_options("${PROJECT_NAME}" PRIVATE
        /WX
        "$<$<CONFIG:DEBUG>:/INCREMENTAL;/OPT:NOREF;/OPT:NOICF>"
        "$<$<CONFIG:RELEASE>:/LTCG;/INCREMENTAL:NO;/OPT:REF;/OPT:ICF;/DEBUG:FULL>"
    )
endif()

# Find required packages (adjust as needed)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/CommonLibSSE CommonLibSSE)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/DKUtil DKUtil)
find_package(spdlog CONFIG REQUIRED)

# Include directories and libraries
target_include_directories("${PROJECT_NAME}" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories("${PROJECT_NAME}" PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/cmake ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Link libraries
target_link_libraries("${PROJECT_NAME}" 
PUBLIC 
CommonLibSSE::CommonLibSSE
PRIVATE
DKUtil::DKUtil
)
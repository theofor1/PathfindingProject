# MonProjetCMake/Engine/CMakeLists.txt

project(Engine)

# Ajoutez tous les fichiers source et en-tête spécifiques à la bibliothèque Engine (de manière récursive)
file(GLOB_RECURSE ENGINE_SOURCES
    *.cpp
    *.h
    *.hxx
)

# Créez la bibliothèque Engine (par exemple, une bibliothèque statique)
add_library(Engine STATIC ${ENGINE_SOURCES})

# Incluez le répertoire parent comme un répertoire d'inclusion système
target_include_directories(Engine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Gameplay/>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Gameplay/GameObject/>

    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../rapidxml> # Inclure la dépendence rapidxml
    $<BUILD_INTERFACE:${SFML_SOURCE_DIR}/include>  # Chemin absolu vers le répertoire d'en-tête SFML
)

# Organisez l'architecture virtuelle pour refléter la structure des fichiers
foreach(_source IN ITEMS ${ENGINE_SOURCES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

########################################################################################################################
# Dépendances

########################################################################################################################
# SFML
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

target_link_libraries(Engine PRIVATE sfml-graphics)
target_compile_features(Engine PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET Engine
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Engine>
        VERBATIM)
endif()

install(TARGETS Engine)
########################################################################################################################
########################################################################################################################


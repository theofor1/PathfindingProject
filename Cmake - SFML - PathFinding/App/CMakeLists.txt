# MonProjetCMake/App/CMakeLists.txt

project(App)

# Ajoutez tous les fichiers source spécifiques à votre application
file(GLOB APP_SOURCES
    src/*.cpp
)

add_executable(App ${APP_SOURCES})

# Incluez le répertoire d'en-tête de Engine comme un répertoire d'inclusion système
target_include_directories(App PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>  # Chemin absolu vers le répertoire d'en-tête
)

# Lien avec la bibliothèque Engine
target_link_libraries(App PRIVATE Engine)

########################################################################################################################
# SFML
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

target_link_libraries(App PRIVATE sfml-graphics)
target_compile_features(App PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET App
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:App>
        VERBATIM)
endif()

install(TARGETS App)
########################################################################################################################


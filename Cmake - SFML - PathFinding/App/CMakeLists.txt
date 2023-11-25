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
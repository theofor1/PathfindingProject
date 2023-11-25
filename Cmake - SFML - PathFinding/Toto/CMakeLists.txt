# MonProjetCMake/Toto/CMakeLists.txt

project(Toto)

# Ajoutez tous les fichiers source spécifiques à la bibliothèque Toto (de manière récursive)
file(GLOB_RECURSE TOTO_SOURCES
    *.cpp
)

# Créez la bibliothèque Toto (par exemple, une bibliothèque statique)
add_library(Toto STATIC ${TOTO_SOURCES})

# Incluez le répertoire actuel pour que les fichiers d'en-tête soient trouvés
target_include_directories(Toto PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Organisez l'architecture virtuelle pour refléter la structure des fichiers
foreach(_source IN ITEMS ${TOTO_SOURCES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

# Vous pouvez ajouter d'autres dépendances, etc.

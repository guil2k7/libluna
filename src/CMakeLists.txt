include_directories(${LUNA_INCLUDE_DIRS})
link_libraries(spdlog::spdlog)

set(LUNA_SOURCE_FILES
    Main.cc
)

add_subdirectory(Core)
add_subdirectory(Serde)
add_subdirectory(Game)
add_subdirectory(Network)
add_subdirectory(Loader)
add_subdirectory(Luna)

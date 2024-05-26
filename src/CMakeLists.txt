set(LUNA_LINK_LIBRARIES spdlog::spdlog imgui)
set(LUNA_SOURCE_FILES Main.cc)

add_subdirectory(Core)
add_subdirectory(Game)

add_library(luna SHARED ${LUNA_SOURCE_FILES})
target_include_directories(luna PRIVATE ${LUNA_INCLUDE_DIRS})
target_link_libraries(luna PRIVATE ${LUNA_LINK_LIBRARIES})

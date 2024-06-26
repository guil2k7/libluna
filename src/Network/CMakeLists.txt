set(LUNA_SOURCE_FILES
    Client.cc
    RemotePlayer.cc
)

add_library(LunaNetwork STATIC ${LUNA_SOURCE_FILES})
target_link_libraries(LunaNetwork PUBLIC raknet)

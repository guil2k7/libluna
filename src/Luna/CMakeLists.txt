set(LUNA_SOURCE_FILES
    Main.cc
)

add_library(Luna SHARED ${LUNA_SOURCE_FILES})

target_link_libraries(Luna PRIVATE
    LunaCore
    LunaGame
    LunaNetwork
    LunaSerde
)

set_target_properties(Luna PROPERTIES PREFIX "")

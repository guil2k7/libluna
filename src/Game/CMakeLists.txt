set(LUNA_SOURCE_FILES
    Game.cc
    Gui.cc
    Hud.cc
    imgui_impl_rw.cc
    Luna.cc
    Pad.cc
    Ped.cc
    PlayerPed.cc
    RW.cc
    OSEvent.cc
    World.cc
)

add_library(LunaGame STATIC ${LUNA_SOURCE_FILES})
target_link_libraries(LunaGame PUBLIC imgui LunaCore LunaNetwork)

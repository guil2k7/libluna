set(LUNA_SOURCE_FILES
    Main.cc
)

add_library(LunaLoader SHARED ${LUNA_SOURCE_FILES})
target_link_libraries(LunaLoader PUBLIC LunaCore)

set(LUNA_SOURCE_FILES
    Memory.cc
    MemoryExec.cc
    ThumbHook.cc
    ArmHook.cc
)

add_library(LunaCore STATIC ${LUNA_SOURCE_FILES})

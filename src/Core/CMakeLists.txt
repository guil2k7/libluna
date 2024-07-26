set(LUNA_SOURCE_FILES
    Memory.cc
    MemoryExec.cc
    Hooker.cc
)

add_library(LunaCore STATIC ${LUNA_SOURCE_FILES})

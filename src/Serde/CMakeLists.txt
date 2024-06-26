set(LUNA_SOURCE_FILES
    Deserializer.cc
    BitDeserializer.cc
    BitSerializer.cc
)

add_library(LunaSerde STATIC ${LUNA_SOURCE_FILES})

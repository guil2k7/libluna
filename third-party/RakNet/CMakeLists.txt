cmake_minimum_required(VERSION 3.22)
project(RakNet VERSION 2.52 LANGUAGES C CXX)

option(THREAD_SAFE OFF)

set(RAKNET_SOURCES
    Source/SAMP/Obfuscator.cpp
    Source/BitStream.cpp
    Source/CheckSum.cpp
    Source/DataBlockEncryptor.cpp
    Source/DS_HuffmanEncodingTree.cpp
    Source/GetTime.cpp
    Source/InternalPacketPool.cpp
    Source/NetworkTypes.cpp
    Source/PluginInterface.cpp
    Source/RakNetworkFactory.cpp
    Source/RakPeer.cpp
    Source/RakSleep.cpp
    Source/Rand.cpp
    Source/ReliabilityLayer.cpp
    Source/SHA1.cpp
    Source/SimpleMutex.cpp
    Source/SocketLayer.cpp
    Source/StringCompressor.cpp
    Source/StringTable.cpp
    Source/rijndael.cpp
)

add_library(raknet STATIC ${RAKNET_SOURCES})
target_include_directories(raknet INTERFACE Include PRIVATE Include/RakNet)

if(THREAD_SAFE)
    target_compile_definitions(raknet PRIVATE _RAKNET_THREADSAFE=1)
endif()

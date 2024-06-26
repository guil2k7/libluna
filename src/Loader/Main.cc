// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Core/Memory.hh>
#include <Luna/Core/ThumbHook.hh>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/android_sink.h>
#include <dlfcn.h>
#include <jni.h>

using namespace Luna::Core;

static void* libGTASAHandle = nullptr;
static void* libLunaHandle = nullptr;
static uint8_t* gameAddress = nullptr;

static inline char const* GetHomeDir() {
    return reinterpret_cast<char const*>(gameAddress + 0x6E9ED1);
}

static bool LoadLuna() {
    char lunaPath[512];
    snprintf(lunaPath, 512, "%s/Luna/Luna.so", GetHomeDir());

    spdlog::info("Loading Luna...");
    spdlog::info("  Path: {}", lunaPath);

    libLunaHandle = dlopen(lunaPath, RTLD_GLOBAL | RTLD_LAZY);

    if (libLunaHandle == nullptr) {
        spdlog::error("Library not found!");
        return false;
    }

    void* initializeLuna = dlsym(libLunaHandle, "LunaInitialize");

    if (initializeLuna == nullptr)
        return false;

    reinterpret_cast<void (*)(void*)>(initializeLuna)(libGTASAHandle);

    return true;
}

static void PreInitialize() {
    auto logger = spdlog::android_logger_mt("luna", "luna");
    logger->set_level(spdlog::level::debug);

    spdlog::set_default_logger(logger);

    spdlog::info("The Luna loader was injected!");
}

static void NvUtilInit() {
    reinterpret_cast<void (*)()>(gameAddress + 0x27911D)();
    LoadLuna();
}

static void Initialize() {
    libGTASAHandle = dlopen("libGTASA.so", RTLD_NOLOAD);

    if (libGTASAHandle == nullptr)
        spdlog::error("'libGTASA.so' not found!");

    // Calculate the game address.
    gameAddress
        = reinterpret_cast<uint8_t*>(dlsym(libGTASAHandle, "RwEngineInstance"))
        - 0x6CCD38;

    // Remove write protection.

    // .data
    ModifyMemoryProtection(gameAddress + 0x67A000, 0x6B2D84 - 0x67A000, PROTECTION_READ | PROTECTION_WRITE);

    // .got
    ModifyMemoryProtection(gameAddress + 0x66E4D0, 0x679FF3 - 0x66E4D0, PROTECTION_READ | PROTECTION_WRITE);

    // .bss
    ModifyMemoryProtection(gameAddress + 0x6B2DC0, 0xA98FEF - 0x6B2DC0, PROTECTION_READ | PROTECTION_WRITE);

    // .text
    ModifyMemoryProtection(gameAddress + 0x1A1780, 0x5E84E7 - 0x1A1780, PROTECTION_READ | PROTECTION_WRITE | PROTECTION_EXEC);

    *reinterpret_cast<void**>(gameAddress + 0x67E860) = reinterpret_cast<void*>(NvUtilInit);
}

extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    PreInitialize();
    Initialize();

    return JNI_VERSION_1_4;
}

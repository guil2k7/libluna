// All credits to aap - https://github.com/aap/librw.

#include <Luna/Game/imgui_impl_rw.hh>
#include <Luna/Game/RW.hh>

using namespace Luna::Game;

struct BackendData {
    RwTexture* FontTexture;
    RwIm2DVertex* VertexBuf;
    size_t VertexBufSize;

    BackendData() {
        FontTexture = nullptr;
        VertexBuf = nullptr;
        VertexBufSize = 0;
    }

    ~BackendData() {
        if (FontTexture != nullptr)
            RwTextureDestroy(FontTexture);

        if (VertexBufSize > 0)
            delete[] VertexBuf;
    }

    void reserveVertices(size_t newSize) {
        if (VertexBufSize >= newSize)
            return;

        if (VertexBufSize > 0)
            delete[] VertexBuf;

        VertexBuf = new RwIm2DVertex[newSize];
        VertexBufSize = newSize;
    }
};

static inline BackendData* GetBackendData() {
    return reinterpret_cast<BackendData*>(
        ImGui::GetIO().BackendPlatformUserData);
}

bool ImGui_ImplRW_Init() {
    ImGuiIO& io = ImGui::GetIO();
    IM_ASSERT(io.BackendPlatformUserData == nullptr && "Already initialized a renderer backend!");

    BackendData* bd = new BackendData;
    io.BackendPlatformUserData = bd;
    io.BackendPlatformName = "imgui_impl_rw";

    return true;
}

void ImGui_ImplRW_Shutdown() {
    BackendData* bd = GetBackendData();
    IM_ASSERT(bd != nullptr && "No renderer backend to shutdown, or already shutdown?");

    ImGuiIO& io = ImGui::GetIO();

    delete bd;

    io.BackendPlatformUserData = nullptr;
    io.BackendPlatformName = nullptr;
}

static bool ImGui_ImplRW_CreateFontsTexture() {
    ImGuiIO& io = ImGui::GetIO();
    BackendData* bd = GetBackendData();

    // Build texture atlas
    uint8_t* pixels;
    int width, height, depth, format;

    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    RwImage* image = RwImageCreate(width, height, 32);
    RwImageAllocatePixels(image);

    for (int y = 0; y < height; ++y) {
        memcpy(
            image->cpPixels + image->stride * y,
            pixels + width * 4 * y,
            width * 4
        );
    }

    RwImageFindRasterFormat(image, rwRASTERTYPETEXTURE, &width, &height, &depth, &format);

    RwRaster* raster = RwRasterCreate(width, height, depth, format);
    raster = RwRasterSetFromImage(raster, image);

    RwTexture* texture = RwTextureCreate(raster);
    RwTextureSetFilterMode(texture, rwFILTERLINEAR);

    RwImageDestroy(image);

    bd->FontTexture = texture;

    // Store our identifier
    io.Fonts->SetTexID((ImTextureID)bd->FontTexture);

    return true;
}

static bool ImGui_ImplRW_CreateDeviceObjects() {
    return ImGui_ImplRW_CreateFontsTexture();
}

void ImGui_ImplRW_NewFrame() {
    ImGuiIO& io = ImGui::GetIO();
    BackendData* bd = GetBackendData();
    IM_ASSERT(bd != nullptr && "Did you call ImGui_ImplRW_Init()?");

    if (!bd->FontTexture)
        ImGui_ImplRW_CreateDeviceObjects();

    io.DisplaySize = ImVec2(RsGlobal->maximumWidth, RsGlobal->maximumHeight);

    // if (io.WantTextInput && !IsKeyboardShown())
    //     ShowKeyboard();
    // else if (!io.WantTextInput && IsKeyboardShown())
    //     HideKeyboard();
}

void ImGui_ImplRW_RenderDrawData(ImDrawData* drawData) {
    ImGuiIO& io = ImGui::GetIO();
    BackendData* bd = GetBackendData();

    bd->reserveVertices(drawData->TotalVtxCount + 5000);

    RwCamera* camera = RWSRCGLOBAL(curCamera);
    RwIm2DVertex* vtxDst = bd->VertexBuf;

    float recipZ = 1.0F / camera->nearPlane;
    float nearZ = RWSRCGLOBAL(dOpenDevice).zBufferNear;

    for (int n = 0; n < drawData->CmdListsCount; ++n) {
        const ImDrawList* cmdList = drawData->CmdLists[n];
        const ImDrawVert* vtxSrc = cmdList->VtxBuffer.Data;

        for (int i = 0; i < cmdList->VtxBuffer.Size; ++i) {
            vtxDst[i].x = vtxSrc[i].pos.x;
            vtxDst[i].y = vtxSrc[i].pos.y;
            vtxDst[i].z = nearZ;
            vtxDst[i].rhw = camera->nearPlane;
            vtxDst[i].emissiveColor = vtxSrc[i].col;
            vtxDst[i].u = vtxSrc[i].uv.x;
            vtxDst[i].v = vtxSrc[i].uv.y;
        }

        vtxDst += cmdList->VtxBuffer.Size;
    }

    int vertexAlpha; RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &vertexAlpha);
    int srcBlend; RwRenderStateGet(rwRENDERSTATESRCBLEND, &srcBlend);
    int dstBlend; RwRenderStateGet(rwRENDERSTATEDESTBLEND, &dstBlend);
    int ztest; RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &ztest);
    void* tex; RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &tex);
    int addrU; RwRenderStateGet(rwRENDERSTATETEXTUREADDRESSU, &addrU);
    int addrV; RwRenderStateGet(rwRENDERSTATETEXTUREADDRESSV, &addrV);
    int filter; RwRenderStateGet(rwRENDERSTATETEXTUREFILTER, &filter);
    int cullmode; RwRenderStateGet(rwRENDERSTATECULLMODE, &cullmode);

    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)1);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)0);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLNONE);

    int vtxOffset = 0;

    for (int n = 0; n < drawData->CmdListsCount; ++n) {
        const ImDrawList* cmdList = drawData->CmdLists[n];
        int idxOffset = 0;

        for (int i = 0; i < cmdList->CmdBuffer.Size; ++i) {
            const ImDrawCmd* pcmd = &cmdList->CmdBuffer[i];

            if (pcmd->UserCallback) {
                pcmd->UserCallback(cmdList, pcmd);
            }
            else {
                RwTexture* tex = (RwTexture*)pcmd->TextureId;

                if(tex && tex->raster) {
                    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, tex->raster);
                    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESSU, (void*)((tex->filterAddressing >> 8) & 0xF));
                    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESSV, (void*)((tex->filterAddressing >> 12) & 0xF));
                    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)(tex->filterAddressing & 0xFF));
                }
                else {
                    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
                }

                RwIm2DRenderIndexedPrimitive(
                    rwPRIMTYPETRILIST,
                    &bd->VertexBuf[vtxOffset], cmdList->VtxBuffer.Size,
                    &cmdList->IdxBuffer.Data[idxOffset], pcmd->ElemCount
                );
            }

            idxOffset += pcmd->ElemCount;
        }

        vtxOffset += cmdList->VtxBuffer.Size;
    }

    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)vertexAlpha);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)srcBlend);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)dstBlend);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)ztest);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)tex);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESSU, (void*)addrU);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESSV, (void*)addrV);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)filter);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)cullmode);
}

void ImGui_ImplRW_ProcessTouchEvent(Luna::Game::eTouchAction action, int x, int y) {
    ImGuiIO& io = ImGui::GetIO();

    switch(action) {
    case TOUCH_ACTION_RELEASE:
        io.MouseDown[0] = false;
        break;

    case TOUCH_ACTION_PRESS:
        io.MousePos = ImVec2(x, y);
        io.MouseDown[0] = true;
        break;

    case TOUCH_ACTION_MOVE:
        io.MousePos = ImVec2(x, y);
        break;
    }
}

static ImGuiKey OSKeyToImGui(int key) {
    static ImGuiKey map[100] = {
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_GraveAccent,
        ImGuiKey_0,
        ImGuiKey_1,
        ImGuiKey_2,
        ImGuiKey_3,
        ImGuiKey_4,
        ImGuiKey_5,
        ImGuiKey_6,
        ImGuiKey_7,
        ImGuiKey_8,
        ImGuiKey_9,
        ImGuiKey_Minus,
        ImGuiKey_Equal,
        ImGuiKey_None,
        ImGuiKey_Tab,
        ImGuiKey_Q,
        ImGuiKey_W,
        ImGuiKey_E,
        ImGuiKey_R,
        ImGuiKey_T,
        ImGuiKey_Y,
        ImGuiKey_U,
        ImGuiKey_I,
        ImGuiKey_O,
        ImGuiKey_P,
        ImGuiKey_LeftBracket,
        ImGuiKey_RightBracket,
        ImGuiKey_Backslash,
        ImGuiKey_None,
        ImGuiKey_A,
        ImGuiKey_S,
        ImGuiKey_D,
        ImGuiKey_F,
        ImGuiKey_G,
        ImGuiKey_H,
        ImGuiKey_J,
        ImGuiKey_K,
        ImGuiKey_L,
        ImGuiKey_Comma,
        ImGuiKey_Backslash,
        ImGuiKey_None, // \r
        ImGuiKey_None,
        ImGuiKey_Z,
        ImGuiKey_X,
        ImGuiKey_C,
        ImGuiKey_V,
        ImGuiKey_B,
        ImGuiKey_N,
        ImGuiKey_M,
        ImGuiKey_Comma,
        ImGuiKey_Period,
        ImGuiKey_Backslash,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_Space,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_None,
        ImGuiKey_KeypadDivide,
        ImGuiKey_KeypadMultiply,
        ImGuiKey_KeypadSubtract,
        ImGuiKey_Keypad7,
        ImGuiKey_Keypad8,
        ImGuiKey_Keypad9,
        ImGuiKey_KeypadAdd,
        ImGuiKey_Keypad4,
        ImGuiKey_Keypad5,
        ImGuiKey_Keypad6,
        ImGuiKey_Keypad1,
        ImGuiKey_Keypad2,
        ImGuiKey_Keypad3,
        ImGuiKey_Keypad0,
        ImGuiKey_KeypadDecimal,
        ImGuiKey_None, // @
    };

    return map[key];
}

void ImGui_ImplRW_ProcessKeyboardEvent(int key, bool shift, bool down) {
    ImGuiIO& io = ImGui::GetIO();

    if (shift)
        io.AddKeyEvent(ImGuiMod_Shift, down);

    io.AddKeyEvent(OSKeyToImGui(key), down);
}

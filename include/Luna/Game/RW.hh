/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

// TODO: Add OpenGL functions.

#include "RW/rwcore.h"
#include "RW/rphanim.h"
#include "RW/rpuvanim.h"
#include "RW/rpskin.h"
#include "RW/rpmatfx.h"
#include "RW/skeleton.h"

namespace Luna::Game {
    class CRenderWare {
    public:
        static void InitialiseLuna();
    };
}

extern RwGlobals **RwEngineInstance;

/* macro used to access global data structure (the root type is RwGlobals) */
#define RWSRCGLOBAL(variable) ((*RwEngineInstance)->variable)

extern RsGlobalType *RsGlobal;

/* rwplcore.h */


extern RwMemoryFunctions* (*RwOsGetMemoryInterface)(void);
// extern RwFreeList* (*_rwFreeListCreate)(RwInt32 entrySize, RwInt32 entriesPerBlock, RwInt32 alignment, RwUInt32 hint, const RwChar* fileCreate, RwUInt32 lineCreate);
extern RwFreeList* (*RwFreeListCreateAndPreallocateSpace)(RwInt32 entrySize, RwInt32 entriesPerBlock, RwInt32 alignment, RwInt32 numBlocksToPreallocate, RwFreeList* inPlaceSpaceForFreeListStruct, RwUInt32 hint);
extern RwBool (*RwFreeListDestroy)(RwFreeList* freelist);
extern void (*RwFreeListSetFlags)(RwFreeList* freeList, RwUInt32 flags);
extern RwUInt32 (*RwFreeListGetFlags)(RwFreeList* freeList);
extern RwInt32 (*RwFreeListPurge)(RwFreeList* freelist);
extern RwFreeList* (*RwFreeListForAllUsed)(RwFreeList* freelist, RwFreeListCallBack fpCallBack, void* pData);
extern RwInt32 (*RwFreeListPurgeAllFreeLists)(void);
extern void (*RwStreamSetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RwStream* (*_rwStreamInitialize)(RwStream* stream, RwBool rwOwned, RwStreamType type, RwStreamAccessType accessType, const void* pData);
extern RwStream* (*RwStreamOpen)(RwStreamType type, RwStreamAccessType accessType, const void* pData);
extern RwBool (*RwStreamClose)(RwStream* stream, void* pData);
extern RwUInt32 (*RwStreamRead)(RwStream* stream, void* buffer, RwUInt32 length);
extern RwStream* (*RwStreamWrite)(RwStream* stream, const void* buffer, RwUInt32 length);
extern RwStream* (*RwStreamSkip)(RwStream* stream, RwUInt32 offset);
extern RwBool (*_rwStringOpen)(void);
extern void (*_rwStringClose)(void);
extern RwBool (*_rwStringDestroy)(RwChar* string);
extern RwUInt32 (*_rwStringStreamGetSize)(const RwChar* string);
extern const RwChar* (*_rwStringStreamWrite)(const RwChar* string, RwStream* stream);
extern RwChar* (*_rwStringStreamFindAndRead)(RwChar* string, RwStream* stream);
extern void (*RwPluginRegistrySetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RwBool (*_rwPluginRegistrySetStaticPluginsSize)(RwPluginRegistry* reg, RwInt32 size);
extern RwInt32 (*_rwPluginRegistryAddPlugin)(RwPluginRegistry* reg, RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
extern RwInt32 (*_rwPluginRegistryGetPluginOffset)(const RwPluginRegistry* reg, RwUInt32 pluginID);
extern const RwPluginRegistry* (*_rwPluginRegistryInitObject)(const RwPluginRegistry* reg, void* object);
extern const RwPluginRegistry* (*_rwPluginRegistryDeInitObject)(const RwPluginRegistry* reg, void* object);
extern const RwPluginRegistry* (*_rwPluginRegistryCopyObject)(const RwPluginRegistry* reg, void* dstObject, const void* srcObject);
extern RwInt32 (*_rwPluginRegistryAddPluginStream)(RwPluginRegistry* reg, RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 (*_rwPluginRegistryAddPlgnStrmlwysCB)(RwPluginRegistry* reg, RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwInt32 (*_rwPluginRegistryAddPlgnStrmRightsCB)(RwPluginRegistry* reg, RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB);
extern const RwPluginRegistry* (*_rwPluginRegistryReadDataChunks)(const RwPluginRegistry* reg, RwStream* stream, void* object);
extern const RwPluginRegistry* (*_rwPluginRegistryWriteDataChunks)(const RwPluginRegistry* reg, RwStream* stream, const void* object);
extern const RwPluginRegistry* (*_rwPluginRegistrySkipDataChunks)(const RwPluginRegistry* reg, RwStream* stream);
extern RwInt32 (*_rwPluginRegistryGetSize)(const RwPluginRegistry* reg, const void* object);
extern const RwPluginRegistry* (*_rwPluginRegistryInvokeRights)(const RwPluginRegistry* reg, RwUInt32 id, void* obj, RwUInt32 extraData);
extern RwBool (*RwEngineGetMatrixTolerances)(RwMatrixTolerance * const tolerance);
extern RwBool (*RwEngineSetMatrixTolerances)(const RwMatrixTolerance * const tolerance);
extern void (*RwMatrixSetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RwBool (*RwMatrixDestroy)(RwMatrix* mpMat);
extern RwMatrix* (*RwMatrixCreate)(void);
extern RwMatrix* (*RwMatrixMultiply)(RwMatrix* matrixOut, const RwMatrix* MatrixIn1, const RwMatrix* matrixIn2);
extern RwMatrix* (*RwMatrixTransform)(RwMatrix* matrix, const RwMatrix* transform, RwOpCombineType combineOp);
extern RwMatrix* (*RwMatrixOrthoNormalize)(RwMatrix* matrixOut, const RwMatrix* matrixIn);
extern RwMatrix* (*RwMatrixInvert)(RwMatrix* matrixOut, const RwMatrix* matrixIn);
extern RwMatrix* (*RwMatrixScale)(RwMatrix* matrix, const RwV3d* scale, RwOpCombineType combineOp);
extern RwMatrix* (*RwMatrixTranslate)(RwMatrix* matrix, const RwV3d* translation, RwOpCombineType combineOp);
extern RwMatrix* (*RwMatrixRotate)(RwMatrix* matrix, const RwV3d* axis, RwReal angle, RwOpCombineType combineOp);
extern RwMatrix* (*RwMatrixRotateOneMinusCosineSine)(RwMatrix* matrix, const RwV3d* unitAxis, RwReal oneMinusCosine, RwReal sine, RwOpCombineType combineOp);
extern const RwMatrix* (*RwMatrixQueryRotate)(const RwMatrix* matrix, RwV3d* unitAxis, RwReal* angle, RwV3d* center);
extern RwMatrix* (*RwMatrixUpdate)(RwMatrix* matrix);
extern RwMatrix* (*RwMatrixOptimize)(RwMatrix* matrix, const RwMatrixTolerance* tolerance);
extern RwReal (*_rwMatrixDeterminant)(const RwMatrix* matrix);
extern RwReal (*_rwMatrixNormalError)(const RwMatrix* matrix);
extern RwReal (*_rwMatrixOrthogonalError)(const RwMatrix* matrix);
extern RwReal (*_rwMatrixIdentityError)(const RwMatrix* matrix);
extern RwReal (*RwV3dNormalize)(RwV3d* out, const RwV3d* in);
extern RwReal (*RwV3dLength)(const RwV3d* in);
extern RwReal (*RwV2dLength)(const RwV2d* in);
extern RwReal (*RwV2dNormalize)(RwV2d* out, const RwV2d* in);
extern RwV3d* (*RwV3dTransformPoint)(RwV3d* pointOut, const RwV3d* pointIn, const RwMatrix* matrix);
extern RwV3d* (*RwV3dTransformPoints)(RwV3d* pointsOut, const RwV3d* pointsIn, RwInt32 numPoints, const RwMatrix* matrix);
extern RwV3d* (*RwV3dTransformVector)(RwV3d* vectorOut, const RwV3d* vectorIn, const RwMatrix* matrix);
extern RwV3d* (*RwV3dTransformVectors)(RwV3d* vectorsOut, const RwV3d* vectorsIn, RwInt32 numPoints, const RwMatrix* matrix);
extern RwReal (*_rwSqrt)(const RwReal num);
extern RwReal (*_rwInvSqrt)(const RwReal num);
extern RwReal (*_rwV3dNormalize)(RwV3d* out, const RwV3d* in);
extern RwSList* (*_rwSListCreate)(RwInt32 size, RwUInt32 hint);
extern RwBool (*_rwSListDestroy)(RwSList* sList);
extern void (*_rwSListDestroyEndEntries)(RwSList* sList, RwInt32 amount);
extern void* (*_rwSListGetEntry)(RwSList* sList, RwInt32 entry);
extern void* (*_rwSListGetNewEntry)(RwSList* sList, RwUInt32 hint);
extern RwInt32 (*_rwSListGetNumEntries)(const RwSList* sList);
extern void* (*_rwSListGetBegin)(RwSList* sList);
extern void* (*_rwSListGetEnd)(RwSList* sList);
extern RwBool (*RwIm2DRenderPrimitive)(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices);
extern RwBool (*RwIm2DRenderIndexedPrimitive)(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices, RwImVertexIndex* indices, RwInt32 numIndices);
extern RwBool (*RwIm2DRenderTriangle)(RwIm2DVertex* vertices, RwInt32 numVertices, RwInt32 vert1, RwInt32 vert2, RwInt32 vert3);
extern RwBool (*RwIm2DRenderLine)(RwIm2DVertex* vertices, RwInt32 numVertices, RwInt32 vert1, RwInt32 vert2);
extern RwUInt32 (*RwEngineGetVersion)(void);
extern RwBool (*RwEngineInit)(const RwMemoryFunctions* memFuncs, RwUInt32 initFlags, RwUInt32 resArenaSize);
extern RwInt32 (*RwEngineRegisterPlugin)(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor initCB, RwPluginObjectDestructor termCB);
extern RwInt32 (*RwEngineGetPluginOffset)(RwUInt32 pluginID);
extern RwBool (*RwEngineOpen)(RwEngineOpenParams* initParams);
extern RwBool (*RwEngineStart)(void);
extern RwBool (*RwEngineStop)(void);
extern RwBool (*RwEngineClose)(void);
extern RwBool (*RwEngineTerm)(void);
extern RwInt32 (*RwEngineGetNumSubSystems)(void);
extern RwSubSystemInfo* (*RwEngineGetSubSystemInfo)(RwSubSystemInfo* subSystemInfo, RwInt32 subSystemIndex);
extern RwInt32 (*RwEngineGetCurrentSubSystem)(void);
extern RwBool (*RwEngineSetSubSystem)(RwInt32 subSystemIndex);
extern RwInt32 (*RwEngineGetNumVideoModes)(void);
extern RwVideoMode* (*RwEngineGetVideoModeInfo)(RwVideoMode* modeinfo, RwInt32 modeIndex);
extern RwInt32 (*RwEngineGetCurrentVideoMode)(void);
extern RwBool (*RwEngineSetVideoMode)(RwInt32 modeIndex);
extern RwInt32 (*RwEngineGetTextureMemorySize)(void);
extern RwInt32 (*RwEngineGetMaxTextureSize)(void);
extern RwBool (*RwEngineSetFocus)(RwBool enable);
extern RwMetrics* (*RwEngineGetMetrics)(void);
extern RwFileFunctions* (*RwOsGetFileInterface)(void);
extern RwError* (*RwErrorGet)(RwError* code);
extern RwError* (*RwErrorSet)(RwError* code);
extern RwInt32 (*_rwerror)(RwInt32 code, ...);
extern RwBool (*RwResourcesSetArenaSize)(RwUInt32 size);
extern RwInt32 (*RwResourcesGetArenaSize)(void);
extern RwInt32 (*RwResourcesGetArenaUsage)(void);
extern RwBool (*RwResourcesEmptyArena)(void);
extern RwResEntry* (*RwResourcesAllocateResEntry)(void* owner, RwResEntry* ownerRef, RwInt32 size, RwResEntryDestroyNotify destroyNotify);
extern RwBool (*RwResourcesFreeResEntry)(RwResEntry* entry);
extern void (*_rwResourcesPurge)(void);
extern RwBool (*RwStreamFindChunk)(RwStream* stream, RwUInt32 type, RwUInt32* lengthOut, RwUInt32* versionOut);
extern RwStream* (*_rwStreamWriteVersionedChunkHeader)(RwStream* stream, RwInt32 type, RwInt32 size, RwUInt32 version, RwUInt32 buildNum);
extern RwStream* (*RwStreamWriteReal)(RwStream* stream, const RwReal* reals, RwUInt32 numBytes);
extern RwStream* (*RwStreamWriteInt32)(RwStream* stream, const RwInt32* ints, RwUInt32 numBytes);
extern RwStream* (*RwStreamWriteInt16)(RwStream* stream, const RwInt16* ints, RwUInt32 numBytes);
extern RwStream* (*RwStreamReadReal)(RwStream* stream, RwReal* reals, RwUInt32 numBytes);
extern RwStream* (*RwStreamReadInt32)(RwStream* stream, RwInt32* ints, RwUInt32 numBytes);
extern RwStream* (*RwStreamReadInt16)(RwStream* stream, RwInt16* ints, RwUInt32 numBytes);
extern RwStream* (*RwStreamReadChunkHeaderInfo)(RwStream* stream, RwChunkHeaderInfo* chunkHeaderInfo);

/* rwcore.h */

extern RxHeap* (*RxHeapCreate)(RwUInt32 size);
extern void (*RxHeapDestroy)(RxHeap* heap);
extern RwBool (*_rxHeapReset)(RxHeap* heap);
extern void* (*RxHeapAlloc)(RxHeap* heap, RwUInt32 size);
extern void (*RxHeapFree)(RxHeap* heap, void* block);
extern void* (*RxHeapRealloc)(RxHeap* heap, void* block, RwUInt32 newSize, RwBool allowCopy);
extern void (*RxPipelineSetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RwBool (*_rxPipelineOpen)(void);
extern RwBool (*_rxPipelineClose)(void);
extern RxPipeline* (*RxPipelineCreate)(void);
extern void (*_rxPipelineDestroy)(RxPipeline* Pipeline);
extern RxHeap* (*RxHeapGetGlobalHeap)(void);
extern RxPipeline* (*RxPipelineExecute)(RxPipeline* pipeline, void* data, RwBool heapReset);
extern RxPacket* (*RxPacketCreate)(RxPipelineNode* node);
extern RxCluster* (*RxClusterSetStride)(RxCluster* cluster, RwInt32 stride);
extern RxCluster* (*RxClusterSetExternalData)(RxCluster* cluster, void* data, RwInt32 stride, RwInt32 numElements);
extern RxCluster* (*RxClusterSetData)(RxCluster* cluster, void* data, RwInt32 stride, RwInt32 numElements);
extern void (*_rxPacketDestroy)(RxPacket* Packet);
extern RxCluster* (*RxClusterInitializeData)(RxCluster* cluster, RwUInt32 numElements, RwUInt16 stride);
extern RxCluster* (*RxClusterResizeData)(RxCluster* CurrentCluster, RwUInt32 NumElements);
extern RxCluster* (*RxClusterDestroyData)(RxCluster* CurrentCluster);
extern RxCluster* (*RxClusterLockWrite)(RxPacket* packet, RwUInt32 clusterIndex, RxPipelineNode* node);
extern void (*RxClusterUnlock)(RxCluster* cluster);
extern RwUInt32 (*RxPipelineNodeSendConfigMsg)(RxPipelineNode* dest, RwUInt32 msg, RwUInt32 intparam, void* ptrparam);
extern RxPipelineNode* (*RxPipelineNodeForAllConnectedOutputs)(RxPipelineNode* node, RxPipeline* pipeline, RxPipelineNodeOutputCallBack callbackfn, void* callbackdata);
extern RxPipelineCluster* (*RxPipelineNodeGetPipelineCluster)(RxPipelineNode* node, RwUInt32 clustersOfInterestIndex);
extern RwUInt32 (*RxPipelineClusterGetCreationAttributes)(RxPipelineCluster* cluster);
extern RxPipelineCluster* (*RxPipelineClusterSetCreationAttributes)(RxPipelineCluster* cluster, RwUInt32 creationAttributes);
extern RwUInt32 (*RxClusterGetAttributes)(RxCluster* cluster);
extern RxCluster* (*RxClusterSetAttributes)(RxCluster* cluster, RwUInt32 attributes);
extern RxNodeOutput (*RxPipelineNodeFindOutputByName)(RxPipelineNode* node, const RwChar* outputname);
extern RxNodeOutput (*RxPipelineNodeFindOutputByIndex)(RxPipelineNode* node, RwUInt32 outputindex);
extern RxNodeInput (*RxPipelineNodeFindInput)(RxPipelineNode* node);
extern RxNodeDefinition* (*RxPipelineNodeCloneDefinition)(RxPipelineNode* node, RxClusterDefinition* cluster2add);
extern RxPipeline* (*RxPipelineNodeRequestCluster)(RxPipeline* pipeline, RxPipelineNode* node, RxClusterDefinition* clusterDef);
extern RxPipeline* (*RxPipelineNodeReplaceCluster)(RxPipeline* pipeline, RxPipelineNode* node, RxClusterDefinition* oldClusterDef, RxClusterDefinition* newClusterDef);
extern void* (*RxPipelineNodeGetInitData)(RxPipelineNode* node);
extern void* (*RxPipelineNodeCreateInitData)(RxPipelineNode* node, RwUInt32 size);
extern RxPipeline* (*RxPipelineClone)(RxPipeline* pipeline);
extern RxPipelineNode* (*RxPipelineFindNodeByName)(RxPipeline* pipeline, const RwChar* name, RxPipelineNode* start, RwInt32* nodeIndex);
extern RxPipelineNode* (*RxPipelineFindNodeByIndex)(RxPipeline* pipeline, RwUInt32 nodeindex);
extern RxLockedPipe* (*RxPipelineLock)(RxPipeline* pipeline);
extern RxPipeline* (*RxLockedPipeUnlock)(RxLockedPipe* pipeline);
extern RxPipeline* (*RxLockedPipeReplaceNode)(RxLockedPipe* pipeline, RxPipelineNode* node, RxNodeDefinition* nodeDef);
extern RxPipeline* (*RxLockedPipeDeleteNode)(RxLockedPipe* pipeline, RxPipelineNode* node);
extern RxPipeline* (*RxLockedPipeSetEntryPoint)(RxLockedPipe* pipeline, RxNodeInput in);
extern RxPipelineNode* (*RxLockedPipeGetEntryPoint)(RxLockedPipe* pipeline);
extern RxPipeline* (*RxLockedPipeAddPath)(RxLockedPipe* pipeline, RxNodeOutput out, RxNodeInput in);
extern RxPipeline* (*RxLockedPipeDeletePath)(RxLockedPipe* pipeline, RxNodeOutput out, RxNodeInput in);
extern RxPipeline* (*RxPipelineInsertDebugNode)(RxPipeline* pipeline, RxPipelineNode* before, RxPipelineNode* after, RxNodeDefinition* debugNode);
extern void (*RwRasterSetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RwRaster* (*RwRasterCreate)(RwInt32 width, RwInt32 height, RwInt32 depth, RwInt32 flags);
extern RwBool (*RwRasterDestroy)(RwRaster* raster);
extern RwRaster* (*RwRasterGetOffset)(RwRaster* raster, RwInt16* xOffset, RwInt16* yOffset);
extern RwInt32 (*RwRasterGetNumLevels)(RwRaster* raster);
extern RwRaster* (*RwRasterSubRaster)(RwRaster* subRaster, RwRaster* raster, RwRect* rect);
extern RwRaster* (*RwRasterRenderFast)(RwRaster* raster, RwInt32 x, RwInt32 y);
extern RwRaster* (*RwRasterRender)(RwRaster* raster, RwInt32 x, RwInt32 y);
extern RwRaster* (*RwRasterRenderScaled)(RwRaster* raster, RwRect* rect);
extern RwRaster* (*RwRasterPushContext)(RwRaster* raster);
extern RwRaster* (*RwRasterPopContext)(void);
extern RwRaster* (*RwRasterGetCurrentContext)(void);
extern RwBool (*RwRasterClear)(RwInt32 pixelValue);
extern RwBool (*RwRasterClearRect)(RwRect* rpRect, RwInt32 pixelValue);
extern RwRaster* (*RwRasterShowRaster)(RwRaster* raster, void* dev, RwUInt32 flags);
extern RwUInt8* (*RwRasterLock)(RwRaster* raster, RwUInt8 level, RwInt32 lockMode);
extern RwRaster* (*RwRasterUnlock)(RwRaster* raster);
extern RwUInt8* (*RwRasterLockPalette)(RwRaster* raster, RwInt32 lockMode);
extern RwRaster* (*RwRasterUnlockPalette)(RwRaster* raster);
extern RwInt32 (*RwRasterRegisterPlugin)(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
extern RwInt32 (*RwRasterGetPluginOffset)(RwUInt32 pluginID);
extern RxRenderStateVector* (*RxRenderStateVectorSetDefaultRenderStateVector)(RxRenderStateVector* rsvp);
extern RwImage* (*RwImageCreate)(RwInt32 width, RwInt32 height, RwInt32 depth);
extern RwBool (*RwImageDestroy)(RwImage* image);
extern RwImage* (*RwImageAllocatePixels)(RwImage* image);
extern RwImage* (*RwImageFreePixels)(RwImage* image);
extern RwImage* (*RwImageApplyMask)(RwImage* image, const RwImage* mask);
extern RwImage* (*RwImageMakeMask)(RwImage* image);
extern RwImage* (*RwImageReadMaskedImage)(const RwChar* imageName, const RwChar* maskname);
extern RwImage* (*RwImageRead)(const RwChar* imageName);
extern const RwChar* (*RwImageSetPath)(const RwChar* path);
extern RwBool (*RwImageSetGamma)(RwReal gammaValue);
extern RwImage* (*RwImageGammaCorrect)(RwImage* image);
// extern RwBool (*RwPalQuantInit)(RwPalQuant* pq);
// extern void (*RwPalQuantTerm)(RwPalQuant* pq);
// extern void (*RwPalQuantAddImage)(RwPalQuant* pq, RwImage* img, RwReal weight);
// extern RwInt32 (*RwPalQuantResolvePalette)(RwRGBA* palette, RwInt32 maxcols, RwPalQuant* pq);
// extern void (*RwPalQuantMatchImage)(RwUInt8* dstpixels, RwInt32 dststride, RwInt32 dstdepth, RwBool dstPacked, RwPalQuant* pq, RwImage* img);
extern RwBool (*RwTextureSetMipmapping)(RwBool enable);
extern RwBool (*RwTextureGetMipmapping)(void);
extern RwBool (*RwTextureSetAutoMipmapping)(RwBool enable);
extern RwBool (*RwTextureGetAutoMipmapping)(void);
extern RwBool (*RwTextureSetMipmapGenerationCallBack)(RwTextureCallBackMipmapGeneration callback);
extern RwTextureCallBackMipmapGeneration (*RwTextureGetMipmapGenerationCallBack)(void);
extern RwBool (*RwTextureSetMipmapNameCallBack)(RwTextureCallBackMipmapName callback);
extern RwTextureCallBackMipmapName (*RwTextureGetMipmapNameCallBack)(void);
extern RwBool (*RwTextureGenerateMipmapName)(RwChar* name, RwChar* maskName, RwUInt8 mipLevel, RwInt32 format);
extern RwBool (*RwTextureRasterGenerateMipmaps)(RwRaster* raster, RwImage* image);
extern RwBool (*_rwTextureSetAutoMipMapState)(RwBool enable);
extern RwBool (*_rwTextureGetAutoMipMapState)(void);
extern RwTextureCallBackRead (*RwTextureGetReadCallBack)(void);
extern RwBool (*RwTextureSetReadCallBack)(RwTextureCallBackRead callBack);
extern RwTextureCallBackFind (*RwTextureGetFindCallBack)(void);
extern RwBool (*RwTextureSetFindCallBack)(RwTextureCallBackFind callBack);
extern RwTexture* (*RwTextureSetName)(RwTexture* texture, const RwChar* name);
extern RwTexture* (*RwTextureSetMaskName)(RwTexture* texture, const RwChar* maskName);
extern void (*RwTexDictionarySetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RwTexDictionary* (*RwTexDictionaryCreate)(void);
extern RwBool (*RwTexDictionaryDestroy)(RwTexDictionary* dict);
extern RwTexture* (*RwTextureCreate)(RwRaster* raster);
extern RwBool (*RwTextureDestroy)(RwTexture* texture);
extern RwTexture* (*RwTextureSetRaster)(RwTexture* texture, RwRaster* raster);
extern RwTexture* (*RwTexDictionaryAddTexture)(RwTexDictionary* dict, RwTexture* texture);
extern RwTexture* (*RwTexDictionaryRemoveTexture)(RwTexture* texture);
extern RwTexture* (*RwTexDictionaryFindNamedTexture)(RwTexDictionary* dict, const RwChar* name);
extern RwTexDictionary* (*RwTexDictionaryGetCurrent)(void);
extern RwTexDictionary* (*RwTexDictionarySetCurrent)(RwTexDictionary* dict);
extern const RwTexDictionary* (*RwTexDictionaryForAllTextures)(const RwTexDictionary* dict, RwTextureCallBack fpCallBack, void* pData);
extern RwBool (*RwTexDictionaryForAllTexDictionaries)(RwTexDictionaryCallBack fpCallBack, void* pData);
extern RwInt32 (*RwTextureRegisterPlugin)(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
extern RwInt32 (*RwTexDictionaryRegisterPlugin)(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
extern RwInt32 (*RwTextureGetPluginOffset)(RwUInt32 pluginID);
extern RwInt32 (*RwTexDictionaryGetPluginOffset)(RwUInt32 pluginID);
extern RwBool (*RwTextureValidatePlugins)(const RwTexture* texture);
extern RwBool (*RwTexDictionaryValidatePlugins)(const RwTexDictionary* dict);
extern rwIm3DPool* (*_rwIm3DGetPool)(void);
extern void* (*RwIm3DTransform)(RwIm3DVertex* pVerts, RwUInt32 numVerts, RwMatrix* ltm, RwUInt32 flags);
extern RwBool (*RwIm3DEnd)(void);
extern RwBool (*RwIm3DRenderLine)(RwInt32 vert1, RwInt32 vert2);
extern RwBool (*RwIm3DRenderTriangle)(RwInt32 vert1, RwInt32 vert2, RwInt32 vert3);
extern RwBool (*RwIm3DRenderIndexedPrimitive)(RwPrimitiveType primType, RwImVertexIndex* indices, RwInt32 numIndices);
extern RwBool (*RwIm3DRenderPrimitive)(RwPrimitiveType primType);
extern RxPipeline* (*RwIm3DGetTransformPipeline)(void);
extern RxPipeline* (*RwIm3DGetRenderPipeline)(RwPrimitiveType primType);
extern RxPipeline* (*RwIm3DSetTransformPipeline)(RxPipeline* pipeline);
extern RxPipeline* (*RwIm3DSetRenderPipeline)(RxPipeline* pipeline, RwPrimitiveType primType);
extern RwBool (*_rwDeviceRegisterPlugin)(void);
extern RwImage* (*RwImageResample)(RwImage* dstImage, const RwImage* srcImage);
extern RwImage* (*RwImageCreateResample)(const RwImage* srcImage, RwInt32 width, RwInt32 height);
extern RwImage* (*RwImageSetFromRaster)(RwImage* image, RwRaster* raster);
extern RwRaster* (*RwRasterSetFromImage)(RwRaster* raster, RwImage* image);
extern RwRaster* (*RwRasterRead)(const RwChar* filename);
extern RwRaster* (*RwRasterReadMaskedRaster)(const RwChar* filename, const RwChar* maskname);
extern RwImage* (*RwImageFindRasterFormat)(RwImage* ipImage, RwInt32 nRasterType, RwInt32* npWidth, RwInt32* npHeight, RwInt32* npDepth, RwInt32* npFormat);
extern RwFrame* (*RwFrameForAllObjects)(RwFrame* frame, RwObjectCallBack callBack, void* data);
extern RwFrame* (*RwFrameTranslate)(RwFrame* frame, const RwV3d* v, RwOpCombineType combine);
extern RwFrame* (*RwFrameRotate)(RwFrame* frame, const RwV3d* axis, RwReal angle, RwOpCombineType combine);
extern RwFrame* (*RwFrameScale)(RwFrame* frame, const RwV3d* v, RwOpCombineType combine);
extern RwFrame* (*RwFrameTransform)(RwFrame* frame, const RwMatrix* m, RwOpCombineType combine);
extern RwFrame* (*RwFrameOrthoNormalize)(RwFrame* frame);
extern RwFrame* (*RwFrameSetIdentity)(RwFrame* frame);
extern RwFrame* (*RwFrameCloneHierarchy)(RwFrame* root);
extern RwBool (*RwFrameDestroyHierarchy)(RwFrame* frame);
extern RwFrame* (*RwFrameForAllChildren)(RwFrame* frame, RwFrameCallBack callBack, void* data);
extern RwFrame* (*RwFrameRemoveChild)(RwFrame* child);
extern RwFrame* (*RwFrameAddChild)(RwFrame* parent, RwFrame* child);
// extern RwFrame* (*RwFrameAddChildNoUpdate)(RwFrame* parent, RwFrame* child);
extern RwFrame* (*RwFrameGetRoot)(const RwFrame* frame);
extern RwMatrix* (*RwFrameGetLTM)(RwFrame* frame);
extern RwFrame* (*RwFrameUpdateObjects)(RwFrame* frame);
extern void (*RwFrameSetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RwFrame* (*RwFrameCreate)(void);
extern RwBool (*RwFrameDestroy)(RwFrame* frame);
extern void (*_rwFrameInit)(RwFrame* frame);
extern void (*_rwFrameDeInit)(RwFrame* frame);
extern RwBool (*RwFrameDirty)(const RwFrame* frame);
extern RwInt32 (*RwFrameCount)(RwFrame* frame);
extern RwInt32 (*RwFrameRegisterPlugin)(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
extern RwInt32 (*RwFrameGetPluginOffset)(RwUInt32 pluginID);
extern RwBool (*RwFrameValidatePlugins)(const RwFrame* frame);
extern RwFrame* (*_rwFrameCloneAndLinkClones)(RwFrame* root);
extern RwFrame* (*_rwFramePurgeClone)(RwFrame* root);
extern RwBool (*_rwFrameSyncDirty)(void);
extern void (*_rwFrameSyncHierarchyLTM)(RwFrame* frame);
extern RwInt32 (*RwTextureRegisterPluginStream)(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 (*RwTextureSetStreamAlwaysCallBack)(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwUInt32 (*RwTextureStreamGetSize)(const RwTexture* texture);
extern RwTexture* (*RwTextureStreamRead)(RwStream* stream);
extern const RwTexture* (*RwTextureStreamWrite)(const RwTexture* texture, RwStream* stream);
extern RwInt32 (*RwTexDictionaryRegisterPluginStream)(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 (*RwTexDictionarySetStreamAlwaysCallBack)(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwUInt32 (*RwTexDictionaryStreamGetSize)(const RwTexDictionary* texDict);
extern RwTexDictionary* (*RwTexDictionaryStreamRead)(RwStream* stream);
extern const RwTexDictionary* (*RwTexDictionaryStreamWrite)(const RwTexDictionary* texDict, RwStream* stream);
extern RwTextureChunkInfo* (*_rwTextureChunkInfoRead)(RwStream* stream, RwTextureChunkInfo* textureChunkInfo, RwInt32* bytesRead);
// extern void (*RwFrameListSetAutoUpdate)(RwBool flag);
extern RwInt32 (*RwFrameRegisterPluginStream)(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 (*RwFrameSetStreamAlwaysCallBack)(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB);
extern rwFrameList* (*_rwFrameListInitialize)(rwFrameList* frameList, RwFrame* frame);
extern RwBool (*_rwFrameListFindFrame)(const rwFrameList* frameList, const RwFrame* frame, RwInt32* npIndex);
extern rwFrameList* (*_rwFrameListDeinitialize)(rwFrameList* frameList);
extern RwUInt32 (*_rwFrameListStreamGetSize)(const rwFrameList* frameList);
extern rwFrameList* (*_rwFrameListStreamRead)(RwStream* stream, rwFrameList* fl);
extern const rwFrameList* (*_rwFrameListStreamWrite)(const rwFrameList* frameList, RwStream* stream);
extern RwBBox* (*RwBBoxCalculate)(RwBBox* boundBox, const RwV3d* verts, RwInt32 numVerts);
extern RwBBox* (*RwBBoxInitialize)(RwBBox* boundBox, const RwV3d* vertex);
extern RwBBox* (*RwBBoxAddPoint)(RwBBox* boundBox, const RwV3d* vertex);
extern RwBool (*RwBBoxContainsPoint)(const RwBBox* boundBox, const RwV3d* vertex);
extern RwCamera* (*RwCameraBeginUpdate)(RwCamera* camera);
extern RwCamera* (*RwCameraEndUpdate)(RwCamera* camera);
extern RwCamera* (*RwCameraClear)(RwCamera* camera, RwRGBA* colour, RwInt32 clearMode);
extern RwCamera* (*RwCameraShowRaster)(RwCamera* camera, void* pDev, RwUInt32 flags);
extern void (*RwCameraSetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RwBool (*RwCameraDestroy)(RwCamera* camera);
extern RwCamera* (*RwCameraCreate)(void);
extern RwCamera* (*RwCameraClone)(RwCamera* camera);
extern RwCamera* (*RwCameraSetViewOffset)(RwCamera* camera, const RwV2d* offset);
extern RwCamera* (*RwCameraSetViewWindow)(RwCamera* camera, const RwV2d* viewWindow);
extern RwCamera* (*RwCameraSetProjection)(RwCamera* camera, RwCameraProjection projection);
extern RwCamera* (*RwCameraSetNearClipPlane)(RwCamera* camera, RwReal nearClip);
extern RwCamera* (*RwCameraSetFarClipPlane)(RwCamera* camera, RwReal farClip);
extern RwInt32 (*RwCameraRegisterPlugin)(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
extern RwInt32 (*RwCameraGetPluginOffset)(RwUInt32 pluginID);
extern RwBool (*RwCameraValidatePlugins)(const RwCamera* camera);
extern RwFrustumTestResult (*RwCameraFrustumTestSphere)(const RwCamera* camera, const RwSphere* sphere);
extern RwInt32 (*RwCameraRegisterPluginStream)(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 (*RwCameraSetStreamAlwaysCallBack)(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwUInt32 (*RwCameraStreamGetSize)(const RwCamera* camera);
extern RwCamera* (*RwCameraStreamRead)(RwStream* stream);
extern const RwCamera* (*RwCameraStreamWrite)(const RwCamera* camera, RwStream* stream);
extern RwCameraChunkInfo* (*RwCameraChunkInfoRead)(RwStream* stream, RwCameraChunkInfo* cameraChunkInfo, RwInt32* bytesRead);

/* rpworld.h */

extern void (*RpMaterialSetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RpMaterial* (*RpMaterialCreate)(void);
extern RwBool (*RpMaterialDestroy)(RpMaterial* material);
extern RpMaterial* (*RpMaterialClone)(RpMaterial* material);
extern RpMaterial* (*RpMaterialSetTexture)(RpMaterial* material, RwTexture* texture);
extern RwInt32 (*RpMaterialRegisterPlugin)(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
extern RwInt32 (*RpMaterialRegisterPluginStream)(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 (*RpMaterialSetStreamAlwaysCallBack)(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwInt32 (*RpMaterialSetStreamRightsCallBack)(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB);
extern RwInt32 (*RpMaterialGetPluginOffset)(RwUInt32 pluginID);
extern RwBool (*RpMaterialValidatePlugins)(const RpMaterial* material);
extern RwUInt32 (*RpMaterialStreamGetSize)(const RpMaterial* material);
extern RpMaterial* (*RpMaterialStreamRead)(RwStream* stream);
extern const RpMaterial* (*RpMaterialStreamWrite)(const RpMaterial* material, RwStream* stream);
extern RpMaterialChunkInfo* (*_rpMaterialChunkInfoRead)(RwStream* stream, RpMaterialChunkInfo* materialChunkInfo, RwInt32* bytesRead);
extern RpMaterialList* (*_rpMaterialListInitialize)(RpMaterialList* matList);
extern RpMaterialList* (*_rpMaterialListDeinitialize)(RpMaterialList* matList);
extern RpMaterial** (*_rpMaterialListAlloc)(RwUInt32 count);
extern RpMaterial* (*_rpMaterialListGetMaterial)(const RpMaterialList* matList, RwInt32 matIndex);
extern RpMaterialList* (*_rpMaterialListSetSize)(RpMaterialList* matList, RwInt32 size);
extern RpMaterialList* (*_rpMaterialListCopy)(RpMaterialList* matListOut, const RpMaterialList* matListIn);
extern RwInt32 (*_rpMaterialListAppendMaterial)(RpMaterialList* matList, RpMaterial* material);
extern RwInt32 (*_rpMaterialListFindMaterialIndex)(const RpMaterialList* matList, const RpMaterial* material);
extern RwUInt32 (*_rpMaterialListStreamGetSize)(const RpMaterialList* matList);
extern RpMaterialList* (*_rpMaterialListStreamRead)(RwStream* stream, RpMaterialList* matList);
extern const RpMaterialList* (*_rpMaterialListStreamWrite)(const RpMaterialList* matList, RwStream* stream);
extern void* (*_rpMeshOpen)(void* instance, RwInt32 offset, RwInt32 size);
extern void* (*_rpMeshClose)(void* instance, RwInt32 offset, RwInt32 size);
extern RwInt16 (*_rpMeshGetNextSerialNumber)(void);
extern RpBuildMesh* (*_rpBuildMeshCreate)(RwUInt32 bufferSize);
extern RwBool (*_rpBuildMeshDestroy)(RpBuildMesh* mesh);
extern RwBool (*_rpMeshDestroy)(RpMeshHeader* mesh);
extern RpBuildMesh* (*_rpBuildMeshAddTriangle)(RpBuildMesh* mesh, RpMaterial* material, RwInt32 vert1, RwInt32 vert2, RwInt32 vert3, RwUInt16 matIndex, RwUInt16 textureIndex, RwUInt16 rasterIndex, RwUInt16 pipelineIndex);
extern RpMeshHeader* (*_rpMeshHeaderForAllMeshes)(RpMeshHeader* meshHeader, RpMeshCallBack fpCallBack, void* pData);
extern RwStream* (*_rpMeshWrite)(const RpMeshHeader* meshHeader, const void* object, RwStream* stream, const RpMaterialList* matList);
extern RpMeshHeader* (*_rpMeshRead)(RwStream* stream, const void* object, const RpMaterialList* matList);
extern RwInt32 (*_rpMeshSize)(const RpMeshHeader* meshHeader, const void* object);
extern void (*_rpMeshHeaderDestroy)(RpMeshHeader* meshHeader);
extern RpMeshHeader* (*_rpMeshHeaderCreate)(RwUInt32 size);
extern RpTriStripPolygon* (*RpTriStripPolygonFollowStrip)(RpTriStripPolygon* curr, RpTriStripPolygon* prev);
extern RwUInt32 (*RpTriStripDefaultCost)(RpTriStripPolygon* startPolygon, RwUInt32 testFrame, void* data);
extern RpTriStripMesh* (*RpTriStripMeshTunnel)(RpTriStripMesh* mesh, void* data);
extern RpTriStripMesh* (*RpTriStripMeshQuick)(RpTriStripMesh* mesh, void* data);
extern RpMeshHeader* (*RpBuildMeshGenerateTriStrip)(RpBuildMesh* buildMesh, void* data);
extern RpMeshHeader* (*RpBuildMeshGenerateTrivialTriStrip)(RpBuildMesh* buildMesh, void* data);
extern RpMeshHeader* (*RpBuildMeshGenerateDefaultTriStrip)(RpBuildMesh* buildmesh, void* data);
extern RpMeshHeader* (*RpBuildMeshGeneratePreprocessTriStrip)(RpBuildMesh* buildmesh, void* data);
extern RpMeshHeader* (*RpBuildMeshGenerateExhaustiveTriStrip)(RpBuildMesh* buildmesh, void* data);
extern RpMeshHeader* (*RpBuildMeshGenerateDefaultIgnoreWindingTriStrip)(RpBuildMesh* buildmesh, void* data);
extern RpMeshHeader* (*RpBuildMeshGeneratePreprocessIgnoreWindingTriStrip)(RpBuildMesh* buildmesh, void* data);
extern RpMeshHeader* (*RpBuildMeshGenerateExhaustiveIgnoreWindingTriStrip)(RpBuildMesh* buildmesh, void* data);
extern RwBool (*RpMeshSetTriStripMethod)(RpTriStripMeshCallBack callback, void* data);
extern RwBool (*RpMeshGetTriStripMethod)(RpTriStripMeshCallBack* callback, void* data);
extern RpMeshHeader* (*_rpTriListMeshGenerate)(RpBuildMesh* buildMesh, void* data);
extern RpMeshHeader* (*_rpMeshOptimise)(RpBuildMesh* buildmesh, RwUInt32 flags);
extern RpGeometry* (*RpGeometryTransform)(RpGeometry* geometry, const RwMatrix* matrix);
extern RpGeometry* (*RpGeometryCreateSpace)(RwReal radius);
extern const RpMorphTarget* (*RpMorphTargetCalcBoundingSphere)(const RpMorphTarget* morphTarget, RwSphere* boundingSphere);
extern RwInt32 (*RpGeometryAddMorphTargets)(RpGeometry* geometry, RwInt32 mtcount);
extern RwInt32 (*RpGeometryAddMorphTarget)(RpGeometry* geometry);
extern RpGeometry* (*RpGeometryRemoveMorphTarget)(RpGeometry* geometry, RwInt32 morphTarget);
extern const RpGeometry* (*RpGeometryTriangleSetVertexIndices)(const RpGeometry* geometry, RpTriangle* triangle, RwUInt16 vert1, RwUInt16 vert2, RwUInt16 vert3);
extern RpGeometry* (*RpGeometryTriangleSetMaterial)(RpGeometry* geometry, RpTriangle* triangle, RpMaterial* material);
extern const RpGeometry* (*RpGeometryTriangleGetVertexIndices)(const RpGeometry* geometry, const RpTriangle* triangle, RwUInt16* vert1, RwUInt16* vert2, RwUInt16* vert3);
extern RpMaterial* (*RpGeometryTriangleGetMaterial)(const RpGeometry* geometry, const RpTriangle* triangle);
extern RpGeometry* (*RpGeometryForAllMaterials)(RpGeometry* geometry, RpMaterialCallBack fpCallBack, void* pData);
extern RpGeometry* (*RpGeometryLock)(RpGeometry* geometry, RwInt32 lockMode);
extern RpGeometry* (*RpGeometryUnlock)(RpGeometry* geometry);
extern const RpGeometry* (*RpGeometryForAllMeshes)(const RpGeometry* geometry, RpMeshCallBack fpCallBack, void* pData);
extern RpGeometry* (*RpGeometryCreate)(RwInt32 numVert, RwInt32 numTriangles, RwUInt32 format);
extern RwBool (*RpGeometryDestroy)(RpGeometry* geometry);
extern RwInt32 (*RpGeometryRegisterPlugin)(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
extern RwInt32 (*RpGeometryRegisterPluginStream)(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 (*RpGeometrySetStreamAlwaysCallBack)(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwInt32 (*RpGeometryGetPluginOffset)(RwUInt32 pluginID);
extern RwBool (*RpGeometryValidatePlugins)(const RpGeometry* geometry);
extern RwUInt32 (*RpGeometryStreamGetSize)(const RpGeometry* geometry);
extern const RpGeometry* (*RpGeometryStreamWrite)(const RpGeometry* geometry, RwStream* stream);
extern RpGeometry* (*RpGeometryStreamRead)(RwStream* stream);
extern RpGeometryChunkInfo* (*_rpGeometryChunkInfoRead)(RwStream* stream, RpGeometryChunkInfo* geometryChunkInfo, RwInt32* bytesRead);
extern RpWorldSector* (*RpWorldSectorRender)(RpWorldSector* worldSector);
extern const RpWorldSector* (*RpWorldSectorForAllMeshes)(const RpWorldSector* sector, RpMeshCallBack fpCallBack, void* pData);
extern RwInt32 (*RpWorldSectorRegisterPlugin)(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
extern RwInt32 (*RpWorldSectorRegisterPluginStream)(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 (*RpWorldSectorSetStreamAlwaysCallBack)(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwInt32 (*RpWorldSectorSetStreamRightsCallBack)(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB);
extern RwInt32 (*RpWorldSectorGetPluginOffset)(RwUInt32 pluginID);
extern RwBool (*RpWorldSectorValidatePlugins)(const RpWorldSector* sector);
extern void (*RpLightSetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RpLight* (*RpLightCreate)(RwInt32 type);
extern RwBool (*RpLightDestroy)(RpLight* light);
extern RpLight* (*RpLightSetRadius)(RpLight* light, RwReal radius);
extern RpLight* (*RpLightSetColor)(RpLight* light, const RwRGBAReal* color);
extern RwReal (*RpLightGetConeAngle)(const RpLight* light);
extern RpLight* (*RpLightSetConeAngle)(RpLight* ight, RwReal angle);
extern RwUInt32 (*RpLightStreamGetSize)(const RpLight* light);
extern RpLight* (*RpLightStreamRead)(RwStream* stream);
extern RpLightChunkInfo* (*_rpLightChunkInfoRead)(RwStream* stream, RpLightChunkInfo* lightChunkInfo, RwInt32* bytesRead);
extern RwInt32 (*RpLightRegisterPlugin)(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
extern RwInt32 (*RpLightRegisterPluginStream)(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 (*RpLightSetStreamAlwaysCallBack)(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwInt32 (*RpLightGetPluginOffset)(RwUInt32 pluginID);
extern RwBool (*RpLightValidatePlugins)(const RpLight* light);
extern void (*RpAtomicSetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern void (*RpClumpSetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RpAtomic* (*AtomicDefaultRenderCallBack)(RpAtomic* atomic);
extern void (*_rpAtomicResyncInterpolatedSphere)(RpAtomic* atomic);
extern const RwSphere* (*RpAtomicGetWorldBoundingSphere)(RpAtomic* atomic);
extern RpClump* (*RpClumpForAllAtomics)(RpClump* clump, RpAtomicCallBack callback, void* pData);
extern RpClump* (*RpClumpForAllLights)(RpClump* clump, RpLightCallBack callback, void* pData);
extern RpClump* (*RpClumpForAllCameras)(RpClump* clump, RwCameraCallBack callback, void* pData);
extern RpAtomic* (*RpAtomicSetFrame)(RpAtomic* atomic, RwFrame* frame);
extern RpClump* (*RpClumpCreateSpace)(const RwV3d* position, RwReal radius);
extern RpClump* (*RpClumpRender)(RpClump* clump);
extern RpClump* (*RpClumpRemoveAtomic)(RpClump* clump, RpAtomic* atomic);
extern RpClump* (*RpClumpAddAtomic)(RpClump* clump, RpAtomic* atomic);
extern RpClump* (*RpClumpRemoveLight)(RpClump* clump, RpLight* light);
extern RpClump* (*RpClumpAddLight)(RpClump* clump, RpLight* light);
extern RpClump* (*RpClumpRemoveCamera)(RpClump* clump, RwCamera* camera);
extern RpClump* (*RpClumpAddCamera)(RpClump* clump, RwCamera* camera);
extern RwBool (*RpClumpDestroy)(RpClump* clump);
extern RpClump* (*RpClumpCreate)(void);
extern RpClump* (*RpClumpClone)(RpClump* clump);
extern RwBool (*RpAtomicDestroy)(RpAtomic* atomic);
extern RpAtomic* (*RpAtomicClone)(RpAtomic* atomic);
extern RpAtomic* (*RpAtomicCreate)(void);
extern RpAtomic* (*RpAtomicSetGeometry)(RpAtomic* atomic, RpGeometry* geometry, RwUInt32 flags);
extern RpClump* (*RpClumpSetCallBack)(RpClump* clump, RpClumpCallBack callback);
extern RpClumpCallBack (*RpClumpGetCallBack)(const RpClump* clump);
extern RwInt32 (*RpClumpGetNumAtomics)(RpClump* clump);
extern RwInt32 (*RpClumpGetNumLights)(RpClump* clump);
extern RwInt32 (*RpClumpGetNumCameras)(RpClump* clump);
extern RpClump* (*RpLightGetClump)(const RpLight* light);
extern RpClump* (*RwCameraGetClump)(const RwCamera* camera);
extern RwUInt32 (*RpAtomicStreamGetSize)(RpAtomic* atomic);
extern RpAtomic* (*RpAtomicStreamRead)(RwStream* stream);
extern RpAtomic* (*RpAtomicStreamWrite)(RpAtomic* atomic, RwStream* stream);
extern RwUInt32 (*RpClumpStreamGetSize)(RpClump* clump);
extern RpClump* (*RpClumpStreamRead)(RwStream* stream);
extern RpClump* (*RpClumpStreamWrite)(RpClump* clump, RwStream* stream);
extern RpClumpChunkInfo* (*_rpClumpChunkInfoRead)(RwStream* stream, RpClumpChunkInfo* clumpChunkInfo, RwInt32* bytesRead);
extern RwInt32 (*RpAtomicRegisterPlugin)(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
extern RwInt32 (*RpClumpRegisterPlugin)(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
extern RwInt32 (*RpAtomicRegisterPluginStream)(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 (*RpAtomicSetStreamAlwaysCallBack)(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwInt32 (*RpAtomicSetStreamRightsCallBack)(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB);
extern RwInt32 (*RpClumpRegisterPluginStream)(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 (*RpClumpSetStreamAlwaysCallBack)(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwInt32 (*RpAtomicGetPluginOffset)(RwUInt32 pluginID);
extern RwInt32 (*RpClumpGetPluginOffset)(RwUInt32 pluginID);
extern RwBool (*RpAtomicValidatePlugins)(const RpAtomic* atomic);
extern RwBool (*RpClumpValidatePlugins)(const RpClump* clump);
extern RwBool (*RpAtomicInstance)(RpAtomic* atomic);
extern RwBool (*_rpWorldFindBBox)(RpWorld* world, RwBBox* boundingBox);
extern RpWorld* (*_rpWorldSetupSectorBoundingBoxes)(RpWorld* world);
// extern void (*_rpWorldSectorDeinstanceAll)(RpSector* sector);
// extern void (*_rpWorldSectorDestroyRecurse)(RpSector* sector);
extern RwBool (*_rpWorldForAllGlobalLights)(RpLightCallBack callBack, void* pData);
extern RpWorldSector* (*_rpWorldSectorForAllLocalLights)(RpWorldSector* sector, RpLightCallBack callBack, void* pData);
extern RpWorldSector* (*_rpSectorDefaultRenderCallBack)(RpWorldSector* sector);
extern RpWorld* (*RpWorldLock)(RpWorld* world);
extern RpWorld* (*RpWorldUnlock)(RpWorld* world);
extern void (*_rpWorldRegisterWorld)(RpWorld* world, RwUInt32 memorySize);
extern void (*_rpWorldUnregisterWorld)(RpWorld* world);
extern RwBool (*RpWorldPluginAttach)(void);
extern RpWorld* (*RpWorldForAllClumps)(RpWorld* world, RpClumpCallBack fpCallBack, void* pData);
extern RpWorld* (*RpWorldForAllMaterials)(RpWorld* world, RpMaterialCallBack fpCallBack, void* pData);
extern RpWorld* (*RpWorldForAllLights)(RpWorld* world, RpLightCallBack fpCallBack, void* pData);
extern RpWorld* (*RpWorldForAllWorldSectors)(RpWorld* world, RpWorldSectorCallBack fpCallBack, void* pData);
extern RpWorld* (*RpWorldRender)(RpWorld* world);
extern RwBool (*RpWorldDestroy)(RpWorld* world);
extern RpWorld* (*RpWorldCreate)(RwBBox* boundingBox);
extern RpWorld* (*RpWorldSetSectorRenderCallBack)(RpWorld* world, RpWorldSectorCallBackRender fpCallBack);
extern RpWorldSectorCallBackRender (*RpWorldGetSectorRenderCallBack)(const RpWorld* world);
extern RpWorld* (*RpWorldSectorGetWorld)(const RpWorldSector* sector);
extern RwInt32 (*RpWorldRegisterPlugin)(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
extern RwInt32 (*RpWorldRegisterPluginStream)(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB);
extern RwInt32 (*RpWorldSetStreamAlwaysCallBack)(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB);
extern RwInt32 (*RpWorldSetStreamRightsCallBack)(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB);
extern RwInt32 (*RpWorldGetPluginOffset)(RwUInt32 pluginID);
extern RwBool (*RpWorldValidatePlugins)(RpWorld* world);
extern RxPipeline* (*RpWorldSetDefaultSectorPipeline)(RxPipeline* pipeline);
extern RxPipeline* (*RpAtomicSetDefaultPipeline)(RxPipeline* pipeline);
extern RxPipeline* (*RpMaterialSetDefaultPipeline)(RxPipeline* pipeline);
extern const RpGeometry* (*RpGeometryIsCorrectlySorted)(const RpGeometry* geometry, RwBool* result);
extern RpGeometry* (*RpGeometrySortByMaterial)(const RpGeometry* geometry, RpGeometrySortByMaterialCallBack callback);
extern void (*RpTieSetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern void (*RpLightTieSetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RpWorld* (*RpWorldRemoveCamera)(RpWorld* world, RwCamera* camera);
extern RpWorld* (*RpWorldAddCamera)(RpWorld* world, RwCamera* camera);
extern RpWorld* (*RwCameraGetWorld)(const RwCamera* camera);
extern RpWorld* (*RpWorldRemoveAtomic)(RpWorld* world, RpAtomic* atomic);
extern RpWorld* (*RpWorldAddAtomic)(RpWorld* world, RpAtomic* atomic);
extern RpWorld* (*RpAtomicGetWorld)(const RpAtomic* atomic);
extern RpWorld* (*RpWorldAddClump)(RpWorld* world, RpClump* clump);
extern RpWorld* (*RpWorldRemoveClump)(RpWorld* world, RpClump* clump);
extern RpWorld* (*RpClumpGetWorld)(const RpClump* clump);
extern RpWorld* (*RpWorldAddLight)(RpWorld* world, RpLight* light);
extern RpWorld* (*RpWorldRemoveLight)(RpWorld* world, RpLight* light);
extern RpWorld* (*RpLightGetWorld)(const RpLight* light);
extern RwCamera* (*RwCameraForAllClumpsInFrustum)(RwCamera* camera, void* data);
// extern RwCamera* (*RwCameraForAllAtomicsInFrustum)(RwCamera* camera, RpAtomicCallBack callback, void* data);
extern RwCamera* (*RwCameraForAllSectorsInFrustum)(RwCamera* camera, RpWorldSectorCallBack callBack, void* pData);
extern RpLight* (*RpLightForAllWorldSectors)(RpLight* light, RpWorldSectorCallBack callback, void* data);
extern RpAtomic* (*RpAtomicForAllWorldSectors)(RpAtomic* atomic, RpWorldSectorCallBack callback, void* data);
extern RpWorldSector* (*RpWorldSectorForAllAtomics)(RpWorldSector* sector, RpAtomicCallBack callback, void* data);
extern RpWorldSector* (*RpWorldSectorForAllCollisionAtomics)(RpWorldSector* sector, RpAtomicCallBack callback, void* data);
extern RpWorldSector* (*RpWorldSectorForAllLights)(RpWorldSector* sector, RpLightCallBack callback, void* data);
extern RwUInt32 (*RpWorldStreamGetSize)(const RpWorld* world);
extern RpWorld* (*RpWorldStreamRead)(RwStream* stream);
extern const RpWorld* (*RpWorldStreamWrite)(const RpWorld* world, RwStream* stream);
extern RpWorldSectorChunkInfo* (*_rpWorldSectorChunkInfoRead)(RwStream* stream, RpWorldSectorChunkInfo* worldSectorChunkInfo, RwInt32* bytesRead);
extern RpPlaneSectorChunkInfo* (*_rpPlaneSectorChunkInfoRead)(RwStream* stream, RpPlaneSectorChunkInfo* planeSectorChunkInfo, RwInt32* bytesRead);
extern RpWorldChunkInfo* (*_rpWorldChunkInfoRead)(RwStream* stream, RpWorldChunkInfo* worldChunkInfo, RwInt32* bytesRead);

/* rtquat.h */

extern RwBool (*RtQuatConvertFromMatrix)(RtQuat * const qpQuat, const RwMatrix * const mpMatrix);
extern RtQuat* (*RtQuatRotate)(RtQuat* quat, const RwV3d* axis, RwReal angle, RwOpCombineType combineOp);
extern const RtQuat* (*RtQuatQueryRotate)(const RtQuat* quat, RwV3d* unitAxis, RwReal* angle);
extern RwV3d* (*RtQuatTransformVectors)(RwV3d* vectorsOut, const RwV3d* vectorsIn, const RwInt32 numPoints, const RtQuat* quat);
extern RwReal (*RtQuatModulus)(RtQuat* q);

/* rtanim.h */

extern void (*RtAnimAnimationFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RwBool (*RtAnimInitialize)(void);
extern RwBool (*RtAnimRegisterInterpolationScheme)(RtAnimInterpolatorInfo* interpolatorInfo);
extern RtAnimInterpolatorInfo* (*RtAnimGetInterpolatorInfo)(RwInt32 typeID);
extern RtAnimAnimation* (*RtAnimAnimationCreate)(RwInt32 typeID, RwInt32 numFrames, RwInt32 flags, RwReal duration);
extern RwBool (*RtAnimAnimationDestroy)(RtAnimAnimation* animation);
extern RtAnimAnimation* (*RtAnimAnimationRead)(const RwChar* filename);
extern RwBool (*RtAnimAnimationWrite)(const RtAnimAnimation* animation, const RwChar* filename);
extern RtAnimAnimation* (*RtAnimAnimationStreamRead)(RwStream* stream);
extern RwBool (*RtAnimAnimationStreamWrite)(const RtAnimAnimation* animation, RwStream* stream);
extern RwInt32 (*RtAnimAnimationStreamGetSize)(const RtAnimAnimation* animation);
extern RwUInt32 (*RtAnimAnimationGetNumNodes)(const RtAnimAnimation* animation);
extern RtAnimInterpolator* (*RtAnimInterpolatorCreate)(RwInt32 numNodes, RwInt32 maxInterpKeyFrameSize);
extern void (*RtAnimInterpolatorDestroy)(RtAnimInterpolator* anim);
extern RwBool (*RtAnimInterpolatorSetCurrentAnim)(RtAnimInterpolator* animI, RtAnimAnimation* anim);
extern RwBool (*RtAnimInterpolatorSetKeyFrameCallBacks)(RtAnimInterpolator* anim, RwInt32 keyFrameTypeID);
extern void (*RtAnimInterpolatorSetAnimLoopCallBack)(RtAnimInterpolator* anim, RtAnimCallBack callBack, void* data);
extern void (*RtAnimInterpolatorSetAnimCallBack)(RtAnimInterpolator* anim, RtAnimCallBack callBack, RwReal time, void* data);
extern RwBool (*RtAnimInterpolatorCopy)(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim);
extern RwBool (*RtAnimInterpolatorSubAnimTime)(RtAnimInterpolator* anim, RwReal time);
extern RwBool (*RtAnimInterpolatorAddAnimTime)(RtAnimInterpolator* anim, RwReal time);
extern RwBool (*RtAnimInterpolatorSetCurrentTime)(RtAnimInterpolator* anim, RwReal time);
extern RwBool (*RtAnimAnimationMakeDelta)(RtAnimAnimation* animation, RwInt32 numNodes, RwReal time);
extern RwBool (*RtAnimInterpolatorBlend)(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1, RtAnimInterpolator* inAnim2, RwReal alpha);
extern RwBool (*RtAnimInterpolatorAddTogether)(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1, RtAnimInterpolator* inAnim2);
extern RtAnimInterpolator* (*RtAnimInterpolatorCreateSubInterpolator)(RtAnimInterpolator* parentAnim, RwInt32 startNode, RwInt32 numNodes, RwInt32 maxInterpKeyFrameSize);
extern RwBool (*RtAnimInterpolatorBlendSubInterpolator)(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1, RtAnimInterpolator* inAnim2, RwReal alpha);
extern RwBool (*RtAnimInterpolatorAddSubInterpolator)(RtAnimInterpolator* outAnim, RtAnimInterpolator* mainAnim, RtAnimInterpolator* subAnim);

/* rphanim.h */

extern void (*RpHAnimHierarchySetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RpHAnimHierarchy* (*RpHAnimHierarchyCreate)(RwInt32 numNodes, RwUInt32* nodeFlags, RwInt32* nodeIDs, RpHAnimHierarchyFlag flags, RwInt32 maxInterpKeyFrameSize);
extern RpHAnimHierarchy* (*RpHAnimHierarchyCreateFromHierarchy)(RpHAnimHierarchy* hierarchy, RpHAnimHierarchyFlag flags, RwInt32 maxInterpKeyFrameSize);
extern RpHAnimHierarchy* (*RpHAnimHierarchyDestroy)(RpHAnimHierarchy* hierarchy);
extern RpHAnimHierarchy* (*RpHAnimHierarchyCreateSubHierarchy)(RpHAnimHierarchy* parentHierarchy, RwInt32 startNode, RpHAnimHierarchyFlag flags, RwInt32 maxInterpKeyFrameSize);
extern RpHAnimHierarchy* (*RpHAnimHierarchyAttach)(RpHAnimHierarchy* hierarchy);
extern RpHAnimHierarchy* (*RpHAnimHierarchyDetach)(RpHAnimHierarchy* hierarchy);
extern RpHAnimHierarchy* (*RpHAnimHierarchyAttachFrameIndex)(RpHAnimHierarchy* hierarchy, RwInt32 nodeIndex);
extern RpHAnimHierarchy* (*RpHAnimHierarchyDetachFrameIndex)(RpHAnimHierarchy* hierarchy, RwInt32 nodeIndex);
extern RwBool (*RpHAnimFrameSetHierarchy)(RwFrame* frame, RpHAnimHierarchy* hierarchy);
extern RpHAnimHierarchy* (*RpHAnimFrameGetHierarchy)(RwFrame* frame);
extern RwMatrix* (*RpHAnimHierarchyGetMatrixArray)(RpHAnimHierarchy* hierarchy);
extern RwBool (*RpHAnimHierarchyUpdateMatrices)(RpHAnimHierarchy* hierarchy);
extern RwInt32 (*RpHAnimIDGetIndex)(RpHAnimHierarchy* hierarchy, RwInt32 ID);
extern RwBool (*RpHAnimPluginAttach)(void);
extern void (*RpHAnimKeyFrameApply)(void* matrix, void* voidIFrame);
extern void (*RpHAnimKeyFrameBlend)(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha);
extern void (*RpHAnimKeyFrameInterpolate)(void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* customData);
extern void (*RpHAnimKeyFrameAdd)(void* voidOut, void* voidIn1, void* voidIn2);
extern void (*RpHAnimKeyFrameMulRecip)(void* voidFrame, void* voidStart);
extern RtAnimAnimation* (*RpHAnimKeyFrameStreamRead)(RwStream* stream, RtAnimAnimation* animation);
extern RwBool (*RpHAnimKeyFrameStreamWrite)(const RtAnimAnimation* animation, RwStream* stream);
extern RwInt32 (*RpHAnimKeyFrameStreamGetSize)(const RtAnimAnimation* animation);
extern RwBool (*RpHAnimFrameSetID)(RwFrame* frame, RwInt32 id);
extern RwInt32 (*RpHAnimFrameGetID)(RwFrame* frame);

/* rpuvanim.h */

extern _rpUVAnimCustomData* (*_rpUVAnimCustomDataStreamRead)(RwStream* stream);
extern const _rpUVAnimCustomData* (*_rpUVAnimCustomDataStreamWrite)(const _rpUVAnimCustomData* customData, RwStream* stream);
extern RwUInt32 (*_rpUVAnimCustomDataStreamGetSize)(const _rpUVAnimCustomData* customData);
extern RwBool (*RpUVAnimPluginAttach)(void);
extern void (*RpUVAnimLinearKeyFrameApply)(void* matrix, void* voidIFrame);
extern void (*RpUVAnimLinearKeyFrameBlend)(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha);
extern void (*RpUVAnimLinearKeyFrameInterpolate)(void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* customData);
extern void (*RpUVAnimLinearKeyFrameAdd)(void* voidOut, void* voidIn1, void* voidIn2);
extern void (*RpUVAnimLinearKeyFrameMulRecip)(void* voidFrame, void* voidStart);
extern void (*RpUVAnimParamKeyFrameApply)(void* matrix, void* voidIFrame);
extern void (*RpUVAnimParamKeyFrameBlend)(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha);
extern void (*RpUVAnimParamKeyFrameInterpolate)(void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* customData);
extern void (*RpUVAnimParamKeyFrameAdd)(void* voidOut, void* voidIn1, void* voidIn2);
extern void (*RpUVAnimParamKeyFrameMulRecip)(void* voidFrame, void* voidStart);
extern RtAnimAnimation* (*RpUVAnimKeyFrameStreamRead)(RwStream* stream, RtAnimAnimation* animation);
extern RwBool (*RpUVAnimKeyFrameStreamWrite)(const RtAnimAnimation* animation, RwStream* stream);
extern RwInt32 (*RpUVAnimKeyFrameStreamGetSize)(const RtAnimAnimation* animation);
extern RpUVAnim* (*RpUVAnimCreate)(const RwChar* name, RwUInt32 numNodes, RwUInt32 numFrames, RwReal duration, RwUInt32* nodeIndexToUVChannelMap, RpUVAnimKeyFrameType keyframeType);
extern RwBool (*RpUVAnimDestroy)(RpUVAnim* anim);
extern RpUVAnim* (*RpUVAnimAddRef)(RpUVAnim* anim);
extern const RwChar* (*RpUVAnimGetName)(const RpUVAnim* anim);
extern RpMaterial* (*RpMaterialSetUVAnim)(RpMaterial* material, RpUVAnim* anim, RwUInt32 slot);
extern RpUVAnimInterpolator* (*RpMaterialUVAnimGetInterpolator)(RpMaterial* material, RwUInt32 slot);
extern RpMaterial* (*RpMaterialUVAnimSetInterpolator)(RpMaterial* material, RpUVAnimInterpolator* interp, RwUInt32 slot);
extern RpMaterial* (*RpMaterialUVAnimSetCurrentTime)(RpMaterial* material, RwReal time);
extern RpMaterial* (*RpMaterialUVAnimAddAnimTime)(RpMaterial* material, RwReal deltaTime);
extern RpMaterial* (*RpMaterialUVAnimSubAnimTime)(RpMaterial* material, RwReal deltaTime);
extern RwBool (*RpMaterialUVAnimExists)(const RpMaterial* material);

/* rpskin.h */

extern void (*RpSkinSetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RwBool (*RpSkinPluginAttach)(void);
extern RpAtomic* (*RpSkinAtomicSetHAnimHierarchy)(RpAtomic* atomic, RpHAnimHierarchy* hierarchy);
extern RpHAnimHierarchy* (*RpSkinAtomicGetHAnimHierarchy)(const RpAtomic* atomic);
extern RpGeometry* (*RpSkinGeometrySetSkin)(RpGeometry* geometry, RpSkin* skin);
extern RpSkin* (*RpSkinGeometryGetSkin)(RpGeometry* geometry);
extern RpSkin* (*RpSkinCreate)(RwUInt32 numVertices, RwUInt32 numBones, RwMatrixWeights* vertexWeights, RwUInt32* vertexIndices, RwMatrix* inverseMatrices);
extern RpSkin* (*RpSkinDestroy)(RpSkin* skin);
extern RwUInt32 (*RpSkinGetNumBones)(RpSkin* skin);
extern const RwMatrixWeights* (*RpSkinGetVertexBoneWeights)(RpSkin* skin);
extern const RwUInt32* (*RpSkinGetVertexBoneIndices)(RpSkin* skin);
extern const RwMatrix* (*RpSkinGetSkinToBoneMatrices)(RpSkin* skin);
extern RwBool (*RpSkinIsSplit)(RpSkin* skin);
extern RpAtomic* (*RpSkinAtomicSetType)(RpAtomic* atomic, RpSkinType type);
extern RpSkinType (*RpSkinAtomicGetType)(RpAtomic* atomic);
extern RpGeometry* (*_rpSkinInitialize)(RpGeometry* geometry);
extern RpGeometry* (*_rpSkinDeinitialize)(RpGeometry* geometry);
extern RwUInt8* (*_rpSkinGetMeshBoneRemapIndices)(RpSkin* skin);
extern RwUInt8* (*_rpSkinGetMeshBoneRLECount)(RpSkin* skin);
extern RwUInt8* (*_rpSkinGetMeshBoneRLE)(RpSkin* skin);
extern RpSkin* (*_rpSkinSplitDataCreate)(RpSkin* skin, RwUInt32 boneLimit, RwUInt32 numMatrices, RwUInt32 numMeshes, RwUInt32 numRLE);
extern RwBool (*_rpSkinSplitDataDestroy)(RpSkin* skin);

/* rtdict.h */

extern RtDictSchema* (*RtDictSchemaInit)(RtDictSchema* schema);
extern RwBool (*RtDictSchemaDestruct)(RtDictSchema* schema);
extern RtDict* (*RtDictSchemaStreamReadDict)(RtDictSchema* schema, RwStream* stream);
extern RtDict* (*RtDictSchemaCreateDict)(RtDictSchema* schema);
extern RtDictSchema* (*RtDictSchemaAddDict)(RtDictSchema* schema, RtDict* dict);
extern RtDictSchema* (*RtDictSchemaRemoveDict)(RtDictSchema* schema, RtDict* dict);
extern RwBool (*RtDictSchemaForAllDictionaries)(RtDictSchema* schema, RtDictCallBack* callback, RtDictEntryType data);
extern RtDict* (*RtDictSchemaGetCurrentDict)(RtDictSchema* schema);
extern RtDictSchema* (*RtDictSchemaSetCurrentDict)(RtDictSchema* schema, RtDict* dict);
extern RwBool (*RtDictDestroy)(RtDict* dictionary);
extern RtDictEntryType (*RtDictAddEntry)(RtDict* dictionary, RtDictEntryType entry);
extern RtDictEntryType (*RtDictFindNamedEntry)(RtDict* dictionary, const RwChar* name);
extern const RtDict* (*RtDictForAllEntries)(const RtDict* dictionary, RtDictEntryCallBack* callBack, RtDictEntryType data);
extern RtDict* (*RtDictRemoveEntry)(RtDict* dictionary, RtDictEntryType entry);
extern const RtDict* (*RtDictStreamWrite)(const RtDict* dictionary, RwStream* stream);
extern RwUInt32 (*RtDictStreamGetSize)(const RtDict* dictionary);
extern RtDict* (*_rtDictSchemaInitDict)(RtDictSchema* schema, RtDict* dictionary);
extern RwBool (*_rtDictDestruct)(RtDict* dictionary);

/* rpmatfx.h */

extern void (*RpMatFXMaterialDataSetFreeListCreateParams)(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern RwBool (*RpMatFXPluginAttach)(void);
extern RpAtomic* (*RpMatFXAtomicEnableEffects)(RpAtomic* atomic);
extern RwBool (*RpMatFXAtomicQueryEffects)(RpAtomic* atomic);
extern RpWorldSector* (*RpMatFXWorldSectorEnableEffects)(RpWorldSector* worldSector);
extern RwBool (*RpMatFXWorldSectorQueryEffects)(RpWorldSector* worldSector);
extern RpMaterial* (*RpMatFXMaterialSetEffects)(RpMaterial* material, RpMatFXMaterialFlags flags);
extern RpMaterial* (*RpMatFXMaterialSetupBumpMap)(RpMaterial* material, RwTexture* texture, RwFrame* frame, RwReal coef);
extern RpMaterial* (*RpMatFXMaterialSetupEnvMap)(RpMaterial* material, RwTexture* texture, RwFrame* frame, RwBool useFrameBufferAlpha, RwReal coef);
extern RpMaterial* (*RpMatFXMaterialSetupDualTexture)(RpMaterial* material, RwTexture* texture, RwBlendFunction srcBlendMode, RwBlendFunction dstBlendMode);
extern RpMatFXMaterialFlags (*RpMatFXMaterialGetEffects)(const RpMaterial* material);
extern RpMaterial* (*RpMatFXMaterialSetBumpMapTexture)(RpMaterial* material, RwTexture* texture);
extern RpMaterial* (*RpMatFXMaterialSetBumpMapFrame)(RpMaterial* material, RwFrame* frame);
extern RpMaterial* (*RpMatFXMaterialSetBumpMapCoefficient)(RpMaterial* material, RwReal coef);
extern RwTexture* (*RpMatFXMaterialGetBumpMapTexture)(const RpMaterial* material);
extern RwTexture* (*RpMatFXMaterialGetBumpMapBumpedTexture)(const RpMaterial* material);
extern RwFrame* (*RpMatFXMaterialGetBumpMapFrame)(const RpMaterial* material);
extern RwReal (*RpMatFXMaterialGetBumpMapCoefficient)(const RpMaterial* material);
extern RpMaterial* (*RpMatFXMaterialSetEnvMapTexture)(RpMaterial* material, RwTexture* texture);
extern RpMaterial* (*RpMatFXMaterialSetEnvMapFrame)(RpMaterial* material, RwFrame* frame);
extern RpMaterial* (*RpMatFXMaterialSetEnvMapFrameBufferAlpha)(RpMaterial* material, RwBool useFrameBufferAlpha);
extern RpMaterial* (*RpMatFXMaterialSetEnvMapCoefficient)(RpMaterial* material, RwReal coef);
extern RwTexture* (*RpMatFXMaterialGetEnvMapTexture)(const RpMaterial* material);
extern RwFrame* (*RpMatFXMaterialGetEnvMapFrame)(const RpMaterial* material);
extern RwBool (*RpMatFXMaterialGetEnvMapFrameBufferAlpha)(const RpMaterial* material);
extern RwReal (*RpMatFXMaterialGetEnvMapCoefficient)(const RpMaterial* material);
extern RpMaterial* (*RpMatFXMaterialSetDualTexture)(RpMaterial* material, RwTexture* texture);
extern RpMaterial* (*RpMatFXMaterialSetDualBlendModes)(RpMaterial* material, RwBlendFunction srcBlendMode, RwBlendFunction dstBlendMode);
extern RwTexture* (*RpMatFXMaterialGetDualTexture)(const RpMaterial* material);
extern const RpMaterial* (*RpMatFXMaterialGetDualBlendModes)(const RpMaterial* material, RwBlendFunction* srcBlendMode, RwBlendFunction* dstBlendMode);
extern RpMaterial* (*RpMatFXMaterialSetUVTransformMatrices)(RpMaterial* material, RwMatrix* baseTransform, RwMatrix* dualTransform);
extern const RpMaterial* (*RpMatFXMaterialGetUVTransformMatrices)(const RpMaterial* material, RwMatrix* baseTransform, RwMatrix* dualTransform);

/* skeleton.h */
extern RsEventStatus (*RsEventHandler)(RsEvent e, void* param);

/* rpanisot.h */

// extern RwInt8 (*RpAnisotGetMaxSupportedMaxAnisotropy)(void);
// extern RwTexture* (*RpAnisotTextureSetMaxAnisotropy)(RwTexture* tex, RwInt8 val);
// extern RwInt8 (*RpAnisotTextureGetMaxAnisotropy)(RwTexture* tex);
// extern RwBool (*RpAnisotPluginAttach)(void);

/* rtbmp.h */

extern RwImage* (*RtBMPImageWrite)(RwImage* image, const RwChar* imageName);
extern RwImage* (*RtBMPImageRead)(const RwChar* imageName);

/* rtpng.h */

extern RwImage* (*RtPNGImageWrite)(RwImage* image, const RwChar* imageName);
extern RwImage* (*RtPNGImageRead)(const RwChar* imageName);

extern void (*_rpMaterialSetDefaultSurfaceProperties)(RwSurfaceProperties *surfProps);

extern void (*_rwObjectHasFrameSetFrame)(void *object, RwFrame *frame);
extern void (*_rwObjectHasFrameReleaseFrame)(void *object);


extern RwBool (*_rwStreamReadChunkHeader)(RwStream *stream, RwUInt32 *pType, RwUInt32 *pLength, RwUInt32 *pVersion, RwUInt32 *pBuild);

#define RwRenderStateGetMacro(_state, _value)   \
    (RWSRCGLOBAL(dOpenDevice).fpRenderStateGet(_state, _value))

#define RwRenderStateSetMacro(_state, _value)   \
    (RWSRCGLOBAL(dOpenDevice).fpRenderStateSet(_state, _value))

#define RwRenderStateGet(_state, _value) \
        RwRenderStateGetMacro(_state, _value)

#define RwRenderStateSet(_state, _value) \
        RwRenderStateSetMacro(_state, _value)

#define RWRSTATE(a) (reinterpret_cast<void *>(a))

#define rwObjectHasFrameSetFrame(object, frame) \
        _rwObjectHasFrameSetFrame(object, frame)
#define rwObjectHasFrameReleaseFrame(object) \
        _rwObjectHasFrameReleaseFrame(object)

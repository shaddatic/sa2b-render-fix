/*
*   Sonic Adventure Mod Tools (SA2B) - '/magic/rendercore.h'
*
*   Description:
*       Magic's RenderCore namespace.
*
*   Contributors:
*     - Magic Developers
*     - kellnc
*     - MainMemory
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _MAGIC_RENDERCORE_H_
#define _MAGIC_RENDERCORE_H_

#ifdef  __cplusplus

/************************/
/*  Includes            */
/************************/
/** Utility **/
#include <sa2b/util/cpp_old.h>

/** Magic **/
#include <sa2b/magic/math.h>

/** cppstd **/
#include <map>
#include <list>
#include <string>
#include <vector>

/************************/
/*  Abstract Types      */
/************************/
#ifndef _D3D9_H_

typedef void*       LPDIRECT3D9;
typedef int32_t     D3DDISPLAYMODE[4];
typedef void*       LPDIRECT3DDEVICE9;
typedef int32_t     D3DPRESENT_PARAMETERS[14];
typedef void        HWND__;
typedef void*       LPDIRECT3DSURFACE9;
typedef void*       LPDIRECT3DVERTEXDECLARATION9;
typedef void*       LPDIRECT3DVERTEXBUFFER9;
typedef void*       LPDIRECT3DINDEXBUFFER9;
typedef void*       LPDIRECT3DTEXTURE9;
typedef void*       LPDIRECT3DVERTEXSHADER9;
typedef void*       LPDIRECT3DPIXELSHADER9;

#endif/*_D3D9_H_*/

/************************/
/*  Render Core         */
/************************/
namespace Magic::RenderCore
{
    struct Sampler;
    struct Resource;
    struct Material;
    struct Texture;
    struct InputLayout;
    struct RenderDevice;
    struct ResourceProfiler;
    struct DX9_DeviceCreator_Base;
    struct VideoDevice;
    struct DeviceConfig_t;

    enum RESOURCE_POOL : __int32
    {
        RES_POOL_VIDEO,
        RES_POOL_COMBINED,
        RES_POOL_MEMORY,
        RES_POOL_MAX
    };

    struct VideoDevice
    {
        struct vft_s
        {
            void(__cdecl* Destructor)(VideoDevice* _this);
            int(__cdecl* GetDisplayWidth)(VideoDevice* _this);
            int(__cdecl* GetDisplayHeight)(VideoDevice* _this);
            int(__cdecl* GetDisplayFormat)(VideoDevice* _this);
            bool(__cdecl* IsWideScreen)(VideoDevice* _this);
            float(__cdecl* GetRefreshRate)(VideoDevice* _this);
        }*vft;
    };

    struct DX9_VideoDevice_Base : VideoDevice
    {
        LPDIRECT3D9 m_pD3D;
    };

    struct DX9_VideoDevice_PC : DX9_VideoDevice_Base
    {
        D3DDISPLAYMODE m_VideoMode;
    };

    struct DX9_DeviceCreator_Base
    {
        struct vft_s
        {
            bool(__cdecl* CreateD3DDevice)(DX9_DeviceCreator_Base* _this, const DeviceConfig_t*);
            void(__cdecl* FreeD3DDevice)(DX9_DeviceCreator_Base* _this, char flag);
        }*vft;

        LPDIRECT3D9 m_pD3D;
        LPDIRECT3DDEVICE9 m_pD3DDevice;
        D3DPRESENT_PARAMETERS m_D3DPP;
        int m_ShaderModel;
        int m_VideoMemorySize;
    };

    struct DeviceConfig_t
    {
        unsigned int m_BackBufferFormat;
        unsigned int m_DepthStencilFormat;
        unsigned int m_BackBufferWidth;
        unsigned int m_BackBufferHeight;
        HWND__* m_hWnd;
        bool m_IsFullScreen;
        bool m_IsVSyn;
        int m_RefreshRate;
        int m_Display;
        void* m_pUserData;
        int field_28;
    };

    struct RenderDeviceInitInfo_t
    {
        bool m_IsWindow;
        int m_BackBufferWidth;
        int m_BackBufferHeight;
        int m_BackBufferFormat;
        int m_DepthStencilFormat;
        int m_MultiSampleType;
        bool m_IsVSyn;
    };

    struct SamplerState_t
    {
        int m_MinFilter;
        int m_MagFilter;
        int m_MipFilter;
        int m_AddressU;
        int m_AddressV;
        int m_AddressW;
        int m_BorderColor;
    };

    template<typename T>
    struct ShaderParam
    {
        std::string m_Name;
        T m_Param;
        void* m_Handle;
        int m_SamplerIndex;
        bool m_IsUnused;
    };

    struct Sampler : SamplerState_t
    {
        struct vft_s
        {
            void(__thiscall* Destructor)(Sampler* _this);
        }*vft;

        std::string m_Name;
        Texture* m_pTexture;
        int m_Index;
    };

    template<typename T>
    struct TrieShaderParam
    {
        void* root;
        T* m_Container;
        unsigned int m_Size;
    };

    template<typename T>
    struct ShaderParamPool
    {
        TrieShaderParam<ShaderParam<T>*> m_Params;
    };

    struct ShaderParamData
    {
        ShaderParamPool<bool> m_BoolParamPool;
        ShaderParamPool<int> m_IntParamPool;
        ShaderParamPool<float> m_FloatParamPool;
        ShaderParamPool<Magic::MATH::Vector4<float> > m_VectorParamPool;
        ShaderParamPool<Magic::MATH::Matrix4<float> > m_MatrixParamPool;
        ShaderParamPool<Magic::RenderCore::Sampler*> m_SamplerParamPool;
    };

    struct GSphere_t
    {
        MATH::Vector3<float> m_Center;
        float m_Radius;
    };

    struct GBoundingBox_t
    {
        MATH::Vector3<float> m_Min;
        MATH::Vector3<float> m_Max;
    };

    struct GRect_t
    {
        float m_Left;
        float m_Top;
        float m_Right;
        float m_Bottom;
    };

    struct Resource
    {
        struct vft_s
        {
            void(__thiscall* Destructor)(Resource* _this, int a2);
            int(__thiscall* GetSize)(Resource* _this);
            bool(__thiscall* IsLoaded)(Resource* _this);
        }*vft;

        int m_ResType;
        int m_ResPool;
        void* m_pUserData;
        unsigned int m_ResMask;
        cppold::std::string m_Name;
        cppold::std::string m_Path;
    };

    struct VertexBuffer : Resource
    {
        enum PrimitiveType : __int32
        {
            PT_POINT_LIST,
            PT_LINE_LIST,
            PT_LINE_STRIP,
            PT_TRIANGLE_LIST,
            PT_TRIANGLE_STRIP,
            PT_TRIANGLE_FAN,
            PT_MAX
        };

        PrimitiveType m_PrimitiveType;
        int m_VertexNum;
        int m_VertexSize;
        bool m_IsLocked;
    };

    struct IndexBuffer : Resource
    {
        enum IndexSizeType : __int32
        {
            INDEX_SIZE_16,
            INDEX_SIZE_32
        };

        int m_IndexNum;
        int m_IndexSize;
        bool m_IsLocked;
    };

    struct ShaderStage : Resource
    {
        int m_ShaderStageType;
        void* m_ConstTableHandle;
        int m_ShaderCodeSize;
    };

    struct PixelShader : ShaderStage {};
    struct VertexShader : ShaderStage {};

    struct ShaderGroup
    {
        VertexShader* pVertexShader, m_pVS;
        PixelShader* m_pPS;
    };

    struct Material : Resource
    {
        int m_MaterialState;
        int m_AlphaRef;
        ShaderParamData m_ShaderParamData[2];
        VertexShader* pVertexShader, m_pVertexShader;
        PixelShader* m_pPixelShader;
    };

    struct Mesh : Resource
    {
        int m_IndexBase;
        int m_IndexCount;
        int m_VertexBase;
        int m_VertexCount;
        GBoundingBox_t m_BoundingBox;
        GSphere_t m_BoundingSphere;
        VertexBuffer* m_pVertexBuf;
        IndexBuffer* m_pIndexBuffer;
        Material* m_pMaterial;
        MATH::Matrix4<float> m_LocalTrans;
    };

    struct Texture : Resource
    {
        enum EType : __int32
        {
            TEX_1D,
            TEX_2D,
            TEX_CUBE,
            TEX_VOLUME,
            TYPE_MAX
        };

        enum EFlag : __int32
        {
            F_LINEAR,
            F_LITTLE_ENDIAN
        };


        enum EUsage : __int32
        {
            U_NORMAL,
            U_BACK_BUFFER,
            U_FRONT_BUFFER,
            U_RENDER_TARGET,
            U_DEPTH_STENCIL,
            U_MAX
        };

        int m_TexType;
        int m_TexSize;
        int m_TexFlags;
        int m_Width;
        int m_Height;
        int m_Depth;
        int m_Format;
        int m_Usage;
        int m_MipmapLevelCount;
        bool m_IsLocked;
    };

    struct MultiRenderTargets_t
    {
        Texture* m_RenderTarget0;
        Texture* m_RenderTarget1;
        Texture* m_RenderTarget2;
        Texture* m_RenderTarget3;
        Texture* m_DepthStencil;
    };

    struct InputElementDesc_t
    {
        int m_StreamIndex;
        int m_Offset;
        int m_Format;
        int m_Method;
        int m_SemanticName;
        int m_SemanticIndex;
    };

    struct InputLayout
    {
        struct vft_s
        {
            void(__thiscall* Destructor)(InputLayout* _this);
        }*vft;

        std::vector<InputElementDesc_t, std::allocator<InputElementDesc_t>> m_InputElements;
        void* m_pData;
        int m_StreamCount;
        int m_StreamSize[3];
        int m_UniqueID;
    };

    struct CallbackFunc // custom
    {
        void(__thiscall* Destructor)(CallbackFunc*, char flag);
        void(__fastcall* Function)(CallbackFunc*);
    };

    typedef CallbackFunc OnDeviceLostFunc;
    typedef CallbackFunc OnDeviceResetFunc;

    struct ResourceProfiler
    {
        struct vft_s
        {
            void(__cdecl* Destructor)(ResourceProfiler* _this);
        }*vft;

        std::list<Magic::RenderCore::Resource*> m_pResources[11];
    };

    struct RenderDevice
    {
        enum RenderState : __int32
        {
            RS_FILL_MODE,
            RS_SHADING_MODE,
            RS_CULLING_MODE,
            RS_Z_ENABLE,
            RS_Z_TEST_FUNC,
            RS_Z_WRITE_ENABLE,
            RS_ALPHA_TEST_ENABLE,
            RS_ALPHA_BLENDING_ENABLE,
            RS_ALPHA_BLENDING_SRC_FACTOR,
            RS_ALPHA_BLENDING_DST_FACTOR,
            RS_ALPHA_TEST_FUNC,
            RS_ALPHA_REF,
            RS_STENCIL_TEST_ENABLE,
            RS_STENCIL_TEST_FAIL,
            RS_STENCIL_TEST_ZFAIL,
            RS_STENCIL_TEST_PASS,
            RS_STENCIL_TEST_FUNC,
            RS_STENCIL_REF,
            RS_STENCIL_MASK,
            RS_STENCIL_WRITE_MASK,
            RS_COLORWRITEENABLE,
            RS_MULTISAMPLEANTIALIAS,
            RS_POINTSIZE,
            RS_MAX
        };

        enum ShadingMode : __int32
        {
            SM_FLAT,
            SM_GOURAUD,
            SM_MAX
        };

        enum CullingMode : __int32
        {
            CULL_NONE,
            CULL_CW,
            CULL_CCW,
            CULL_MAX
        };

        enum FillMode : __int32
        {
            FILLMODE_POINT,
            FILLMODE_WIREFRAME,
            FILLMODE_SOLID,
            FILLMODE_MAX
        };

        enum CmpFunc : __int32
        {
            CMP_NEVER,
            CMP_LESS,
            CMP_EQUAL,
            CMP_LESSEQUAL,
            CMP_GREATER,
            CMP_NOTEQUAL,
            CMP_GREATEREQUAL,
            CMP_ALWAYS,
            CMP_MAX
        };

        enum StencilOperator : __int32
        {
            STENCILOP_KEEP,
            STENCILOP_ZERO,
            STENCILOP_REPLACE,
            STENCILOP_INCRSAT,
            STENCILOP_DECRSAT,
            STENCILOP_INVERT,
            STENCILOP_INCR,
            STENCILOP_DECR,
            STENCILOP_MAX
        };

        enum ImageFileFormat : __int32
        {
            IFF_BMP,
            IFF_JPG,
            IFF_TGA,
            IFF_PNG,
            IFF_DDS,
            IFF_PPM,
            IFF_DIB,
            IFF_HDR,
            IFF_PFM,
            IFF_MAX
        };

        enum LockMode : __int32
        {
            LOCK_DEFAULT,
            LOCK_DISCARD,
            LOCK_READONLY,
            LOCK_NOOVERWRITE,
            LOCK_MAX
        };

        enum : __int32
        {
            SAMPLER_COUNT_MAX = 0x8
        };

        enum BlendMode : __int32
        {
            BM_ZERO,
            BM_ONE,
            BM_SRCCOLOR,
            BM_INVSRCCOLOR,
            BM_SRCALPHA,
            BM_INVSRCALPHA,
            BM_DESTALPHA,
            BM_INVDESTALPHA,
            BM_DESTCOLOR,
            BM_INVDESTCOLOR,
            BM_MAX
        };

        enum CubeMapFace : __int32
        {
            CUBEMAP_FACE_POSITIVE_X,
            CUBEMAP_FACE_NEGATIVE_X,
            CUBEMAP_FACE_POSITIVE_Y,
            CUBEMAP_FACE_NEGATIVE_Y,
            CUBEMAP_FACE_POSITIVE_Z,
            CUBEMAP_FACE_NEGATIVE_Z,
            CUBEMAP_FACE_MAX
        };

        enum ColorWriteMask : __int32
        {
            COLOR_MASK_R = 0x1,
            COLOR_MASK_G = 0x2,
            COLOR_MASK_B = 0x4,
            COLOR_MASK_A = 0x8,
            COLOR_MASK_ALL = COLOR_MASK_R | COLOR_MASK_G | COLOR_MASK_B | COLOR_MASK_A
        };

        enum RenderTargetType : __int32
        {
            RENDER_TARGET_0,
            RENDER_TARGET_1,
            RENDER_TARGET_2,
            RENDER_TARGET_3,
            RENDER_TARGET_MAX
        };

        enum FrameBufferType : uint32_t
        {
            FBT_COLOR = 0x1,
            FBT_DEPTH = 0x2,
            FBT_STENCIL = 0x4,
            FBT_MAX = 0xFFFFFFFF
        };

        enum MultiSampleType : __int32
        {
            MULTISAMPLE_NONE,
            MULTISAMPLE_2X,
            MULTISAMPLE_4X,
            MULTISAMPLE_MAX
        };

        struct vft_s
        {
            void(__thiscall* Destructor)(RenderDevice* _this, char flag);
            void(__thiscall* InitializeThing)(RenderDevice* _this);
            void(__thiscall* FreeThing)(RenderDevice* _this);
            void(__thiscall* GetRenderAPIName)(RenderDevice* _this, char*); // returns "directx_9"
            RenderDevice* (__thiscall* GetRenderAPI)(RenderDevice* _this);
            void(__thiscall* GetTextureCaps)(RenderDevice* _this, void* unknown_struct);
            int(__thiscall* GetVideoMemorySize)(RenderDevice* _this);
            int(__thiscall* GetShaderModel)(RenderDevice* _this);
            void(__thiscall* GetRenderDeviceInitInfo)(RenderDevice* _this, RenderDeviceInitInfo_t* pInfo);
            void(__thiscall* ResetRenderDeviceInitInfo)(RenderDevice* _this, RenderDeviceInitInfo_t* pInfo, OnDeviceLostFunc** lostFunc, OnDeviceResetFunc** resetFunc);
            void(__thiscall* BeginFrame)(RenderDevice* _this);
            void(__thiscall* EndFrame)(RenderDevice* _this);
            void(__thiscall* BeginRenderToTargets)(RenderDevice* _this, MultiRenderTargets_t* MRT);
            void(__thiscall* EndRenderToTargets)(RenderDevice* _this, bool flag);
            void(__thiscall* Present)(RenderDevice* _this);
            void(__thiscall* ClearFrameBuffer)(RenderDevice* _this, unsigned int type, unsigned int Color, float depth, unsigned int stencil);
            void(__thiscall* DrawPrimitive1)(RenderDevice* _this, InputLayout*, VertexBuffer*, int, int, IndexBuffer* pIndexBuf, int, int);
            void(__thiscall* DrawPrimitive2)(RenderDevice* _this, InputLayout*, Mesh*);
            void(__thiscall* DrawPrimitive3)(RenderDevice* _this, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);
            void(__thiscall* DrawPrimitiveInstance1)(RenderDevice* _this, InputLayout* pInputLayout, VertexBuffer*, int, int, IndexBuffer* pIndexBuf, int, int, VertexBuffer*, int, int, int);
            void(__thiscall* DrawPrimitiveInstance2)(RenderDevice* _this, InputLayout* pInputLayout, Mesh*, VertexBuffer* pVertexBuf);
            void(__thiscall* DrawPrimitiveDirectly)(RenderDevice* _this, InputLayout* pInputLayout, VertexBuffer::PrimitiveType primitiveType, int primitiveCount, void* pVertexData, int vertexSize, int);
            void(__thiscall* GetRenderState)(RenderDevice* _this, RenderState state, uint32_t* value);
            void(__thiscall* SetRenderState)(RenderDevice* _this, RenderState state, uint32_t value);
            void(__thiscall* GetRenderStateRaw)(RenderDevice* _this, RenderState state, uint32_t* rawValue);
            void(__thiscall* SetRenderStateRaw)(RenderDevice* _this, RenderState state, uint32_t rawValue);
            MATH::Vector4<float>* (__thiscall* GetViewport)(RenderDevice* _this, MATH::Vector4<float>* result);
            void(__thiscall* SetViewport)(RenderDevice* _this, const MATH::Vector4<float>* pRect);
            void(__thiscall* GetScissorRect)(RenderDevice* _this, const MATH::Vector4<float>* pRect);
            void(__thiscall* SetScissorRect)(RenderDevice* _this, const MATH::Vector4<float>* pRect);
            void(__thiscall* StoreDepthStencilSurface)(RenderDevice* _this, Texture* pTexture);
            void(__thiscall* LoadDepthStencilSurface)(RenderDevice* _this, Texture* pTexture);
            void(__thiscall* UnloadDepthStencilSurface)(RenderDevice* _this, Texture* pTexture);
            void(__thiscall* RestoreDepthStencilSurface)(RenderDevice* _this, Texture* pTexture);
            void(__thiscall* StoreRenderTarget)(RenderDevice* _this, int rtIndex, Texture* pTexture);
            void(__thiscall* LoadRenderTarget)(RenderDevice* _this, int rtIndex, Texture* pTexture);
            void(__thiscall* LoadCubeRenderTarget)(RenderDevice* _this, int rtIndex, Texture* pTexture, int iFace);
            void* Unknown37;
            void(__thiscall* UnloadRenderTarget)(RenderDevice* _this, int rtIndex, Texture* pTexture);
            void(__thiscall* RestoreRenderTarget)(RenderDevice* _this, int rtIndex, Texture* pTexture);
            void(__thiscall* LockShader)(RenderDevice* _this, const ShaderGroup* spShaders);
            void(__thiscall* UnlockShader)(RenderDevice* _this);
            bool(__thiscall* IsShaderLocked)(RenderDevice* _this);
            VertexShader* (__thiscall* GetVertexShader)(RenderDevice* _this);
            void(__thiscall* SetVertexShader)(RenderDevice* _this, VertexShader* pVertexShader);
            void(__thiscall* UnsetVertexShader)(RenderDevice* _this);
            PixelShader* (__thiscall* GetPixelShader)(RenderDevice* _this);
            void(__thiscall* SetPixelShader)(RenderDevice* _this, PixelShader* pPixelShader);
            void(__thiscall* UnsetPixelShader)(RenderDevice* _this);
            ShaderGroup* (__thiscall* GetShader)(RenderDevice* _this, ShaderGroup* result);
            void(__thiscall* SetShader1)(RenderDevice* _this, const ShaderGroup* spShaders);
            void(__thiscall* SetShader2)(RenderDevice* _this, VertexShader* pVertexShader, PixelShader* pPixelShader);
            void(__thiscall* UnsetShader)(RenderDevice* _this);
            void(__thiscall* ShaderSetConstant1)(RenderDevice* _this, ShaderStage* pShaderStage, const char* name, Sampler*, void**, int*);
            void(__thiscall* ShaderSetConstant2)(RenderDevice* _this, ShaderStage* pShaderStage, const char* name, const MATH::Matrix4<float>* value, void**);
            void(__thiscall* ShaderSetConstant3)(RenderDevice* _this, ShaderStage* pShaderStage, const char* name, const MATH::Vector4<float>* value, void**);
            void(__thiscall* ShaderSetConstant4)(RenderDevice* _this, ShaderStage* pShaderStage, const char* name, float, void**);
            void(__thiscall* ShaderSetConstant5)(RenderDevice* _this, ShaderStage* pShaderStage, const char* name, int, void**);
            void(__thiscall* ShaderSetConstant6)(RenderDevice* _this, ShaderStage* pShaderStage, const char* name, bool, void**);
            void(__thiscall* ShaderSetConstant7)(RenderDevice* _this, int, int, Texture* pTexture, const SamplerState_t*);
            void(__thiscall* ShaderSetConstant8)(RenderDevice* _this, int, int, const Magic::MATH::Matrix4<float>*);
            void(__thiscall* ShaderSetConstant9)(RenderDevice* _this, int, int, const Magic::MATH::Vector4<float>*);
            void(__thiscall* ShaderSetConstant10)(RenderDevice* _this, int, int, const float*, int);
            void(__thiscall* ShaderSetConstant11)(RenderDevice* _this, int, int, const int*, int);
            void(__thiscall* ShaderSetConstant12)(RenderDevice* _this, int, int, const bool*, int);
            bool(__thiscall* CheckDeviceLost)(RenderDevice* _this, OnDeviceLostFunc* lostFunc, OnDeviceResetFunc* resetFunc);
            void* Unknown66;
            void* Unknown67;
            void(__thiscall* SaveBackBufferToFile)(RenderDevice* _this, const std::string* name, ImageFileFormat imageFileFormat);
            void(__thiscall* BuildMipmaps)(RenderDevice* _this, Texture* pTexture);
            void(__thiscall* SetVerticalBlankCallback)(RenderDevice* _this, void(__cdecl* pCallback)(void*));
            bool(__thiscall* LoadInputLayout)(RenderDevice* _this, InputLayout* pInputLayout, InputElementDesc_t* elems);
            void(__thiscall* UnloadInputLayout)(RenderDevice* _this, InputLayout* pInputLayout);
            bool(__thiscall* LoadVertexBuffer)(RenderDevice* _this, VertexBuffer*, void* pRawData, int indexNum, int indexSize, RESOURCE_POOL pool);
            void(__thiscall* UnloadVertexBuffer)(RenderDevice* _this, VertexBuffer* pVertexBuf);
            bool(__thiscall* LockVertexBuffer)(RenderDevice* _this, VertexBuffer*, void** ppLockedData, int offset, int size, int lockFlag);
            void(__thiscall* UnlockVertexBuffer)(RenderDevice* _this, VertexBuffer* pVertexBuf);
            bool(__thiscall* LoadIndexBuffer)(RenderDevice* _this, IndexBuffer* pIndexBuf, void* pRawData, int indexNum, int indexSize, RESOURCE_POOL pool);
            void(__thiscall* UnloadIndexBuffer)(RenderDevice* _this, IndexBuffer* pIndexBuf);
            bool(__thiscall* LockIndexBuffer)(RenderDevice* _this, IndexBuffer* pIndexBuf, void** ppLockedData, int offset, int size, int lockFlag);
            void(__thiscall* UnlockIndexBuffer)(RenderDevice* _this, IndexBuffer* pIndexBuf);
            bool(__thiscall* CreateTexture)(RenderDevice* _this, Texture* pTexture, int texType, int* width, int* height, int* depth, int* format, int* mipLevels, RESOURCE_POOL* pool, int* flag);
            bool(__thiscall* LoadTexture)(RenderDevice* _this, Texture* pTexture, int textureType, void* pRawData, int size, int* width, int* height, int* depth, int* format, int* mipLevels, int* flag);
            void(__thiscall* UnloadTexture)(RenderDevice* _this, Texture* pTexture);
            bool(__thiscall* LockTexture)(RenderDevice* _this, Texture* pTexture, int mipmapLevel, void** ppLockedData, int* pPitch, GRect_t*, int lockFlag);
            void(__thiscall* UnlockTexture)(RenderDevice* _this, Texture* pTexture);
            int(__thiscall* GetLockedTexelOffset)(RenderDevice* _this, Texture* pTexture, int x, int y, int pitch, int mipmapLevel);
            bool(__thiscall* LoadVertexShader)(RenderDevice* _this, VertexShader* pVertexShader, void* pRawData, int size, int flag);
            void(__thiscall* UnloadVertexShader)(RenderDevice* _this, VertexShader* pVertexShader);
            bool(__thiscall* LoadPixelShader)(RenderDevice* _this, PixelShader* pPixelShader, void* pRawData, int size, int flag);
            void(__thiscall* UnloadPixelShader)(RenderDevice* _this, PixelShader* pPixelShader);
            bool(__thiscall* CopyTextureFromBackBuffer)(RenderDevice* _this, Texture* pDstTexture);
            bool(__thiscall* CopyTextureFromDepthStencilSurface)(RenderDevice* _this, Texture* pDstTexture);
            bool(__thiscall* CopyTextureFromRenderTarget)(RenderDevice* _this, Texture* pDstTexture, Texture* pSrcTexture);
            bool(__thiscall* CopyTextureFromTexture)(RenderDevice* _this, Texture* pDstTexture, Texture* pSrcTexture);
            bool(__thiscall* CreateDepthStencilSurface)(RenderDevice* _this, Texture* pTexture, int width, int height, int format, int* pool, int* flag);
            bool(__thiscall* CreateRenderTarget)(RenderDevice* _this, Texture* pTexture, int width, int height, int format, int* pool, int* flag);
            void(__thiscall* SaveTextureToFile)(RenderDevice* _this, const std::string* name, Texture* pTexture, ImageFileFormat imageFileFormat);
            void(__thiscall* ResetRenderStates)(RenderDevice* _this);
        }*vft;

        int m_ShaderLockCounter;
        Magic::RenderCore::ResourceProfiler* m_pResourceProfiler;
    };

    struct RenderTargetManager
    {
        RenderDevice* m_pRenderDevice;
        std::map<Magic::RenderCore::Texture*, LPDIRECT3DSURFACE9> m_RenderTargetMap;
        std::map<Magic::RenderCore::Texture*, LPDIRECT3DSURFACE9> m_DepthStencilMap;
        Magic::RenderCore::MultiRenderTargets_t m_CurrentMRT;
        Magic::RenderCore::MultiRenderTargets_t m_LastMRT;
    };

    struct RenderDevice_DX9 : RenderDevice
    {
        struct RenderResCache_t
        {
            LPDIRECT3DVERTEXDECLARATION9 m_pVertexDecl;
            LPDIRECT3DVERTEXBUFFER9 m_VertexBufferArray[4];
            LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
            LPDIRECT3DTEXTURE9 m_VSTextureArray[4];
            LPDIRECT3DTEXTURE9 m_PSTextureArray[16];
            LPDIRECT3DVERTEXSHADER9 m_pVertexShader;
            LPDIRECT3DPIXELSHADER9 m_pPixelShader;
        };

        char gap[4];

        int m_VideoMemorySize;
        int m_ShaderModel;
        RenderDeviceInitInfo_t m_InitInfo;
        DX9_DeviceCreator_Base* m_pDeviceCreator;
        LPDIRECT3DDEVICE9 m_pD3DDevice;
        std::map<Magic::RenderCore::Texture*, LPDIRECT3DSURFACE9> m_pLockedSurfaceMap;
        ShaderGroup* m_pShaderGroup;
        RenderDevice_DX9::RenderResCache_t m_RenderResCache;
        bool m_IsUseResCache;
        bool m_IsLockTail;
        std::map<Magic::RenderCore::IndexBuffer*, LPDIRECT3DVERTEXBUFFER9> m_IndexStreamSourceMap;
        Texture* m_pBackBufferScreenShotTex;
        RenderTargetManager* m_pRenderTargetManager;
    };
}

/************************/
/*  Data                */
/************************/
#define g_pRenderDevice     DATA_REF(Magic::RenderCore::RenderDevice_DX9*, 0x01A557C0)

#endif/*__cplusplus*/

#endif/*_MAGIC_RENDERCORE_H_*/

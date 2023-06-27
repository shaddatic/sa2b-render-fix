/*
*	Contains the calls to the d3d9 render device
*	
*/

#ifndef _MAGIC_RENDERDEVICE_H_
#define _MAGIC_RENDERDEVICE_H_

#include <list>

namespace Magic
{
	namespace RenderCore
	{
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

		struct OnDeviceLostFunc;
		struct MultiRenderTargets_t;
		struct InputLayout;
		struct VertexBuffer;
		struct IndexBuffer;

		struct Resource;

		struct /*VFT*/ RenderDevice_vtbl
		{
			void(__thiscall* dest_RenderDevice)(Magic::RenderCore::RenderDevice* ths);
			void(__thiscall* Init)(Magic::RenderCore::RenderDevice* ths);
			void(__thiscall* Exit)(Magic::RenderCore::RenderDevice* ths);
			void* (__thiscall* GetRenderAPI)(Magic::RenderCore::RenderDevice* ths);
			int(__thiscall* GetVideoMemorySize)(Magic::RenderCore::RenderDevice* ths);
			int(__thiscall* GetShaderModel)(Magic::RenderCore::RenderDevice* ths);
			void(__thiscall* GetRenderDeviceInitInfo)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::RenderDeviceInitInfo_t*);
			void(__thiscall* ResetRenderDeviceInitInfo)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::RenderDeviceInitInfo_t*, Magic::RenderCore::RenderDevice::OnDeviceLostFunc*, Magic::RenderCore::RenderDevice::OnDeviceResetFunc*);
			void(__thiscall* BeginFrame)(Magic::RenderCore::RenderDevice* ths);
			void(__thiscall* EndFrame)(Magic::RenderCore::RenderDevice* ths);
			void(__thiscall* BeginRenderToTargets)(Magic::RenderCore::RenderDevice* ths, const Magic::RenderCore::MultiRenderTargets_t*);
			void(__thiscall* EndRenderToTargets)(Magic::RenderCore::RenderDevice* ths, bool);
			void(__thiscall* Present)(Magic::RenderCore::RenderDevice* ths);
			void(__thiscall* ClearFrameBuffer)(Magic::RenderCore::RenderDevice* ths, unsigned int, unsigned int, float, unsigned int);
			void(__thiscall* DrawPrimitive)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::InputLayout*, Magic::RenderCore::VertexBuffer*, int, int, Magic::RenderCore::IndexBuffer*, int, int);
			void(__thiscall* DrawPrimitive)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::InputLayout*, Magic::RenderCore::Mesh*);
			void(__thiscall* DrawPrimitiveInstance)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::InputLayout*, Magic::RenderCore::VertexBuffer*, int, int, Magic::RenderCore::IndexBuffer*, int, int, Magic::RenderCore::VertexBuffer*, int, int, int);
			void(__thiscall* DrawPrimitiveInstance)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::InputLayout*, Magic::RenderCore::Mesh*, Magic::RenderCore::VertexBuffer*);
			void(__thiscall* DrawPrimitiveDirectly)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::InputLayout*, int, int, void*, int);
			void(__thiscall* GetRenderState)(Magic::RenderCore::RenderDevice* ths, unsigned int, unsigned int*);
			void(__thiscall* SetRenderState)(Magic::RenderCore::RenderDevice* ths, unsigned int, unsigned int);
			void(__thiscall* GetRenderStateRaw)(Magic::RenderCore::RenderDevice* ths, unsigned int, unsigned int*);
			void(__thiscall* SetRenderStateRaw)(Magic::RenderCore::RenderDevice* ths, unsigned int, unsigned int);
			Magic::MATH::Vector4<float>* (__thiscall* GetViewport)(Magic::RenderCore::RenderDevice* ths, Magic::MATH::Vector4<float>* result);
			void(__thiscall* SetViewport)(Magic::RenderCore::RenderDevice* ths, const Magic::MATH::Vector4<float>*);
			void(__thiscall* StoreDepthStencilSurface)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*);
			void(__thiscall* LoadDepthStencilSurface)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*);
			void(__thiscall* UnloadDepthStencilSurface)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*);
			void(__thiscall* RestoreDepthStencilSurface)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*);
			void(__thiscall* StoreRenderTarget)(Magic::RenderCore::RenderDevice* ths, int, Magic::RenderCore::Texture*);
			void(__thiscall* LoadRenderTarget)(Magic::RenderCore::RenderDevice* ths, int, Magic::RenderCore::Texture*);
			void(__thiscall* LoadCubeRenderTarget)(Magic::RenderCore::RenderDevice* ths, int, Magic::RenderCore::Texture*, int);
			void(__thiscall* UnloadRenderTarget)(Magic::RenderCore::RenderDevice* ths, int, Magic::RenderCore::Texture*);
			void(__thiscall* RestoreRenderTarget)(Magic::RenderCore::RenderDevice* ths, int, Magic::RenderCore::Texture*);
			void(__thiscall* LockShader)(Magic::RenderCore::RenderDevice* ths, const Magic::RenderCore::ShaderGroup*);
			void(__thiscall* UnlockShader)(Magic::RenderCore::RenderDevice* ths);
			bool(__thiscall* IsShaderLocked)(Magic::RenderCore::RenderDevice* ths);
			Magic::RenderCore::VertexShader* (__thiscall* GetVertexShader)(Magic::RenderCore::RenderDevice* ths);
			void(__thiscall* SetVertexShader)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::VertexShader*);
			void(__thiscall* UnsetVertexShader)(Magic::RenderCore::RenderDevice* ths);
			Magic::RenderCore::PixelShader* (__thiscall* GetPixelShader)(Magic::RenderCore::RenderDevice* ths);
			void(__thiscall* SetPixelShader)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::PixelShader*);
			void(__thiscall* UnsetPixelShader)(Magic::RenderCore::RenderDevice* ths);
			Magic::RenderCore::ShaderGroup* (__thiscall* GetShader)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::ShaderGroup* result);
			void(__thiscall* SetShader)(Magic::RenderCore::RenderDevice* ths, const Magic::RenderCore::ShaderGroup*);
			void(__thiscall* SetShader)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::VertexShader*, Magic::RenderCore::PixelShader*);
			void(__thiscall* UnsetShader)(Magic::RenderCore::RenderDevice* ths);
			void(__thiscall* ShaderSetConstant)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::ShaderStage*, const char*, Magic::RenderCore::Sampler*, void**, int*);
			void(__thiscall* ShaderSetConstant)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::ShaderStage*, const char*, const Magic::MATH::Matrix4<float>*, void**);
			void(__thiscall* ShaderSetConstant)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::ShaderStage*, const char*, const Magic::MATH::Vector4<float>*, void**);
			void(__thiscall* ShaderSetConstant)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::ShaderStage*, const char*, float, void**);
			void(__thiscall* ShaderSetConstant)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::ShaderStage*, const char*, int, void**);
			void(__thiscall* ShaderSetConstant)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::ShaderStage*, const char*, bool, void**);
			void(__thiscall* ShaderSetConstant)(Magic::RenderCore::RenderDevice* ths, int, int, Magic::RenderCore::Texture*, const Magic::RenderCore::SamplerState_t*);
			void(__thiscall* ShaderSetConstant)(Magic::RenderCore::RenderDevice* ths, int, int, const Magic::MATH::Matrix4<float>*);
			void(__thiscall* ShaderSetConstant)(Magic::RenderCore::RenderDevice* ths, int, int, const Magic::MATH::Vector4<float>*);
			void(__thiscall* ShaderSetConstant)(Magic::RenderCore::RenderDevice* ths, int, int, const float*, int);
			void(__thiscall* ShaderSetConstant)(Magic::RenderCore::RenderDevice* ths, int, int, const int*, int);
			void(__thiscall* ShaderSetConstant)(Magic::RenderCore::RenderDevice* ths, int, int, const bool*, int);
			bool(__thiscall* CheckDeviceLost)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::RenderDevice::OnDeviceLostFunc*, Magic::RenderCore::RenderDevice::OnDeviceResetFunc*);
			void(__thiscall* SaveBackBufferToFile)(Magic::RenderCore::RenderDevice* ths, const std::basic_string<char, std::char_traits<char>, std::allocator<char> >*, int);
			void(__thiscall* BuildMipmaps)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*);
			void(__thiscall* SetVerticalBlankCallback)(Magic::RenderCore::RenderDevice* ths, void(__thiscall*)(void*));
			bool(__thiscall* LoadInputLayout)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::InputLayout*, Magic::RenderCore::InputElementDesc_t*);
			void(__thiscall* UnloadInputLayout)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::InputLayout*);
			bool(__thiscall* LoadVertexBuffer)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::VertexBuffer*, void*, int, int, int);
			void(__thiscall* UnloadVertexBuffer)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::VertexBuffer*);
			bool(__thiscall* LockVertexBuffer)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::VertexBuffer*, void**, int, int, int);
			void(__thiscall* UnlockVertexBuffer)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::VertexBuffer*);
			bool(__thiscall* LoadIndexBuffer)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::IndexBuffer*, void*, int, int, int);
			void(__thiscall* UnloadIndexBuffer)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::IndexBuffer*);
			bool(__thiscall* LockIndexBuffer)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::IndexBuffer*, void**, int, int, int);
			void(__thiscall* UnlockIndexBuffer)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::IndexBuffer*);
			bool(__thiscall* CreateTexture)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*, int, int*, int*, int*, int*, int*, int*, int*);
			bool(__thiscall* LoadTexture)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*, int, void*, int, int*, int*, int*, int*, int*, int*);
			void(__thiscall* UnloadTexture)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*);
			bool(__thiscall* LockTexture)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*, int, void**, int*, Magic::RenderCore::GRect_t*, int);
			void(__thiscall* UnlockTexture)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*);
			int(__thiscall* GetLockedTexelOffset)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*, int, int, int, int);
			bool(__thiscall* LoadVertexShader)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::VertexShader*, void*, int, int);
			void(__thiscall* UnloadVertexShader)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::VertexShader*);
			bool(__thiscall* LoadPixelShader)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::PixelShader*, void*, int, int);
			void(__thiscall* UnloadPixelShader)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::PixelShader*);
			bool(__thiscall* CopyTextureFromBackBuffer)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*);
			bool(__thiscall* CopyTextureFromDepthStencilSurface)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*);
			bool(__thiscall* CopyTextureFromRenderTarget)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*, Magic::RenderCore::Texture*);
			bool(__thiscall* CopyTextureFromTexture)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*, Magic::RenderCore::Texture*);
			bool(__thiscall* CreateDepthStencilSurface)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*, int, int, int, int*, int*);
			bool(__thiscall* CreateRenderTarget)(Magic::RenderCore::RenderDevice* ths, Magic::RenderCore::Texture*, int, int, int, int*, int*);
			void(__thiscall* SaveTextureToFile)(Magic::RenderCore::RenderDevice* ths, const std::basic_string<char, std::char_traits<char>, std::allocator<char> >*, Magic::RenderCore::Texture*, int);
		};

		struct ResourceProfiler
		{
			Magic::RenderCore::ResourceProfiler_vtbl* __vftable /*VFT*/;
			std::list<Magic::RenderCore::Resource*, std::allocator<Magic::RenderCore::Resource*> > m_pResources[11];
		};


		struct RenderDevice
		{
			Magic::RenderCore::RenderDevice_vtbl* __vftable /*VFT*/;
			int m_ShaderLockCounter;
			Magic::RenderCore::ResourceProfiler* m_pResourceProfiler;
		};

	}
}

#endif /* _MAGIC_RENDERDEVICE_H_ */
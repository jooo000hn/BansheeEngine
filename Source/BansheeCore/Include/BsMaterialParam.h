//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsCorePrerequisites.h"
#include "BsGpuParam.h"

namespace BansheeEngine
{
	/** @addtogroup Implementation
	 *  @{
	 */

	class MaterialParams;
	class MaterialParamsCore;

	template<bool Core> struct TMaterialParamsType { };
	template<> struct TMaterialParamsType<false> { typedef MaterialParams Type; };
	template<> struct TMaterialParamsType<true> { typedef MaterialParamsCore Type; };

	/**
	 * A handle that allows you to set a Material parameter. Internally keeps a reference to the material parameters so that
	 * possibly expensive lookup of parameter name can be avoided each time the parameter is accessed, and instead the 
	 * handle can be cached.
	 * 			
	 * @note	
	 * This is pretty much identical to GPU parameter version (for example TGpuDataParam), except that this will get/set
	 * parameter values on all GPU programs attached to the material, while TGpuDataParam works only for single GPU
	 * program's parameters. Also, additional parameters that might be optimized out in the GPU program will still exist
	 * here as long as they're  defined in the shader used by the material, which is not the case with TGpuDataParam.
	 * @note
	 * For core-thread version of this class no shader-based caching is done, and instead this represents just a wrapper
	 * for multiple GPU parameters.
	 * 
	 * @see		Material
	 */
	template<class T, bool Core>
	class BS_CORE_EXPORT TMaterialDataParam
	{
		typedef typename TMaterialParamsType<Core>::Type MaterialParamsType;

	public:
		TMaterialDataParam(const String& name, const SPtr<MaterialParamsType>& params,
			const SPtr<Vector<TGpuDataParam<T, Core>>>& gpuParams);
		TMaterialDataParam() { }

		/** @copydoc TGpuDataParam::set */
		void set(const T& value, UINT32 arrayIdx = 0) const;

		/** @copydoc TGpuDataParam::get */
		T get(UINT32 arrayIdx = 0) const;

		/** Checks if param is initialized. */
		bool operator==(const nullptr_t& nullval) const
		{
			return mGPUParams == nullptr;
		}

	protected:
		UINT32 mParamIndex;
		UINT32 mArraySize;
		SPtr<MaterialParamsType> mMaterialParams;
		SPtr<Vector<TGpuDataParam<T, Core>>> mGPUParams;
	};
	
	/** @copydoc TMaterialDataParam */
	template<bool Core>
	class BS_CORE_EXPORT TMaterialParamStruct
	{
		typedef typename TMaterialParamsType<Core>::Type MaterialParamsType;

	public:
		TMaterialParamStruct(const String& name, const SPtr<MaterialParamsType>& params,
			const SPtr<Vector<TGpuParamStruct<Core>>>& gpuParams);
		TMaterialParamStruct() { }

		/** @copydoc TGpuParamStruct::set */
		void set(const void* value, UINT32 sizeBytes, UINT32 arrayIdx = 0) const;

		/** @copydoc TGpuParamStruct::get */
		void get(void* value, UINT32 sizeBytes, UINT32 arrayIdx = 0) const;

		/** @copydoc TGpuParamStruct::getElementSize */
		UINT32 getElementSize() const;

		/** Checks if param is initialized. */
		bool operator==(const nullptr_t& nullval) const
		{
			return mGPUParams == nullptr;
		}

	protected:
		UINT32 mParamIndex;
		UINT32 mArraySize;
		SPtr<MaterialParamsType> mMaterialParams;
		SPtr<Vector<TGpuParamStruct<Core>>> mGPUParams;
	};

	/** @copydoc TMaterialDataParam */
	template<bool Core>
	class BS_CORE_EXPORT TMaterialParamTexture
	{
		typedef typename TMaterialParamsType<Core>::Type MaterialParamsType;
		typedef typename TGpuParamTextureType<Core>::Type TextureType;

	public:
		TMaterialParamTexture(const String& name, const SPtr<MaterialParamsType>& params,
			const SPtr<Vector<TGpuParamTexture<Core>>>& gpuParams);
		TMaterialParamTexture() { }

		/** @copydoc GpuParamTexture::set */
		void set(const TextureType& texture) const;

		/** @copydoc GpuParamTexture::get */
		TextureType get() const;

		/** Checks if param is initialized. */
		bool operator==(const nullptr_t& nullval) const
		{
			return mGPUParams == nullptr;
		}

	protected:
		UINT32 mParamIndex;
		SPtr<MaterialParamsType> mMaterialParams;
		SPtr<Vector<TGpuParamTexture<Core>>> mGPUParams;
	};

	/** @copydoc TMaterialDataParam */
	template<bool Core>
	class BS_CORE_EXPORT TMaterialParamLoadStoreTexture
	{
		typedef typename TMaterialParamsType<Core>::Type MaterialParamsType;
		typedef typename TGpuParamTextureType<Core>::Type TextureType;

	public:
		TMaterialParamLoadStoreTexture(const String& name, const SPtr<MaterialParamsType>& params,
			const SPtr<Vector<TGpuParamLoadStoreTexture<Core>>>& gpuParams);
		TMaterialParamLoadStoreTexture() { }

		/** @copydoc GpuParamLoadStoreTexture::set */
		void set(const TextureType& texture, const TextureSurface& surface = TextureSurface()) const;

		/** @copydoc GpuParamLoadStoreTexture::get */
		TextureType get() const;

		/** Checks if param is initialized. */
		bool operator==(const nullptr_t& nullval) const
		{
			return mGPUParams == nullptr;
		}

	protected:
		UINT32 mParamIndex;
		SPtr<MaterialParamsType> mMaterialParams;
		SPtr<Vector<TGpuParamLoadStoreTexture<Core>>> mGPUParams;
	};
	
	/** @copydoc TMaterialDataParam */
	template<bool Core>
	class BS_CORE_EXPORT TMaterialParamBuffer
	{
		typedef typename TMaterialParamsType<Core>::Type MaterialParamsType;
		typedef typename TGpuBufferType<Core>::Type BufferType;

	public:
		TMaterialParamBuffer(const String& name, const SPtr<MaterialParamsType>& params,
			const SPtr<Vector<TGpuParamBuffer<Core>>>& gpuParams);
		TMaterialParamBuffer() { }

		/** @copydoc GpuParamBuffer::set */
		void set(const BufferType& buffer) const;

		/** @copydoc GpuParamBuffer::get */
		BufferType get() const;

		/** Checks if param is initialized. */
		bool operator==(const nullptr_t& nullval) const
		{
			return mGPUParams == nullptr;
		}

	protected:
		UINT32 mParamIndex;
		SPtr<MaterialParamsType> mMaterialParams;
		SPtr<Vector<TGpuParamBuffer<Core>>> mGPUParams;
	};

	/** @copydoc TMaterialDataParam */
	template<bool Core>
	class BS_CORE_EXPORT TMaterialParamSampState
	{
		typedef typename TMaterialParamsType<Core>::Type MaterialParamsType;
		typedef typename TGpuParamSamplerStateType<Core>::Type SamplerStateType;

	public:
		TMaterialParamSampState(const String& name, const SPtr<MaterialParamsType>& params,
			const SPtr<Vector<TGpuParamSampState<Core>>>& gpuParams);
		TMaterialParamSampState() { }

		/** @copydoc GpuParamSampState::set */
		void set(const SamplerStateType& sampState) const;

		/** @copydoc GpuParamSampState::get */
		SamplerStateType get() const;

		/** Checks if param is initialized. */
		bool operator==(const nullptr_t& nullval) const
		{
			return mGPUParams == nullptr;
		}

	protected:
		UINT32 mParamIndex;
		SPtr<MaterialParamsType> mMaterialParams;
		SPtr<Vector<TGpuParamSampState<Core>>> mGPUParams;
	};

	/** @} */

	/** @addtogroup Material
	 *  @{
	 */

	typedef TMaterialDataParam<float, false> MaterialParamFloat;
	typedef TMaterialDataParam<Vector2, false> MaterialParamVec2;
	typedef TMaterialDataParam<Vector3, false> MaterialParamVec3;
	typedef TMaterialDataParam<Vector4, false> MaterialParamVec4;
	typedef TMaterialDataParam<int, false> MaterialParamInt;
	typedef TMaterialDataParam<Vector2I, false> MaterialParamVec2I;
	typedef TMaterialDataParam<Vector3I, false> MaterialParamVec3I;
	typedef TMaterialDataParam<Vector4I, false> MaterialParamVec4I;
	typedef TMaterialDataParam<Matrix3, false> MaterialParamMat3;
	typedef TMaterialDataParam<Matrix4, false> MaterialParamMat4;
	typedef TMaterialDataParam<Color, false> MaterialParamColor;

	typedef TMaterialDataParam<float, true> MaterialParamFloatCore;
	typedef TMaterialDataParam<Vector2, true> MaterialParamVec2Core;
	typedef TMaterialDataParam<Vector3, true> MaterialParamVec3Core;
	typedef TMaterialDataParam<Vector4, true> MaterialParamVec4Core;
	typedef TMaterialDataParam<int, true> MaterialParamIntCore;
	typedef TMaterialDataParam<Vector2I, true> MaterialParamVec2ICore;
	typedef TMaterialDataParam<Vector3I, true> MaterialParamVec3ICore;
	typedef TMaterialDataParam<Vector4I, true> MaterialParamVec4ICore;
	typedef TMaterialDataParam<Matrix3, true> MaterialParamMat3Core;
	typedef TMaterialDataParam<Matrix4, true> MaterialParamMat4Core;
	typedef TMaterialDataParam<Color, true> MaterialParamColorCore;

	typedef TMaterialParamStruct<false> MaterialParamStruct;
	typedef TMaterialParamStruct<true> MaterialParamStructCore;

	typedef TMaterialParamTexture<false> MaterialParamTexture;
	typedef TMaterialParamTexture<true> MaterialParamTextureCore;

	typedef TMaterialParamLoadStoreTexture<false> MaterialParamLoadStoreTexture;
	typedef TMaterialParamLoadStoreTexture<true> MaterialParamLoadStoreTextureCore;

	typedef TMaterialParamBuffer<false> MaterialParamBuffer;
	typedef TMaterialParamBuffer<true> MaterialParamBufferCore;

	typedef TMaterialParamSampState<false> MaterialParamSampState;
	typedef TMaterialParamSampState<true> MaterialParamSampStateCore;

	/** @} */
}
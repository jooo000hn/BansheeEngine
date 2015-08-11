#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptObject.h"

namespace BansheeEngine
{
	/**
	 * @brief	Base interop class for any types deriving from RenderTarget.
	 */
	class BS_SCR_BE_EXPORT ScriptRenderTargetBase : public ScriptObjectBase
	{
	public:
		/**
		 * @brief	Returns the native render target this object wraps.
		 */
		virtual RenderTargetPtr getNativeValue() const = 0;

	protected:
		friend class ScriptResourceManager;

		ScriptRenderTargetBase(MonoObject* instance)
			:ScriptObjectBase(instance)
		{ }

		virtual ~ScriptRenderTargetBase() {}
	};

	/**
	 * @brief	Interop class between C++ & CLR for RenderTarget.
	 */
	class BS_SCR_BE_EXPORT ScriptRenderTarget : public ScriptObject<ScriptRenderTarget, ScriptRenderTargetBase>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "RenderTarget")

	private:
		ScriptRenderTarget(MonoObject* instance);

		/************************************************************************/
		/* 								CLR HOOKS						   		*/
		/************************************************************************/
		static void internal_getWidth(ScriptRenderTarget* thisPtr, int* value);
		static void internal_getHeight(ScriptRenderTarget* thisPtr, int* value);
		static void internal_getGammaCorrection(ScriptRenderTarget* thisPtr, bool* value);
		static void internal_getSampleCount(ScriptRenderTarget* thisPtr, int* value);
		static void internal_getPriority(ScriptRenderTarget* thisPtr, int* value);
		static void internal_setPriority(ScriptRenderTarget* thisPtr, int value);
	};
}
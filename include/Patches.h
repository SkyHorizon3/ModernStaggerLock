#pragma once
#include "DKUtil/Hook.hpp"

namespace ModernStaggerLock
{
	using namespace DKUtil::Alias;

	class StaggeredStateCheckPatch
	{
	public:
		static void Install()
		{
			REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(36700, 37710), REL::Relocate(0x55, 0x54) };  // 1-5-97-0 1405FA205
			REL::safe_write(target.address(), REL::NOP6, sizeof(REL::NOP6));

			INFO("{} Done!", __FUNCTION__);
		}

	private:
		StaggeredStateCheckPatch() = delete;
		~StaggeredStateCheckPatch() = delete;
	};
}
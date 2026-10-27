#pragma once

namespace ModernStaggerLock
{
	class StaggeredStateCheckPatch
	{
	public:
		static void Install()
		{
			REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(36700, 37710), REL::Relocate(0x55, 0x54) };  // 1-5-97-0 1405FA205
			REL::safe_write(target.address(), REL::NOP6, sizeof(REL::NOP6));

			SKSE::log::info("{} Done!", __FUNCTION__);
		}

	private:
		StaggeredStateCheckPatch() = delete;
		~StaggeredStateCheckPatch() = delete;
	};
}
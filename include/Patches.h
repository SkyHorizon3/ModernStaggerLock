#pragma once
#include "DKUtil/Hook.hpp"

namespace ModernStaggerLock
{
	using namespace DKUtil::Alias;

	class StaggeredStateCheckPatch
	{
		static constexpr OpCode NOP = 0x90;
		static constexpr OpCode StaggeredCheckNop[6]{ NOP, NOP, NOP, NOP, NOP, NOP };

	public:
		static void Install()
		{
			const auto funcAddr = RELOCATION_ID(36700, 37710).address();
			DKUtil::Hook::WriteData(funcAddr + REL::Relocate(0x55, 0x54), &StaggeredCheckNop, sizeof(StaggeredCheckNop), false);
			INFO("{} Done!", __FUNCTION__);
		}

	private:
		StaggeredStateCheckPatch() = delete;
		~StaggeredStateCheckPatch() = delete;
	};
}
#pragma once
#include "DKUtil/Hook.hpp"

namespace ModernStaggerLock
{
	using namespace DKUtil::Alias;

	class StaggeredStateCheckPatch
	{
		static constexpr OpCode NOP = 0x90;
		static constexpr OpCode StaggeredCheckNop[6]{ NOP, NOP, NOP, NOP, NOP, NOP };

		// 1-5-97-0 1405FA205
		//static constexpr std::uint64_t FuncID = 37710;  //SE 1-5-97-0: 1405fa1b0, ID: 36700; AE 1-6-640: 1406332E0, ID: 37710
		//static constexpr std::ptrdiff_t Offset = 0x55;

	public:
		static void Install()
		{
			const auto funcAddr = REL::RelocationID(36700, 37710).address();
			DKUtil::Hook::WriteData(funcAddr + REL::Relocate(0x55, 0x54, 0x55), &StaggeredCheckNop, sizeof(StaggeredCheckNop), false);
			INFO("{} Done!", __FUNCTION__);
		}

	private:
		StaggeredStateCheckPatch() = delete;
		~StaggeredStateCheckPatch() = delete;
	};
}
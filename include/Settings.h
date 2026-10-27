#pragma once

namespace ModernStaggerLock
{
	class MSLSettings : public REX::Singleton<MSLSettings>
	{
	public:
		std::vector<std::string> GetFiles();
		MSLSettings();

		bool DisableJumpWhenStagger{ true };
		float SmallStaggerMagnitude{ 0.0f };
		float MediumStaggerMagnitude{ 0.5f };
		float LargeStaggerMagnitude{ 0.75f };
		float LargestStaggerMagnitude{ 1.0f };

		enum StaggerType : std::int32_t
		{
			kSmall = 0,
			kMedium,
			kLarge,
			kLargest,
			kTotal
		};

		std::vector<std::string> quickRecoveryEvents;
	};
}
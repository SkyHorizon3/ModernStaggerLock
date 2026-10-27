#include "Settings.h"

namespace ModernStaggerLock
{
	using json = nlohmann::json;

	inline std::string tolower(std::string_view a_str)
	{
		std::string result(a_str);
		std::ranges::transform(result, result.begin(), [](unsigned char ch) { return static_cast<unsigned char>(std::tolower(ch)); });
		return result;
	}

	std::vector<std::string> MSLSettings::GetFiles()
	{
		std::vector<std::string> files;

		constexpr const char* PATH = "Data/SKSE/Plugins/ModernStaggerLock";
		if (!std::filesystem::exists(PATH))
			return files;

		for (const auto& entry : std::filesystem::directory_iterator(PATH)) {
			if (entry.is_regular_file()) {
				const auto jsonPath = tolower(entry.path().string());
				if (jsonPath.ends_with("_msl.json")) {
					files.emplace_back(jsonPath);
				}
			}
		}
		return files;
	}

	MSLSettings::MSLSettings()
	{
		const auto path = std::format("Data/SKSE/Plugins/{}.ini", Plugin::NAME);

		CSimpleIniA ini;
		ini.SetUnicode();
		ini.LoadFile(path.c_str());

		constexpr const char* sectionControl = "Control";
		DisableJumpWhenStagger = ini.GetBoolValue(sectionControl, "DisableJumpWhenStagger");

		constexpr const char* sectionStaggerLevel = "StaggerLevel";
		SmallStaggerMagnitude = std::clamp(static_cast<float>(ini.GetDoubleValue(sectionStaggerLevel, "SmallStaggerMagnitude")), 0.0f, 1.0f);
		MediumStaggerMagnitude = std::clamp(static_cast<float>(ini.GetDoubleValue(sectionStaggerLevel, "MediumStaggerMagnitude")), 0.0f, 1.0f);
		LargeStaggerMagnitude = std::clamp(static_cast<float>(ini.GetDoubleValue(sectionStaggerLevel, "LargeStaggerMagnitude")), 0.0f, 1.0f);
		LargestStaggerMagnitude = std::clamp(static_cast<float>(ini.GetDoubleValue(sectionStaggerLevel, "LargestStaggerMagnitude")), 0.0f, 1.0f);

		SKSE::log::info("Setting:\"{}\" is {}", "DisableJumpWhenStagger", DisableJumpWhenStagger);
		SKSE::log::info("Setting:\"{}\" is {}", "SmallStaggerMagnitude", SmallStaggerMagnitude);
		SKSE::log::info("Setting:\"{}\" is {}", "MediumStaggerMagnitude", MediumStaggerMagnitude);
		SKSE::log::info("Setting:\"{}\" is {}", "LargeStaggerMagnitude", LargeStaggerMagnitude);
		SKSE::log::info("Setting:\"{}\" is {}", "LargestStaggerMagnitude", LargestStaggerMagnitude);

		auto MSLFilesName = GetFiles();
		for (const auto& fileName : MSLFilesName) {
			try {
				json j = json::parse(std::ifstream(fileName));
				if (j.contains("QuickRecoveryEvents")) {
					auto eventLists = j.at("QuickRecoveryEvents").get<std::vector<std::string>>();
					quickRecoveryEvents.insert(quickRecoveryEvents.end(), eventLists.begin(), eventLists.end());
				}
			} catch (const json::exception& ex) {
				SKSE::log::error("Caught expection when parsing file \"{}\":\n {}", fileName, ex.what());
			}
		}

		for (const auto& eventName : quickRecoveryEvents) {
			SKSE::log::info("Got a Quick Recovery Event Name: \"{}\"", eventName);
		}
	}

}
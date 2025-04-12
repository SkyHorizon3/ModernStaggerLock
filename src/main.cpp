#include "LoadGame.h"

extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []() {
	SKSE::PluginVersionData v;
	v.PluginName(Plugin::NAME);
	v.PluginVersion(Plugin::VERSION);
	v.AuthorName("Maxsu and SkyHorizon"sv);
	v.UsesAddressLibrary();
	v.UsesNoStructs();

	return v;
}();

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface*, SKSE::PluginInfo* pluginInfo)
{
	pluginInfo->name = SKSEPlugin_Version.pluginName;
	pluginInfo->infoVersion = SKSE::PluginInfo::kVersion;
	pluginInfo->version = SKSEPlugin_Version.pluginVersion;
	return true;
}

DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	/*
#ifndef NDEBUG
	while (!IsDebuggerPresent()) {
		Sleep(100);
	}
#endif
	*/

	DKUtil::Logger::Init(Plugin::NAME, REL::Module::get().version().string());

	//REL::Module::reset();
	SKSE::Init(a_skse, false);

	if (REL::Module::IsSE()) {
		const auto message = std::format("Modern Stagger Lock AE is not compatible with version {} and below. Please use the original version.", a_skse->RuntimeVersion());
		SKSE::stl::report_and_fail(message);
	}

	INFO("{} v{} loaded", Plugin::NAME, Plugin::VERSION);

	// do stuff
	auto g_message = SKSE::GetMessagingInterface();
	if (!g_message) {
		ERROR("Messaging Interface Not Found!");
		return false;
	}

	g_message->RegisterListener(ModernStaggerLock::EventCallback);

	return true;
}

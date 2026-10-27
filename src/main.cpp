#include "LoadGame.h"

SKSE_PLUGIN_VERSION = []() {
	SKSE::PluginVersionData v;
	v.PluginName(Plugin::NAME);
	v.PluginVersion(Plugin::VERSION);
	v.AuthorName("Maxsu and SkyHorizon");
	v.UsesAddressLibrary();
	v.UsesNoStructs();
	return v;
}();

SKSE_PLUGIN_QUERY(const SKSE::QueryInterface*, SKSE::PluginInfo* pluginInfo)
{
	pluginInfo->name = SKSEPlugin_Version.pluginName;
	pluginInfo->infoVersion = SKSE::PluginInfo::kVersion;
	pluginInfo->version = SKSEPlugin_Version.pluginVersion;
	return true;
}

SKSE_PLUGIN_LOAD(const SKSE::LoadInterface* skse)
{
	/*
#ifndef NDEBUG
	while (!IsDebuggerPresent()) {
		Sleep(100);
	}
#endif
	*/

	SKSE::Init(skse, true);
	spdlog::set_pattern("[%H:%M:%S:%e] [%l] %v"s);

	SKSE::log::info("Game version: {}", skse->RuntimeVersion());

	auto message = SKSE::GetMessagingInterface();
	if (!message) {
		SKSE::log::error("Messaging Interface Not Found!");
		return false;
	}

	message->RegisterListener(ModernStaggerLock::EventCallback);

	return true;
}

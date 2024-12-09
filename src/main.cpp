#include "hooks.h"
#include "settings.h"

void InitListener(SKSE::MessagingInterface::Message* a_msg) 
{
	if (a_msg->type == SKSE::MessagingInterface::kDataLoaded) {
		Settings::LoadSettings();
		Settings::LoadForms();
		Hooks::InstallHooks();
	}
}

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);
	SKSE::GetMessagingInterface()->RegisterListener(InitListener);
	return true;
}

#include "hooks.h"
#include "settings.h"
#include "ui.h"

void InitListener(SKSE::MessagingInterface::Message* a_msg) 
{
	if (a_msg->type == SKSE::MessagingInterface::kDataLoaded) {
		Options::Forms::GetSingleton()->LoadForms();
	}
}

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);
	Options::Settings::GetSingleton()->Update();
	SKSE::GetMessagingInterface()->RegisterListener(InitListener);
	UI::Register();
	return true;
}

#include "affinity_service.h"


using namespace GTASA::SDK;
using namespace Logging;

namespace {
	AutoRegisterService<AffinityService> _autoRegister;
}

void AffinityService::onInit()
{
	// Set the process affinity to the first CPU core
	HANDLE hProcess = GetCurrentProcess();
	DWORD_PTR processAffinityMask = 1; // First CPU core
	if (SetProcessAffinityMask(hProcess, processAffinityMask)) {
		LOG_INFO("[AffinityService] Process affinity set to first CPU core.\n");
	}
	else {
		LOG_ERROR("[AffinityService] Failed to set process affinity.\n");
	}
}

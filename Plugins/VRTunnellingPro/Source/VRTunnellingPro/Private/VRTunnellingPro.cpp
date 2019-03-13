// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "VRTunnellingPro.h"

#define LOCTEXT_NAMESPACE "FVRTunnellingProModule"

void FVRTunnellingProModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FVRTunnellingProModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FVRTunnellingProModule, VRTunnellingPro)
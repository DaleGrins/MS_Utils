// Copyright Epic Games, Inc. All Rights Reserved.

#include "MetaSoundsSPL.h"
#include "MetasoundExecutableOperator.h"
#include "Internationalization/Text.h"
#include "MetasoundPrimitives.h"
#include "MetasoundTime.h"
#include "MetasoundNodeRegistrationMacro.h"


#define LOCTEXT_NAMESPACE "FMetaSoundsSPLModule"

void FMetaSoundsSPLModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FMetasoundFrontendRegistryContainer::Get()->RegisterPendingNodes();
}

void FMetaSoundsSPLModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMetaSoundsSPLModule, MetaSoundsSPL)
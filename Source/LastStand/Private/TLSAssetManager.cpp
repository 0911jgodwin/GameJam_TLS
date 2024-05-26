// Copyright JGodwin


#include "TLSAssetManager.h"
#include "AbilitySystemGlobals.h"

UTLSAssetManager& UTLSAssetManager::Get()
{
	check(GEngine);
	
	UTLSAssetManager* TLSAssetManager = Cast<UTLSAssetManager>(GEngine->AssetManager);
	return *TLSAssetManager;
}

void UTLSAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	// This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}
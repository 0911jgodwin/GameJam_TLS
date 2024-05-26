// Copyright JGodwin

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TLSAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API UTLSAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	UTLSAssetManager& Get();

protected:
	void StartInitialLoading();
};

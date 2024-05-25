// Copyright JGodwin

#pragma once

#include "CoreMinimal.h"
#include "Character/TLSCharacterBase.h"
#include "TLSEnemy.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ATLSEnemy : public ATLSCharacterBase
{
	GENERATED_BODY()
public:
	ATLSEnemy();
protected:
	virtual void BeginPlay() override;
};

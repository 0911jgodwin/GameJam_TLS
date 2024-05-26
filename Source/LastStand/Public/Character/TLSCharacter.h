// Copyright JGodwin

#pragma once

#include "CoreMinimal.h"
#include "Character/TLSCharacterBase.h"
#include "TLSCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ATLSCharacter : public ATLSCharacterBase
{
	GENERATED_BODY()
public:
	ATLSCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	virtual void InitAbilityActorInfo();
};

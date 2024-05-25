// Copyright JGodwin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TLSCharacterBase.generated.h"

UCLASS(Abstract)
class LASTSTAND_API ATLSCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ATLSCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};

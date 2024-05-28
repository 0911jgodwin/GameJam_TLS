// Copyright JGodwin

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/TLSAbilitySystemComponent.h"
#include "TLSGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API UTLSGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent;
};

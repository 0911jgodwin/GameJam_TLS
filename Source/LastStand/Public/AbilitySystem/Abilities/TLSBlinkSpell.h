// Copyright JGodwin

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TLSGameplayAbility.h"
#include "TLSBlinkSpell.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API UTLSBlinkSpell : public UTLSGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "Blink")
	void BlinkCharacter(const FVector& BlinkTargetLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Blink")
	void HideCharacter(AActor* Actor, bool Hidden);
};

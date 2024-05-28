// Copyright JGodwin

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TLSGameplayAbility.h"
#include "TLSProjectileSpell.generated.h"

class ATLSProjectile;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class LASTSTAND_API UTLSProjectileSpell : public UTLSGameplayAbility
{
	GENERATED_BODY()
protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ATLSProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};

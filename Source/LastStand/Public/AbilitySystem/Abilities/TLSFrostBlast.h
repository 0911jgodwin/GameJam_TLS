// Copyright JGodwin

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TLSGameplayAbility.h"
#include "TLSFrostBlast.generated.h"
class ATLSProjectile;
/**
 * 
 */
UCLASS()
class LASTSTAND_API UTLSFrostBlast : public UTLSGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	TArray<ATLSProjectile*> SpawnFrostBolts();
protected:

	UPROPERTY(EditDefaultsOnly, Category = "FrostBlast")
	int32 NumFrostBolts = 12;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATLSProjectile> FrostBoltClass;
};

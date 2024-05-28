// Copyright JGodwin


#include "AbilitySystem/Abilities/TLSFrostBlast.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/TLSAbilitySystemLibrary.h"
#include "Actor/TLSProjectile.h"

TArray<ATLSProjectile*> UTLSFrostBlast::SpawnFrostBolts()
{
	TArray<ATLSProjectile*> FrostBolts;
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FRotator> Rotators = UTLSAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, NumFrostBolts);

	for (const FRotator& Rotator : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotator.Quaternion());

		ATLSProjectile* FrostBolt = GetWorld()->SpawnActorDeferred<ATLSProjectile>(
			FrostBoltClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			CurrentActorInfo->PlayerController->GetPawn(),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
		FrostBolt->SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
		FrostBolt->DamageEffectSpecHandle = SpecHandle;

		FrostBolts.Add(FrostBolt);

		FrostBolt->FinishSpawning(SpawnTransform);
	}

	return FrostBolts;
}

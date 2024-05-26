// Copyright JGodwin


#include "AbilitySystem/Abilities/TLSProjectileSpell.h"
#include "Actor/TLSProjectile.h"

void UTLSProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UTLSProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	
	const FVector SpawnLocation = GetAvatarActorFromActorInfo()->GetActorLocation();

	FTransform SpawnTransform;
	FRotator Rotation = (ProjectileTargetLocation - SpawnLocation).Rotation();
	Rotation.Pitch = 0.f;
	SpawnTransform.SetLocation(SpawnLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());

	ATLSProjectile* Projectile = GetWorld()->SpawnActorDeferred<ATLSProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	//TODO: Give the Projectile a Gameplay Effect Spec for causing Damage.
	Projectile->FinishSpawning(SpawnTransform);
}

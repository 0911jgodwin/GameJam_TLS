// Copyright JGodwin


#include "AbilitySystem/Abilities/TLSBlinkSpell.h"

#include "Kismet/KismetSystemLibrary.h"

void UTLSBlinkSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UTLSBlinkSpell::BlinkCharacter(const FVector& BlinkTargetLocation)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	
	GetAvatarActorFromActorInfo()->SetActorLocation(BlinkTargetLocation);
}

void UTLSBlinkSpell::HideCharacter(AActor* Actor, bool Hidden)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	Actor->SetActorHiddenInGame(Hidden);
}

// Copyright JGodwin


#include "AbilitySystem/Abilities/TLSBlinkSpell.h"

void UTLSBlinkSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UTLSBlinkSpell::BlinkCharacter(const FVector& BlinkDirection, const float& BlinkDistance)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	
	const FVector StartLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	GetAvatarActorFromActorInfo()->SetActorLocation(StartLocation+(BlinkDirection*BlinkDistance));
}

void UTLSBlinkSpell::HideCharacter(AActor* Actor, bool Hidden)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	Actor->SetActorHiddenInGame(Hidden);
}

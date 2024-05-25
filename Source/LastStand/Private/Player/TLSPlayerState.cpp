// Copyright JGodwin


#include "Player/TLSPlayerState.h"
#include "AbilitySystem/TLSAbilitySystemComponent.h"
#include "AbilitySystem/TLSAttributeSet.h"

ATLSPlayerState::ATLSPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTLSAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UTLSAttributeSet>("AttributeSet");
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* ATLSPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

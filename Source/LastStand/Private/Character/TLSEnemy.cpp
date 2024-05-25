// Copyright JGodwin


#include "Character/TLSEnemy.h"
#include "AbilitySystem/TLSAbilitySystemComponent.h"
#include "AbilitySystem/TLSAttributeSet.h"

ATLSEnemy::ATLSEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTLSAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UTLSAttributeSet>("AttributeSet");
}

void ATLSEnemy::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
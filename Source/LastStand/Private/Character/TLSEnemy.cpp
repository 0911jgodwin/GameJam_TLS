// Copyright JGodwin


#include "Character/TLSEnemy.h"
#include "AbilitySystem/TLSAbilitySystemComponent.h"
#include "AbilitySystem/TLSAbilitySystemLibrary.h"
#include "AI/TLSAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystem/TLSAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

ATLSEnemy::ATLSEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTLSAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	AttributeSet = CreateDefaultSubobject<UTLSAttributeSet>("AttributeSet");
}

void ATLSEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!HasAuthority()) return;
	TLSAIController = Cast<ATLSAIController>(NewController);
	TLSAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	TLSAIController->RunBehaviorTree(BehaviorTree);
}

void ATLSEnemy::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* ATLSEnemy::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

void ATLSEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();
	AddCharacterAbilities();

	if (const UTLSAttributeSet* TLSAS = Cast<UTLSAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TLSAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TLSAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		OnHealthChanged.Broadcast(TLSAS->GetHealth());
		OnMaxHealthChanged.Broadcast(TLSAS->GetMaxHealth());
	}
}

void ATLSEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UTLSAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}

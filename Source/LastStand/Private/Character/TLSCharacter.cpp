// Copyright JGodwin


#include "Character/TLSCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/TLSPlayerController.h"
#include "Player/TLSPlayerState.h"
#include "UI/HUD/TLSHUD.h"

ATLSCharacter::ATLSCharacter()
{
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ATLSCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void ATLSCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void ATLSCharacter::InitAbilityActorInfo()
{
	ATLSPlayerState* TLSPlayerState = GetPlayerState<ATLSPlayerState>();
	check(TLSPlayerState);
	TLSPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(TLSPlayerState, this);
	AbilitySystemComponent = TLSPlayerState->GetAbilitySystemComponent();
	AttributeSet = TLSPlayerState->GetAttributeSet();

	if (ATLSPlayerController* TLSPlayerController = Cast<ATLSPlayerController>(GetController()))
	{
		if (ATLSHUD* TLSHUD = Cast<ATLSHUD>(TLSPlayerController->GetHUD()))
		{
			TLSHUD->InitOverlay(TLSPlayerController, TLSPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}

// Copyright JGodwin

#include "Player/TLSPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/TLSAbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/TLSInputComponent.h"

ATLSPlayerController::ATLSPlayerController()
{
	bReplicates = true;
}

void ATLSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(TLSContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(TLSContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ATLSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UTLSInputComponent* TLSInputComponent = CastChecked<UTLSInputComponent>(InputComponent);
	TLSInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATLSPlayerController::Move);
	TLSInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void ATLSPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ATLSPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
}

void ATLSPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void ATLSPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

UTLSAbilitySystemComponent* ATLSPlayerController::GetASC()
{
	if (TLSAbilitySystemComponent == nullptr)
	{
		TLSAbilitySystemComponent = Cast<UTLSAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return TLSAbilitySystemComponent;
}
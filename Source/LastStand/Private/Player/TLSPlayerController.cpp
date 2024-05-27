// Copyright JGodwin

#include "Player/TLSPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/TLSAbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/TLSInputComponent.h"
#include "Kismet/KismetMathLibrary.h"

ATLSPlayerController::ATLSPlayerController()
{
	bReplicates = true;
}

void ATLSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	Look();
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
	//const FRotator Rotation = GetControlRotation();
	const FRotator Rotation = PlayerCameraManager->GetCameraRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ATLSPlayerController::Look()
{
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		FVector MouseLocation, MouseDirection;
		DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
		FVector3d ActorLoc = ControlledPawn->GetActorLocation();
		FVector3d ActorFloor = FVector3d(ActorLoc.X, ActorLoc.Y, ActorLoc.Z-88);
		MouseDirection = MouseDirection * 1000000;
		FVector3d Intersection = FMath::LinePlaneIntersection(MouseLocation, MouseDirection, ActorFloor, FVector3d(0,0,1));
		ActorLoc.Z = 0;
		Intersection.Z = 0;
		FRotator LookAtDirection = UKismetMathLibrary::FindLookAtRotation(ActorLoc, Intersection);
		SetControlRotation(LookAtDirection);
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
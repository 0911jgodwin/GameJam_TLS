// Copyright JGodwin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "TLSPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UTLSInputConfig;
class UTLSAbilitySystemComponent;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class LASTSTAND_API ATLSPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATLSPlayerController();
	//virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> TLSContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UTLSInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UTLSAbilitySystemComponent> TLSAbilitySystemComponent;

	UTLSAbilitySystemComponent* GetASC();
};

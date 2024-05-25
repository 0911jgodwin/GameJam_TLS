// Copyright JGodwin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TLSPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
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
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> TLSContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);
};

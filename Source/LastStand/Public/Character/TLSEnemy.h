// Copyright JGodwin

#pragma once

#include "CoreMinimal.h"
#include "Character/TLSCharacterBase.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "TLSEnemy.generated.h"


class UBehaviorTree;
class ATLSAIController;
/**
 * 
 */
UCLASS()
class LASTSTAND_API ATLSEnemy : public ATLSCharacterBase
{
	GENERATED_BODY()
public:
	ATLSEnemy();
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ATLSAIController> TLSAIController;
};

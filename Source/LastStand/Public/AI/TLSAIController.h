// Copyright JGodwin

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TLSAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class LASTSTAND_API ATLSAIController : public AAIController
{
	GENERATED_BODY()
public:
	ATLSAIController();
protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};

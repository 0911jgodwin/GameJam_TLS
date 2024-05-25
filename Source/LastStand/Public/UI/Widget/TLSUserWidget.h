// Copyright JGodwin

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TLSUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API UTLSUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};

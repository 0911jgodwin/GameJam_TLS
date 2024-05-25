// Copyright JGodwin


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/TLSAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UTLSAttributeSet* TLSAttributeSet = CastChecked<UTLSAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(TLSAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(TLSAttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UTLSAttributeSet* TLSAttributeSet = CastChecked<UTLSAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		TLSAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		TLSAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

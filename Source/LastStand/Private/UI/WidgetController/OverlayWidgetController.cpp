// Copyright JGodwin


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/TLSAbilitySystemComponent.h"
#include "AbilitySystem/TLSAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UTLSAttributeSet* TLSAttributeSet = CastChecked<UTLSAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(TLSAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(TLSAttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UTLSAttributeSet* TLSAttributeSet = CastChecked<UTLSAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TLSAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TLSAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

	if (UTLSAbilitySystemComponent* TLSASC = Cast<UTLSAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (TLSASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(TLSASC);
		}
		else
		{
			TLSASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		}
	}
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UTLSAbilitySystemComponent* TLSAbilitySystemComponent)
{
	//TODO Get information about all given abilities, look up their Ability Info, and broadcast it to widgets.
	if (!TLSAbilitySystemComponent->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, TLSAbilitySystemComponent](const FGameplayAbilitySpec& AbilitySpec)
	{
		//TODO need a way to figure out the ability tag for a given ability spec.
		FTLSAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(TLSAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = TLSAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});
	TLSAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}
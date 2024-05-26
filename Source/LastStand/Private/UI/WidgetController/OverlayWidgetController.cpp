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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		TLSAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		TLSAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

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
		Cast<UTLSAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);
			}
		}
	);
	}
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
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
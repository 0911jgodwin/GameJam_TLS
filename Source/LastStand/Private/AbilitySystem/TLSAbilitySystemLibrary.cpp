// Copyright JGodwin


#include "AbilitySystem/TLSAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController/TLSWidgetController.h"
#include "Player/TLSPlayerState.h"
#include "UI/HUD/TLSHUD.h"

UOverlayWidgetController* UTLSAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ATLSHUD* TLSHUD = Cast<ATLSHUD>(PC->GetHUD()))
		{
			ATLSPlayerState* PS = PC->GetPlayerState<ATLSPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return TLSHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
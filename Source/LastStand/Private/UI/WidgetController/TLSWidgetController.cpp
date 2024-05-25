// Copyright JGodwin


#include "UI/WidgetController/TLSWidgetController.h"

void UTLSWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UTLSWidgetController::BroadcastInitialValues()
{
	
}

void UTLSWidgetController::BindCallbacksToDependencies()
{

}
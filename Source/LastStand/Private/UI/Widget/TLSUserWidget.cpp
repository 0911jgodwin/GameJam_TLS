// Copyright JGodwin


#include "UI/Widget/TLSUserWidget.h"

void UTLSUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

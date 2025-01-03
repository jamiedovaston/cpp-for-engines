#include "Widgets/Widget_HUD.h"

#include "ISkeletonTreeItem.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MANAGERS/GM_FPS.h"
#include "MANAGERS/GameRules/GameRule_Base.h"
#include "Pickups/Pickup.h"

void UWidget_HUD::NativeConstruct()
{
	Super::NativeConstruct();
 
	if(HealthBar) { HealthBar->SetPercent(0.f); }

	if(AmmoBar) { AmmoBar->SetPercent(0.f); }
}

void UWidget_HUD::UpdateHealth(float newHealthRatio)
{
	if(HealthBar) { HealthBar->SetPercent(newHealthRatio); }
}

void UWidget_HUD::UpdateAmmo(float newAmmoRatio)
{
	if(AmmoBar) { AmmoBar->SetPercent(newAmmoRatio); }
}

void UWidget_HUD::UpdateReloadBar(float newReloadRaio)
{
	if(ReloadBar) { ReloadBar->SetPercent(newReloadRaio); }
}

void UWidget_HUD::ActivateReloadBar(bool _active)
{
	ReloadBar->SetPercent(0.0f);
	ReloadBar->SetVisibility(_active ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UWidget_HUD::UpdateScore(int newScore)
{
	if(ScoreText)
	{
		UE_LOG(LogTemp,Warning,TEXT("Score updated!"));
		
		ScoreText->SetText(
		   FText::FromString(
			  FString::Printf(TEXT("Enemies Remaining: %d"), newScore)
		   )
		);
	}
}

void UWidget_HUD::UpdateWeaponHoverMenu(FString CurrentHoveredPickupName)
{
	if(!CurrentHoveredPickupName.IsEmpty())
	{
		UE_LOG(LogTemp, Display, TEXT("SHOWING TEXT"));
		WeaponPickupText->SetVisibility(ESlateVisibility::Visible);
		
		UE_LOG(LogTemp, Display, TEXT("UPDATED TEXT"));
    	WeaponPickupText->SetText(FText::FromString(CurrentHoveredPickupName));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("HIDDEN TEXT"));
		WeaponPickupText->SetVisibility(ESlateVisibility::Hidden);
	}
}

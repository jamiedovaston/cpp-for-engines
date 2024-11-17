#include "Widget_HUD.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HealthComponent.h"
 
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

void UWidget_HUD::UpdateScore(int newScore)
{
	if(ScoreText)
	{
		ScoreText->SetText(
		   FText::FromString(
			  FString::Printf(TEXT("Enemies Remaining: %d"), newScore)
		   )
		);
	}
}

#pragma once
 
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_HUD.generated.h"
 
class UTextBlock;
class UProgressBar;
class APickup;
 
UCLASS(Abstract, BlueprintType)
class PROJECT_API UWidget_HUD : public UUserWidget
{
	GENERATED_BODY()
 
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void UpdateHealth(float newHealthRatio);
	UFUNCTION()
	void UpdateAmmo(float newAmmoRatio);
	UFUNCTION()
	void UpdateScore(int newScore);
	UFUNCTION()
	void UpdateWeaponHoverMenu(FString CurrentHoveredPickup);
 
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> AmmoBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> WeaponPickupText;
};
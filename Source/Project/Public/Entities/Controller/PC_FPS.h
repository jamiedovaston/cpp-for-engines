﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Pickups/Pickup.h"
#include "PC_FPS.generated.h"

class UWidget_HUD;
struct FInputActionValue;
class UInputAction;

UCLASS(Abstract)
class PROJECT_API APC_FPS : public APlayerController
{
	GENERATED_BODY()

protected: // INPUT
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _LookAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _MoveAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _JumpAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _CrouchAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _SprintAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _FireAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _ReloadAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _InteractAction;

	virtual void SetupInputComponent() override;

	void Look(const FInputActionValue& value);
	
	void Move(const FInputActionValue& value);
	
	void JumpPressed();
	void JumpReleased();

	void CrouchPressed();
	void CrouchReleased();
	
	void SprintPressed();
	void SprintReleased();
	
	void FirePressed();
	void FireReleased();
	
	void ReloadPressed();
	
	void InteractPressed();
	void InteractReleased();

	UFUNCTION()
	void Handle_HoveredWeaponPickup(FString CurrentHoveredPickup);
	virtual void OnPossess(APawn* InPawn) override;
	
protected: // UI
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_HUD> _HUDWidgetClass;
	TObjectPtr<UWidget_HUD> _HUDWidget;
 
	virtual void BeginPlay() override;

	UFUNCTION()
	void Handle_HealthChangePercentage(float InPercent);
	
	UFUNCTION()
	void Handle_EnemiesRemainingChanged(int _remaining);

	UFUNCTION()
	void Handle_WeaponEquipped(AWeapon_Base* _weapon);
	
	UFUNCTION()
	void Handle_ReloadActive(bool _active);
	
	UFUNCTION()
	void Handle_ReloadTimer(float inPercent);
	
	UFUNCTION()
	void Handle_AmmoChangePercentage(float InPercent);
};

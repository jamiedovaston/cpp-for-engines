#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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
	TObjectPtr<UInputAction> _FireAction;

	virtual void SetupInputComponent() override;

	void Look(const FInputActionValue& value);
	
	void Move(const FInputActionValue& value);
	
	void JumpPressed();
	void JumpReleased();
	
	void FirePressed();
	void FireReleased();

	virtual void OnPossess(APawn* InPawn) override;
	
protected: // UI
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_HUD> _HUDWidgetClass;
	TObjectPtr<UWidget_HUD> _HUDWidget;
 
	virtual void BeginPlay() override;

	UFUNCTION()
	void Handle_HealthChangePercentage(float InPercent);
};

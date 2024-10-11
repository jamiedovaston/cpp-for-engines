﻿#pragma once

#include "CoreMinimal.h"
#include "Inputable.h"
#include "GameFramework/Character.h"
#include "P_FPS.generated.h"

class UHealthComponent;
class UCameraComponent;

UCLASS(Abstract)
class PROJECT_API AP_FPS : public ACharacter, public IInputable
{
	GENERATED_BODY()
	
public:
	AP_FPS();

	virtual void BeginPlay() override;
	
	virtual void Input_FirePressed_Implementation() override;
	virtual void Input_FireReleased_Implementation() override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_Look_Implementation(FVector2D value) override;
	virtual void Input_Move_Implementation(FVector2D value) override;
	
	virtual UInputMappingContext* GetMappingContext_Implementation() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	TObjectPtr<UHealthComponent> _Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;

private:
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
	UFUNCTION()
	void Handle_HealthDamaged(float currentHealth, float maxHealth, float change);
};
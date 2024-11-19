#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Inputable/Inputable.h"
#include "GameFramework/Character.h"
#include "P_FPS.generated.h"

class UHealthComponent;
class UCameraComponent;
class AWeapon_Base;
class UTimelineComponent;
class UCurveFloat;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthChangedPercentageSignature, float, InPercent);

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
	virtual void Input_CrouchPressed_Implementation() override;
	virtual void Input_CrouchReleased_Implementation() override;
	virtual void Input_SprintPressed_Implementation() override;
	virtual void Input_SprintReleased_Implementation() override;
	virtual void Input_Look_Implementation(FVector2D value) override;
	virtual void Input_Move_Implementation(FVector2D value) override;

	virtual UInputMappingContext* GetMappingContext_Implementation() override;

	UPROPERTY(BlueprintAssignable)
	FHealthChangedPercentageSignature OnHealthChangePercentage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AWeapon_Base> _WeaponRef;

	UFUNCTION()
	void Handle_OnPossessed();

    virtual UBehaviorTree* GetBehaviorTree_Implementation() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FOV")
	UCurveFloat* FOVCurve;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> _Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UHealthComponent> _Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float _WalkSpeed = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float _RunSpeed = 900.0f;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _WeaponAttachPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon_Base> _DefaultWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBehaviorTree> _BehaviorTree;

private:
	// Timeline and curve to control FOV
	UPROPERTY()
	UTimelineComponent* FOVTimeline;
	
	float DefaultFOV;
	float SprintFOV;

	UFUNCTION()
	void UpdateFOV(float Value);

	UFUNCTION()
	void Handle_HealthChangePercentage(float inPercent);
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
	UFUNCTION()
	void Handle_HealthDamaged(float currentHealth, float maxHealth, float change);
};

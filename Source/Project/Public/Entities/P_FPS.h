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
class APickup;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthChangedPercentageSignature, float, InPercent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCurrentWeaponPickupUpdatedSignature, FString, CurrentHoveredPickupText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponEquippedSignature, AWeapon_Base*, Weapon);

UCLASS(Abstract)
class PROJECT_API AP_FPS : public ACharacter, public IInputable
{
	GENERATED_BODY()

public:
	AP_FPS();

	virtual void BeginPlay() override;
	
	virtual void Input_FirePressed_Implementation() override;
	virtual void Input_FireReleased_Implementation() override;
	virtual void Input_ReloadPressed_Implementation() override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_CrouchPressed_Implementation() override;
	virtual void Input_CrouchReleased_Implementation() override;
	virtual void Input_SprintPressed_Implementation() override;
	virtual void Input_SprintReleased_Implementation() override;
	virtual void Input_InteractPressed_Implementation() override;
	virtual void Input_InteractReleased_Implementation() override;
	virtual void Input_Look_Implementation(FVector2D value) override;
	virtual void Input_Move_Implementation(FVector2D value) override;

	virtual UInputMappingContext* GetMappingContext_Implementation() override;

	UPROPERTY(BlueprintAssignable)
	FHealthChangedPercentageSignature OnHealthChangePercentage;
	
	UPROPERTY(BlueprintAssignable)
	FCurrentWeaponPickupUpdatedSignature OnHoveredWeaponPickupUpdated;

	UPROPERTY(BlueprintAssignable)
	FWeaponEquippedSignature OnWeaponEquipped;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AWeapon_Base> _WeaponRef;

	UFUNCTION()
	void Handle_OnPossessed();
	void Handle_Recoil(FVector2D recoil);

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
	TSubclassOf<APickup> _Pickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBehaviorTree> _BehaviorTree;

private:
	// Timeline and curve to control FOV
	UPROPERTY()
	UTimelineComponent* FOVTimeline;

	TArray<TObjectPtr<APickup>> CurrentPickupsHovering;
	
	float DefaultFOV;
	float SprintFOV;

	UFUNCTION()
	void UpdateFOV(float Value);
	UFUNCTION()
	void SetWeapon(TSubclassOf<AWeapon_Base> _weapon);
	UFUNCTION()
	void DropWeapon();

	UFUNCTION()
	void Handle_HealthChangePercentage(float inPercent);
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
	UFUNCTION()
	void Handle_HealthDamaged(float currentHealth, float maxHealth, float change);

	UFUNCTION()
	void Handle_ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void Handle_ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

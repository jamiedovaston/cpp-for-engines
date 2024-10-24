﻿#pragma once
 
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"

class UCameraComponent;
class UArrowComponent;
 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFireSignature);
 
UCLASS(Abstract)
class PROJECT_API AWeapon_Base : public AActor
{
	GENERATED_BODY()
 
public:
	AWeapon_Base();
 
	UPROPERTY(BlueprintAssignable)
	FWeaponFireSignature OnFire;
    
	void StartFire();
	void StopFire();
	
	UFUNCTION()
	virtual void Initialise(AActor* _Player, UCameraComponent* _Camera);
    
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> _Camera;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;
 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> _Mesh;
    
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _Muzzle;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _FireDelay;
	FTimerHandle _FireDelayTimer;
 
	UFUNCTION()
	virtual void Fire();
};
#pragma once
 
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"

class UCameraComponent;
class UArrowComponent;
 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFireSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAmmoChangedSignature, float, inPercent);

UCLASS(Abstract)
class PROJECT_API AWeapon_Base : public AActor
{
	GENERATED_BODY()
 
public:
	AWeapon_Base();
 
	UPROPERTY(BlueprintAssignable)
	FWeaponFireSignature OnFire;

	UPROPERTY(BlueprintAssignable)
	FAmmoChangedSignature OnAmmoChanged;
    
	void StartFire();
	void StopFire();

	static void SingleLineTraceHitResult(FHitResult& OutHit, const UObject* WorldContextObject,
		const FVector Start, const FVector End, const TArray<AActor*>& ActorsToIgnore);
	
	UFUNCTION()
	virtual void Initialise(AActor* _Player, UCameraComponent* _Camera);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString _WeaponName;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> _Mesh;
    
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> _Camera;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;
 
    
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _Muzzle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _FireDelay;
	FTimerHandle _FireDelayTimer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _MaxAmmoCount;
	int _CurrentAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _ReloadDelay;
	FTimerHandle _ReloadDelayTimer;

	bool CanShoot;
 
	UFUNCTION()
	virtual void Fire();
	
	UFUNCTION()
	void Reload();
};
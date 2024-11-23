#pragma once
 
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"

class UCameraComponent;
class UArrowComponent;
class UNiagaraSystem;
class AP_FPS;
 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFireSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAmmoChangedSignature, float, inPercent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReloadActiveSignature, bool, active);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReloadTimerSignature, float, inPercent);

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

	UPROPERTY(BlueprintAssignable)
	FReloadTimerSignature OnReloadTimer;

	UPROPERTY(BlueprintAssignable)
	FReloadActiveSignature OnReloadActive;

	virtual void StartFire();
	virtual void StopFire();
	void HandleReload();

	static void SingleLineTraceHitResult(FHitResult& OutHit, const UObject* WorldContextObject,
		const FVector Start, const FVector End, const TArray<AActor*>& ActorsToIgnore);
	
	UFUNCTION()
	virtual void Initialise(AP_FPS* _Player, UCameraComponent* _Camera, TSubclassOf<AWeapon_Base> _WeaponReference);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString _WeaponName;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> _Mesh;

	UPROPERTY()
	TSubclassOf<AWeapon_Base> _WeaponActorReference;
    
protected:
	UPROPERTY()
	AP_FPS* ControllingPlayer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* _MuzzleFlash;
	
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
	FTimerHandle _ReloadUpdateTimer;
	float _ReloadElapsedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _Recoil;
	
	bool CanShoot;
 
	UFUNCTION()
	virtual void Fire();
	UFUNCTION()
	void ReloadUpdate();
	UFUNCTION()
	void Reload();
};
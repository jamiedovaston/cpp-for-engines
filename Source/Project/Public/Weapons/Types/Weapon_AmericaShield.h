#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon_Base.h"
#include "Weapon_AmericaShield.generated.h"

class AProjectile_Shield;
class AProjectile;
class AP_FPS;
class UCameraComponent;
class UTargetComponent;

UCLASS()
class PROJECT_API AWeapon_AmericaShield : public AWeapon_Base
{
	GENERATED_BODY()

public:
	virtual void Initialise(AP_FPS* _Player, UCameraComponent* _Camera, TSubclassOf<AWeapon_Base> _WeaponReference) override;
	virtual void Fire() override;
	
	virtual void StartFire() override;
	virtual void StopFire() override;

	UFUNCTION()
	void PerformRaycast();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> ActorsToIgnore;
	FTimerHandle RaycastTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectile_Shield> _ShieldProjectile;

protected:
	UPROPERTY()
	TArray<UTargetComponent*> HighlightedEnemies;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectile> _ProjectileClass;
};

#pragma once
 
#include "CoreMinimal.h"
#include "Weapons/Weapon_Base.h"
#include "Weapon_Projectile.generated.h"
 
class AProjectile;

UCLASS(Abstract)
class PROJECT_API AWeapon_Projectile : public AWeapon_Base
{
	GENERATED_BODY()
 
public:
	virtual void Initialise(AP_FPS* _Player, UCameraComponent* _Camera, TSubclassOf<AWeapon_Base> _WeaponReference) override;
	virtual void Fire() override;
 
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> ActorsToIgnore;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectile> _ProjectileClass;
};
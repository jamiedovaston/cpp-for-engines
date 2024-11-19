#include "Weapons/Types/Weapon_Projectile.h"
 
#include "Components/ArrowComponent.h"
#include "Weapons/Projectile/Projectile.h"
#include "Camera/CameraComponent.h"
#include "Entities/P_FPS.h"
#include "Kismet/KismetMathLibrary.h"

void AWeapon_Projectile::Initialise(AP_FPS* _Player, UCameraComponent* _Camera)
{
	Super::Initialise(_Player, _Camera);
	
	ActorsToIgnore.Add(Cast<AActor>(_Player));
}

void AWeapon_Projectile::Fire()
{
	Super::Fire();
	
	if(!CanShoot) return;

	UWorld* const world = GetWorld();
	if(world == nullptr || _ProjectileClass == nullptr) { return; }
    
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	spawnParams.Instigator = GetInstigator();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	FHitResult hit(ForceInit);
	FVector start = _Camera->GetComponentLocation();
	FVector end = start + (_Camera->GetForwardVector() * 10000);
	
	FRotator projectileRotation; 
	
	SingleLineTraceHitResult(hit, world, start,end, ActorsToIgnore);
	
	projectileRotation = UKismetMathLibrary::FindLookAtRotation(_Muzzle->GetComponentLocation(), hit.IsValidBlockingHit() ? hit.ImpactPoint : end);
	FVector projectilePosition = _Muzzle->GetComponentLocation();
	
	world->SpawnActor(_ProjectileClass, &projectilePosition, &projectileRotation, spawnParams);
}

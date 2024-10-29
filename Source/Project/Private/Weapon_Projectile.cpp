#include "Weapon_Projectile.h"
 
#include "Components/ArrowComponent.h"
#include "Projectile.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void AWeapon_Projectile::Initialise(AActor* _Player, UCameraComponent* _Camera)
{
	Super::Initialise(_Player, _Camera);
	
	ActorsToIgnore.Add(_Player);
}

void AWeapon_Projectile::Fire()
{
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
	
	if(UKismetSystemLibrary::LineTraceSingle(world, start, end,
	   UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false,
	   ActorsToIgnore, EDrawDebugTrace::ForDuration, hit, true, FLinearColor::Red,
	   FLinearColor::Green, 5))
	{
		
	}
	
	projectileRotation = UKismetMathLibrary::FindLookAtRotation(_Muzzle->GetComponentLocation(), hit.IsValidBlockingHit() ? hit.ImpactPoint : end);
	FVector projectilePosition = _Muzzle->GetComponentLocation();
	
	world->SpawnActor(_ProjectileClass, &projectilePosition, &projectileRotation, spawnParams);
 
	Super::Fire();
}

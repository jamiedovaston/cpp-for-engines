#include "Weapons/Types/Weapon_Hitscan.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Entities/P_FPS.h"


void AWeapon_Hitscan::Initialise(AP_FPS* _Player, UCameraComponent* _Camera, TSubclassOf<AWeapon_Base> _WeaponReference)
{
	Super::Initialise(_Player, _Camera, _WeaponReference);

	ActorsToIgnore.Add(Cast<AActor>(_Player));
}

void AWeapon_Hitscan::Fire()
{
	Super::Fire();
	
	if(!CanShoot) return;

	UWorld* const world = GetWorld();
	if(world == nullptr) { return; }
 
	FHitResult hit(ForceInit);
	FVector start = _Camera->GetComponentLocation();
	FVector end = start + (_Camera->GetForwardVector() * 5000);
 
	SingleLineTraceHitResult(hit, world, start,end, ActorsToIgnore);
	
	UGameplayStatics::ApplyDamage(hit.GetActor(), _Damage,
	   GetOwner()->GetInstigatorController(), GetOwner(),
	   UDamageType::StaticClass());
    
	UE_LOG(LogTemp, Display, TEXT("Hit position: %s"), *hit.ImpactPoint.ToString())
}

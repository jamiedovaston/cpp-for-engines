﻿#include "Weapons/Types/Weapon_Hitscan.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

void AWeapon_Hitscan::Initialise(AActor* _Player, UCameraComponent* _Camera)
{
	Super::Initialise(_Player, _Camera);

	ActorsToIgnore.Add(_Player);
}

void AWeapon_Hitscan::Fire()
{
	Super::Fire();
	
	if(!CanShoot) return;
	
	UWorld* const world = GetWorld();
	if(world == nullptr) { return; }
 
	FHitResult hit(ForceInit);
	FVector start = _Camera->GetComponentLocation();
	FVector end = start + (_Camera->GetForwardVector() * 1000);
 
	SingleLineTraceHitResult(hit, world, start,end, ActorsToIgnore);
	
	UGameplayStatics::ApplyDamage(hit.GetActor(), _Damage,
	   GetOwner()->GetInstigatorController(), GetOwner(),
	   UDamageType::StaticClass());
    
	UE_LOG(LogTemp, Display, TEXT("Hit position: %s"), *hit.ImpactPoint.ToString())
}
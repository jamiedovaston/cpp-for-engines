#include "Weapons/Types/Weapon_AmericaShield.h"

#include "Camera/CameraComponent.h"
#include "Components/TargetComponent.h"
#include "Weapons/Projectile/Projectile.h"
#include "Entities/P_FPS.h"
#include "GameFramework/PlayerController.h"

void AWeapon_AmericaShield::Initialise(AP_FPS* _Player, UCameraComponent* _Camera,
	TSubclassOf<AWeapon_Base> _WeaponReference)
{
	Super::Initialise(_Player, _Camera, _WeaponReference);
	
	ActorsToIgnore.Add(Cast<AActor>(_Player));
}

void AWeapon_AmericaShield::Fire()
{
	Super::Fire();

	if (!CanShoot) return;

	UWorld* const world = GetWorld();
	if (world == nullptr || _ProjectileClass == nullptr) { return; }
}

void AWeapon_AmericaShield::StartFire()
{
	HighlightedEnemies.Empty();
	
	GetWorld()->GetTimerManager().SetTimer(
		RaycastTimerHandle, 
		this, 
		&AWeapon_AmericaShield::PerformRaycast, 
		0.1f,
		true
	);
}

void AWeapon_AmericaShield::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(RaycastTimerHandle);
	
	for (UTargetComponent* Enemy : HighlightedEnemies)
	{
		UE_LOG(LogTemp, Display, TEXT("Detected Enemy: %s"), *Enemy->GetName());
	}

	
}

void AWeapon_AmericaShield::PerformRaycast()
{
	if (!_Camera) return;
	
	UWorld* const world = GetWorld();
	if(world == nullptr) { return; }

	FHitResult hit(ForceInit);
	FVector start = _Camera->GetComponentLocation();
	FVector end = start + (_Camera->GetForwardVector() * 5000);

	SingleLineTraceHitResult(hit, world, start,end, ActorsToIgnore);

	if (AActor* HitActor = hit.GetActor())
	{
		if (IsValid(HitActor))
		{
			if (ActorsToIgnore.Contains(HitActor))
			{
				return;
			}

			if (UTargetComponent* TargetComponent = HitActor->FindComponentByClass<UTargetComponent>())
			{
				if (!HighlightedEnemies.Contains(TargetComponent))
				{
					HighlightedEnemies.Add(TargetComponent);
					
					TargetComponent->Highlight(true);
				}
			}
		}
	}
}




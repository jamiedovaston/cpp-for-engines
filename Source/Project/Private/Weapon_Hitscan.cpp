#include "Weapon_Hitscan.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AWeapon_Hitscan::Initialise(AActor* _Player, UCameraComponent* _Camera)
{
	Super::Initialise(_Player, _Camera);

	ActorsToIgnore.Add(_Player);
}

void AWeapon_Hitscan::Fire()
{
	UWorld* const world = GetWorld();
	if(world == nullptr) { return; }
 
	FHitResult hit(ForceInit);
	FVector start = _Camera->GetComponentLocation();
	FVector end = start + (_Camera->GetForwardVector() * 1000);
 
	if(UKismetSystemLibrary::LineTraceSingle(world, start, end,
	   UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false,
	   ActorsToIgnore, EDrawDebugTrace::ForDuration, hit, true, FLinearColor::Red,
	   FLinearColor::Green, 5))
	{
		UGameplayStatics::ApplyDamage(hit.GetActor(), _Damage,
		   GetOwner()->GetInstigatorController(), GetOwner(),
		   UDamageType::StaticClass());
        
		UE_LOG(LogTemp, Display, TEXT("Hit position: %s"), *hit.ImpactPoint.ToString())
	}
 
	Super::Fire();
}

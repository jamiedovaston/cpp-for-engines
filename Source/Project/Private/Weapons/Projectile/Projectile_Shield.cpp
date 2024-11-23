#include "Weapons/Projectile/Projectile_Shield.h"

#include "Components/TargetComponent.h"
#include "Kismet/GameplayStatics.h"

void AProjectile_Shield::Initialise(TArray<UTargetComponent*>* _highlighted)
{
	HighlightedEnemies = _highlighted;
}

void AProjectile_Shield::Handle_Hit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                    FVector NormalImpulse, const FHitResult& Hit)
{
	if((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if(UTargetComponent* target = Cast<UTargetComponent>(OtherActor))
		{
			if(HighlightedEnemies->GetData()[0] == target)
			{
				UGameplayStatics::ApplyDamage(OtherActor, _Damage, GetInstigatorController(), this, UDamageType::StaticClass());
				HighlightedEnemies->RemoveAt(0);
				Reflect(HighlightedEnemies->GetData()[0]);
			}
		}
	}
}

void AProjectile_Shield::Reflect(UTargetComponent* target)
{
	// rotate towards target (ensure movement rotates too)
}


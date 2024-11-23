// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Projectile_Shield.generated.h"

class UTargetComponent;

UCLASS()
class PROJECT_API AProjectile_Shield : public AProjectile
{
	GENERATED_BODY()

public:
	void Initialise(TArray<UTargetComponent*>* _highlighted);
	
protected:
	virtual void Handle_Hit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
private:
	TArray<UTargetComponent*>* HighlightedEnemies;

	void Reflect(UTargetComponent* target);
};

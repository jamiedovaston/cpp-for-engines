﻿#pragma once
 
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"
 
class UProjectileMovementComponent;
class USphereComponent;
 
UCLASS(Abstract)
class PROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
 
public:
	AProjectile();
 
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> _Collider;
 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> _ProjectileMovement;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _Damage;
 
private:
	UFUNCTION()
	void Handle_Hit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class AWeapon_Base;
class USkeletalMeshComponent;
class USphereComponent;

UCLASS()
class PROJECT_API APickup : public AActor
{
	GENERATED_BODY()
	
public:
	APickup();
	void SetWeaponReference(TSubclassOf<AWeapon_Base> _Weapon);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TSubclassOf<AWeapon_Base> _WeaponReference;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<USkeletalMeshComponent> Mesh; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<USphereComponent> SphereCollision;

	void SetupMesh();
public:
	TSubclassOf<AWeapon_Base> GetWeapon();
};

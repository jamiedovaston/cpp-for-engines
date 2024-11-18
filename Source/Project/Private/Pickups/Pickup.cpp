#include "Pickups/Pickup.h"

#include "Weapons/Weapon_Base.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CoreMinimal.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create the Skeletal Mesh component and attach it to the root
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	
    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
    SphereCollision->InitSphereRadius(100.0f);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	// Set up the mesh based on the WeaponReference
	SetupMesh();
}

void APickup::SetupMesh()
{
	if (AWeapon_Base* DefaultWeapon = _WeaponReference->GetDefaultObject<AWeapon_Base>())
	{
		// This includes inherited or overridden values
		UE_LOG(LogTemp, Display, TEXT("=================================================================== Weapon Name: %s"), *DefaultWeapon->_WeaponName);

		Mesh->SetSkeletalMeshAsset(DefaultWeapon->_Mesh->GetSkeletalMeshAsset());
	}
}

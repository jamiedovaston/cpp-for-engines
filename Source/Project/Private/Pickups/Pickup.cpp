#include "Pickups/Pickup.h"

#include "Weapons/Weapon_Base.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CoreMinimal.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create and initialize the root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent->SetupAttachment(RootComponent); // Attach root to itself (basic setup)

	// Create and initialize the mesh component
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent); // Attach mesh to root component

	// Create and initialize the sphere collision component
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(Mesh); // Attach collision to mesh
	SphereCollision->InitSphereRadius(100.0f); // Optional: Set the collision radius
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	SetupMesh();
}

void APickup::SetupMesh()
{
	if (AWeapon_Base* DefaultWeapon = _WeaponReference->GetDefaultObject<AWeapon_Base>())
	{
		UE_LOG(LogTemp, Display, TEXT("=================================================================== Weapon Name: %s"), *DefaultWeapon->_WeaponName);
		Mesh->SetSkeletalMeshAsset(DefaultWeapon->_Mesh->GetSkeletalMeshAsset());
	}
}

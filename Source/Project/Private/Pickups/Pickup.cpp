#include "Pickups/Pickup.h"

#include "Weapons/Weapon_Base.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CoreMinimal.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Root->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root); 

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(Mesh); 
	SphereCollision->InitSphereRadius(100.0f); 
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

void APickup::SetWeaponReference(TSubclassOf<AWeapon_Base> _Weapon)
{
	_WeaponReference = _Weapon;
	SetupMesh();
}

TSubclassOf<AWeapon_Base> APickup::GetWeapon()
{
	return _WeaponReference;
}

#include "Weapon_Base.h"

#include "Components/ArrowComponent.h"

AWeapon_Base::AWeapon_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	_FireDelay = 0.f;
 
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;
 
	_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);
 
	_Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Muzzle->SetupAttachment(_Mesh);
}
 
void AWeapon_Base::StartFire()
{
	Fire();
	if(_FireDelay != 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(_FireDelayTimer, this, &AWeapon_Base::Fire, _FireDelay, true);
	}
}
 
void AWeapon_Base::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(_FireDelayTimer);
}

void AWeapon_Base::SingleLineTraceHitResult(FHitResult& OutHit, const UObject* WorldContextObject, const FVector Start, const FVector End, const TArray<AActor*>& ActorsToIgnore)
{
	UKismetSystemLibrary::LineTraceSingle(WorldContextObject, Start, End,
	   UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit,
	   true, FLinearColor::Red, FLinearColor::Green, 5);
}

void AWeapon_Base::Initialise(AActor* _Player, UCameraComponent* camera)
{
	_Camera = camera;
	
	_CurrentAmmo = _MaxAmmoCount;
	OnAmmoChanged.Broadcast((float)_CurrentAmmo / (float)_MaxAmmoCount);
	CanShoot = true;
}

void AWeapon_Base::Fire()
{
	if(!CanShoot) return;
	
	if(_CurrentAmmo > 0)
	{
		OnFire.Broadcast();
		_CurrentAmmo--;
		OnAmmoChanged.Broadcast((float)_CurrentAmmo / (float)_MaxAmmoCount);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(_ReloadDelayTimer, this, &AWeapon_Base::Reload, _ReloadDelay, false);
		CanShoot = false;
	}
}

void AWeapon_Base::Reload()
{
	_CurrentAmmo = _MaxAmmoCount;
	OnAmmoChanged.Broadcast((float)_CurrentAmmo / (float)_MaxAmmoCount);
	CanShoot = true;
}

#include "Weapons/Weapon_Base.h"

#include "Components/ArrowComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h" 
#include "Entities/P_FPS.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

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

void AWeapon_Base::HandleReload()
{
	CanShoot = false;
	GetWorld()->GetTimerManager().SetTimer(_ReloadDelayTimer, this, &AWeapon_Base::Reload, _ReloadDelay, false);
}

void AWeapon_Base::SingleLineTraceHitResult(FHitResult& OutHit, const UObject* WorldContextObject, const FVector Start, const FVector End, const TArray<AActor*>& ActorsToIgnore)
{
	UKismetSystemLibrary::LineTraceSingle(WorldContextObject, Start, End,
	   UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit,
	   true, FLinearColor::Red, FLinearColor::Green, 5);
}

void AWeapon_Base::Initialise(AP_FPS* _Player, UCameraComponent* camera)
{
	ControllingPlayer = _Player;
	
	_Camera = camera;
	
	_CurrentAmmo = _MaxAmmoCount;
	OnAmmoChanged.Broadcast(1.0f);
	CanShoot = true;
}

void AWeapon_Base::Fire()
{
	if(!CanShoot) return;
	
	if(_CurrentAmmo > 0)
	{
		if (_MuzzleFlash)
		{
			FVector MuzzleLocation = _Muzzle->GetComponentLocation();
			FRotator MuzzleRotation = _Muzzle->GetComponentRotation();

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _MuzzleFlash,
				MuzzleLocation, MuzzleRotation, FVector(1.0f), true, true, ENCPoolMethod::AutoRelease);
		}
		
		float FinalRecoilY = _Recoil * FMath::FRandRange(1.0f, 1.25f);
		float FinalRecoilX = _Recoil * FMath::FRandRange(-1.0f, 1.0f);
		ControllingPlayer->Handle_Recoil(FVector2D(FinalRecoilX / 2, FinalRecoilY));
		
		OnFire.Broadcast();
		_CurrentAmmo--;
		OnAmmoChanged.Broadcast((float)_CurrentAmmo / (float)_MaxAmmoCount);
	}
	else
	{
		CanShoot = false;
	}
}

void AWeapon_Base::Reload()
{
	_CurrentAmmo = _MaxAmmoCount;
	OnAmmoChanged.Broadcast((float)_CurrentAmmo / (float)_MaxAmmoCount);
	CanShoot = true;
}

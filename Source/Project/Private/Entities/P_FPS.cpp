#include "Entities/P_FPS.h"
#include "Components/HealthComponent.h"
#include "Weapons/Weapon_Base.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "Pickups/Pickup.h"

AP_FPS::AP_FPS()
{
	PrimaryActorTick.bCanEverTick = true;

	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);

	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	_WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Attach"));
	_WeaponAttachPoint->SetupAttachment(_Camera);

	DefaultFOV = 90.0f;
	SprintFOV = 110.0f;

	FOVTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("FOVTimeline"));
	FOVTimeline->SetPlayRate(3.0f);
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &AP_FPS::Handle_ComponentBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddUniqueDynamic(this, &AP_FPS::Handle_ComponentEndOverlap);
}

void AP_FPS::BeginPlay()
{
	Super::BeginPlay();
	
	_Camera->SetFieldOfView(DefaultFOV);

	// Check if FOVCurve is valid
	if (FOVCurve)
	{
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("UpdateFOV"));
		FOVTimeline->AddInterpFloat(FOVCurve, ProgressFunction);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FOVCurve is not assigned in the Editor!"));
	}

	// Initialize Weapon
	if (_DefaultWeapon)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = this;
		_WeaponRef = GetWorld()->SpawnActor<AWeapon_Base>(_DefaultWeapon, _WeaponAttachPoint->GetComponentTransform(), spawnParams);
		_WeaponRef->AttachToComponent(_WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
		_WeaponRef->Initialise(this, _Camera);
	}
}

void AP_FPS::Input_FirePressed_Implementation()
{
	if(_WeaponRef)
	{
		_WeaponRef->StartFire();
	}
}

void AP_FPS::Input_FireReleased_Implementation()
{
	if(_WeaponRef)
	{
		_WeaponRef->StopFire();
	}
}

void AP_FPS::Input_ReloadPressed_Implementation()
{
	if(_WeaponRef)
	{
		_WeaponRef->HandleReload();
	}
}

void AP_FPS::Input_JumpPressed_Implementation()
{
	ACharacter::Jump();
}

void AP_FPS::Input_JumpReleased_Implementation()
{
	ACharacter::StopJumping();
}

void AP_FPS::Input_CrouchPressed_Implementation()
{
	ACharacter::Crouch();
}

void AP_FPS::Input_CrouchReleased_Implementation()
{
	ACharacter::UnCrouch();
}

void AP_FPS::Input_SprintPressed_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = _RunSpeed;

	if (FOVTimeline)
	{
		FOVTimeline->PlayFromStart();
	}
}

void AP_FPS::Input_SprintReleased_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = _WalkSpeed;

	if (FOVTimeline)
	{
		FOVTimeline->ReverseFromEnd();
	}
}

void AP_FPS::Input_Look_Implementation(FVector2D value)
{
	AddActorWorldRotation(FRotator(0.0f, value.X, 0.0f));
	_Camera->AddLocalRotation(FRotator(value.Y, 0.0f, 0.0f));
}

void AP_FPS::Input_Move_Implementation(FVector2D value)
{
	AddMovementInput(FVector::VectorPlaneProject(_Camera->GetForwardVector(), FVector::UpVector)
		.GetSafeNormal(), value.Y);
	AddMovementInput(GetActorRightVector(), value.X);
}

UInputMappingContext* AP_FPS::GetMappingContext_Implementation()
{
	return _InputMapping;
}

void AP_FPS::Handle_HealthChangePercentage(float inPercent)
{
	OnHealthChangePercentage.Broadcast(inPercent);
}

void AP_FPS::UpdateFOV(float Value)
{
	_Camera->SetFieldOfView(FMath::Lerp(DefaultFOV, SprintFOV, Value));
}

void AP_FPS::Handle_OnPossessed()
{
	_Health->UpdateBar();
}

void AP_FPS::Handle_Recoil(FVector2D recoil)
{
	_Camera->AddLocalRotation(FRotator(recoil.Y, 0.0f, 0.0f));
	AddActorWorldRotation(FRotator(0.0f, recoil.X, 0.0f));
}

void AP_FPS::Handle_HealthDead(AController* causer)
{
	
}

void AP_FPS::Handle_HealthDamaged(float currentHealth, float maxHealth, float change)
{
	
}

void AP_FPS::Handle_ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if(APickup* pickup = Cast<APickup>(OtherActor))
		{
			UE_LOG(LogTemp, Display, TEXT("PICKUP ENTERED"));
			if(!CurrentPickupsHovering.Contains(pickup))
				CurrentPickupsHovering.Add(pickup);

			if(CurrentPickupsHovering[0])
				OnHoveredWeaponPickupUpdated.Broadcast(CurrentPickupsHovering[0]->GetWeapon().GetDefaultObject()->_WeaponName);
		}
	}
}

void AP_FPS::Handle_ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UE_LOG(LogTemp, Display, TEXT("PICKUP EXITED"));
		if(APickup* pickup = Cast<APickup>(OtherActor))
		{
			if(CurrentPickupsHovering.Contains(pickup))
				CurrentPickupsHovering.Remove(pickup);
			
			if(CurrentPickupsHovering.IsEmpty())
				OnHoveredWeaponPickupUpdated.Broadcast("");
			else
				OnHoveredWeaponPickupUpdated.Broadcast(CurrentPickupsHovering[0]->GetWeapon().GetDefaultObject()->_WeaponName);
		}
	}
}

UBehaviorTree* AP_FPS::GetBehaviorTree_Implementation()
{
	return _BehaviorTree;
}

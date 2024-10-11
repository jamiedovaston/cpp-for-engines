#include "P_FPS.h"

#include "HealthComponent.h"
#include "Camera/CameraComponent.h"

AP_FPS::AP_FPS()
{
	PrimaryActorTick.bCanEverTick = true;

	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);

	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void AP_FPS::BeginPlay()
{
	Super::BeginPlay();

	_Health->OnDamaged.AddUniqueDynamic(this, &AP_FPS::Handle_HealthDamaged);
	_Health->OnDead.AddUniqueDynamic(this, &AP_FPS::AP_FPS::Handle_HealthDead);
}

void AP_FPS::Input_FirePressed_Implementation()
{
	//TODO: Make gun go bang
}

void AP_FPS::Input_FireReleased_Implementation()
{
	//TODO: Make gun stop
}

void AP_FPS::Input_JumpPressed_Implementation()
{
	ACharacter::Jump();
}

void AP_FPS::Input_JumpReleased_Implementation()
{
	ACharacter::StopJumping();
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

void AP_FPS::Handle_HealthDead(AController* causer)
{
	
}

void AP_FPS::Handle_HealthDamaged(float currentHealth, float maxHealth, float change)
{
	
}
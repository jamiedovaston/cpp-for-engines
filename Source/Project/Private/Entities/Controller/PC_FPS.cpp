#include "Entities/Controller/PC_FPS.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MANAGERS/GameRules/Rules/GameRule_Targets.h"
#include "Interfaces/Inputable/Inputable.h"
#include "Entities/P_FPS.h"
#include "Weapons/Weapon_Base.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Widgets/Widget_HUD.h"
#include "Blueprint/UserWidget.h"

void APC_FPS::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(_LookAction, ETriggerEvent::Triggered, this, &APC_FPS::Look);
		
		EIP->BindAction(_MoveAction, ETriggerEvent::Triggered, this, &APC_FPS::Move);
		
		EIP->BindAction(_JumpAction, ETriggerEvent::Started, this, &APC_FPS::JumpPressed);
		EIP->BindAction(_JumpAction, ETriggerEvent::Completed, this, &APC_FPS::JumpReleased);

		EIP->BindAction(_CrouchAction, ETriggerEvent::Started, this, &APC_FPS::CrouchPressed);
		EIP->BindAction(_CrouchAction, ETriggerEvent::Completed, this, &APC_FPS::CrouchReleased);
		
		EIP->BindAction(_SprintAction, ETriggerEvent::Started, this, &APC_FPS::SprintPressed);
		EIP->BindAction(_SprintAction, ETriggerEvent::Completed, this, &APC_FPS::SprintReleased);
		
		EIP->BindAction(_FireAction, ETriggerEvent::Started, this, &APC_FPS::FirePressed);
		EIP->BindAction(_FireAction, ETriggerEvent::Completed, this, &APC_FPS::FireReleased);
		
		EIP->BindAction(_ReloadAction, ETriggerEvent::Started, this, &APC_FPS::ReloadPressed);
		
		EIP->BindAction(_InteractAction, ETriggerEvent::Started, this, &APC_FPS::InteractPressed);
		EIP->BindAction(_InteractAction, ETriggerEvent::Completed, this, &APC_FPS::InteractReleased);
	}
}

void APC_FPS::Look(const FInputActionValue& value)
{
	FVector2D LookVector = value.Get<FVector2D>();

	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Look(currentPawn, LookVector);
		}
	}
}

void APC_FPS::Move(const FInputActionValue& value)
{
	FVector2D MoveVector = value.Get<FVector2D>();

	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Move(currentPawn, MoveVector);
		}
	}
}

void APC_FPS::JumpPressed()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_JumpPressed(currentPawn);
		}
	}
}

void APC_FPS::JumpReleased()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_JumpReleased(currentPawn);
		}
	}
}

void APC_FPS::CrouchPressed()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_CrouchPressed(currentPawn);
		}
	}
}

void APC_FPS::CrouchReleased()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_CrouchReleased(currentPawn);
		}
	}
}

void APC_FPS::SprintPressed()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_SprintPressed(currentPawn);
		}
	}
}

void APC_FPS::SprintReleased()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_SprintReleased(currentPawn);
		}
	}
}

void APC_FPS::FirePressed()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_FirePressed(currentPawn);
		}
	}
}

void APC_FPS::FireReleased()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_FireReleased(currentPawn);
		}
	}
}

void APC_FPS::ReloadPressed()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_ReloadPressed(currentPawn);
		}
	}
}

void APC_FPS::InteractPressed()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_InteractPressed(currentPawn);
		}
	}
}

void APC_FPS::InteractReleased()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_InteractReleased(currentPawn);
		}
	}
}

void APC_FPS::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(UEnhancedInputLocalPlayerSubsystem* subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UInputable::StaticClass()))
		{
			subsystem->AddMappingContext(IInputable::Execute_GetMappingContext(InPawn), 0);
		}
	}
	
	if(AP_FPS* pawn = Cast<AP_FPS>(InPawn))
	{
		UE_LOG(LogTemp, Display, TEXT("Pawn possessed! ----------------------------------------------------------------------"));
		pawn->OnHealthChangePercentage.AddUniqueDynamic(this, &APC_FPS::Handle_HealthChangePercentage);
		pawn->OnHoveredWeaponPickupUpdated.AddUniqueDynamic(this, &APC_FPS::Handle_HoveredWeaponPickup);
		pawn->OnWeaponEquipped.AddUniqueDynamic(this, &APC_FPS::Handle_WeaponEquipped);
		pawn->Handle_OnPossessed();
	}
}

void APC_FPS::Handle_EnemiesRemainingChanged(int _remaining)
{
	_HUDWidget->UpdateScore(_remaining);
}

void APC_FPS::Handle_WeaponEquipped(AWeapon_Base* _weapon)
{
	_weapon->OnAmmoChanged.AddUniqueDynamic(this, &APC_FPS::Handle_AmmoChangePercentage);
	_weapon->OnReloadActive.AddUniqueDynamic(this, &APC_FPS::Handle_ReloadActive);
	_weapon->OnReloadTimer.AddUniqueDynamic(this, &APC_FPS::Handle_ReloadTimer);
	Handle_ReloadActive(false);
	_HUDWidget->UpdateAmmo(1);
}

void APC_FPS::BeginPlay()
{
	Super::BeginPlay();
	UGameRule_Targets::OnGameRuleValueUpdated.AddUniqueDynamic(this, &APC_FPS::Handle_EnemiesRemainingChanged);
	
	if(_HUDWidgetClass)
	{
		_HUDWidget = CreateWidget<UWidget_HUD, APC_FPS*>( this, _HUDWidgetClass.Get());
		_HUDWidget->AddToViewport();
	}
}

void APC_FPS::Handle_HealthChangePercentage(float InPercent)
{
	_HUDWidget->UpdateHealth(InPercent);
}

void APC_FPS::Handle_HoveredWeaponPickup(FString CurrentHoveredPickup)
{
	_HUDWidget->UpdateWeaponHoverMenu(CurrentHoveredPickup);
}

void APC_FPS::Handle_ReloadTimer(float inPercent)
{
	_HUDWidget->UpdateReloadBar(inPercent);
}

void APC_FPS::Handle_ReloadActive(bool _active)
{
	_HUDWidget->ActivateReloadBar(_active);
}

void APC_FPS::Handle_AmmoChangePercentage(float InPercent)
{
	_HUDWidget->UpdateAmmo(InPercent);
}

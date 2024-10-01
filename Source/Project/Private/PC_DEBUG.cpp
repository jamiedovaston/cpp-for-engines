#include "PC_DEBUG.h"
#include "EnhancedInputComponent.h"

void APC_DEBUG::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(_DebugAction, ETriggerEvent::Triggered, this, &APC_DEBUG::Debug);
	}
}

void APC_DEBUG::Debug(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Display,TEXT("DEBUGGING WORKS--------------------------------------------------------------------------------------------------------------------!"));
}

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_DEBUG.generated.h"

struct FInputActionValue;

class UInputAction;

UCLASS(Abstract)
class PROJECT_API APC_DEBUG : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _DebugAction;

	virtual void SetupInputComponent() override;

	void Debug(const FInputActionValue& value);
};

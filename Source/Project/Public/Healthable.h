#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Healthable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthUpdatedSignature, float, newHealth, float, maxHealth, float, change)

UINTERFACE()
class UHealthable : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_API IHealthable
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintNativeEvent, BlueprintCallable)
	FHealthUpdatedSignature OnHealthUpdated;
};

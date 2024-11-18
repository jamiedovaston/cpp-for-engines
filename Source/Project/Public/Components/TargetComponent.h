#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetComponent.generated.h"

class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetRegisteredSignature, UTargetComponent*, target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTargetDestroyedSignature, UTargetComponent*, target, AController*, causer, int, targetValue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTargetComponent();

	UPROPERTY(BlueprintAssignable)
	FTargetDestroyedSignature OnDestroyed;
	
	static inline FTargetRegisteredSignature OnTargetRegistered;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	int _PointsValue;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UHealthComponent> _Health;

private:
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
};

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameRule_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameRuleCompleteSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameRuleValueUpdatedSignature, int, points);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UGameRule_Base : public UActorComponent
{
	GENERATED_BODY()

public:
	UGameRule_Base();

	FGameRuleCompleteSignature OnComplete;
	static inline FGameRuleValueUpdatedSignature OnGameRuleValueUpdated;
	
	UFUNCTION()
	virtual void Init();

protected:
	void BroadcastComplete();
	void BroadcastGameRuleValue(int points);
};

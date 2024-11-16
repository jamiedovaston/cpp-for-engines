#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameRule.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameRuleCompleteSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameRulePointsScoredSignature, int, points);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UGameRule : public UActorComponent
{
	GENERATED_BODY()

public:
	UGameRule();

	FGameRuleCompleteSignature OnComplete;
	static inline FGameRulePointsScoredSignature OnPointsScoredUpdated;
	
	UFUNCTION()
	virtual void Init();

protected:
	void BroadcastComplete();
	void BroadcastPointsScored(int points);
};

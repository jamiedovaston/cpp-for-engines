// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "GameRule_Targets.generated.h"

class UTargetComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGRTargetRequestTargetSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UGameRule_Targets : public UGameRule
{
	GENERATED_BODY()

public:
	UGameRule_Targets();

	static inline FGRTargetRequestTargetSignature OnRequestTarget;
	virtual void Init() override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TObjectPtr<UTargetComponent>> _Targets;

	int _AmountRemaining;
	
private:
	UFUNCTION()
	void Handle_TargetRegistered(UTargetComponent* target);
	UFUNCTION()
	void Handle_TargetDestroyed(UTargetComponent* target, AController* causer, int targetValue);
	
};

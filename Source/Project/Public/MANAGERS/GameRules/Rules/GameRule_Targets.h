// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MANAGERS/GameRules/GameRule_Base.h"
#include "GameRule_Targets.generated.h"

class UTargetComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UGameRule_Targets : public UGameRule_Base
{
	GENERATED_BODY()

public:
	UGameRule_Targets();

	virtual void Init() override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TObjectPtr<UTargetComponent>> _Targets;
	
	int _AmountRemaining = 0;
	
private:
	UFUNCTION()
	void Handle_TargetRegistered(UTargetComponent* target);
	UFUNCTION()
	void Handle_TargetDestroyed(UTargetComponent* target, AController* causer, int targetValue);
};

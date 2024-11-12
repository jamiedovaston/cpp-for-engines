// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "TargetsHit.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UTargetsHit : public UGameRule
{
	GENERATED_BODY()

public:
	UTargetsHit();

protected:
	virtual void BeginPlay() override;
};

﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthDeadSignature, AController*, causer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthDamagedSignature, float, newHealth, float, maxHealth, float, change);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthChangePercentageSignature, float, inPercent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	UPROPERTY(BlueprintAssignable)
	FHealthDeadSignature OnDead;
	UPROPERTY(BlueprintAssignable)
	FHealthDamagedSignature OnDamaged;
	UPROPERTY(BlueprintAssignable)
	FHealthChangePercentageSignature OnHealthChangePercentage;

	UFUNCTION()
	void UpdateBar() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float _CurrentHealth;
	
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser);
};

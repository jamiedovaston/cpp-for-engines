﻿#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UObject/Interface.h"
#include "Inputable.generated.h"

class UInputMappingContext;

UINTERFACE()
class UInputable : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_API IInputable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Look(FVector2D value);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Move(FVector2D value);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_JumpPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_JumpReleased();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_CrouchPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_CrouchReleased();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_FirePressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_FireReleased();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_ReloadPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_InteractPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_InteractReleased();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_SprintPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_SprintReleased();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_DamagePressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UInputMappingContext* GetMappingContext();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    UBehaviorTree* GetBehaviorTree();
};

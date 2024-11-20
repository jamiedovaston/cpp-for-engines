#include "MANAGERS/GameRules/Rules/GameRule_Targets.h"

#include "Components/TargetComponent.h"

UGameRule_Targets::UGameRule_Targets()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGameRule_Targets::Init()
{
	Super::Init();

	UTargetComponent::OnTargetRegistered.AddDynamic(this, &UGameRule_Targets::Handle_TargetRegistered);
}

void UGameRule_Targets::Handle_TargetRegistered(UTargetComponent* target)
{
	if(_Targets.Contains(target)) { return; }

	_Targets.Add(target);
	target->OnDestroyed.AddUniqueDynamic(this, &UGameRule_Targets::Handle_TargetDestroyed);
	_AmountRemaining++;
	GameRulePoints = _AmountRemaining;
	BroadcastGameRuleValue(GameRulePoints);
	UE_LOG(LogTemp,Warning,TEXT("Registered Target"));
}


void UGameRule_Targets::Handle_TargetDestroyed(UTargetComponent* target, AController* causer, int targetValue)
{
	_Targets.Remove(target);
	_AmountRemaining--;
	GameRulePoints = _AmountRemaining;
	BroadcastGameRuleValue(GameRulePoints);
	UE_LOG(LogTemp, Display, TEXT("Destroyed!"));	


	if(_AmountRemaining == 0)
	{
		BroadcastComplete();
	}
}
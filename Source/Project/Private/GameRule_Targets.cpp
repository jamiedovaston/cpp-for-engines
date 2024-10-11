#include "GameRule_Targets.h"

#include "TargetComponent.h"

UGameRule_Targets::UGameRule_Targets()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGameRule_Targets::Init()
{
	Super::Init();

	
}

void UGameRule_Targets::Handle_TargetRegistered(UTargetComponent* target)
{
	if(_Targets.Contains(target)) { return; }
	_Targets.Add(target);
	target->OnDestroyed.AddUniqueDynamic(this, &UGameRule_Targets::Handle_TargetDestroyed);
	_AmountRemaining++;
}

void UGameRule_Targets::Handle_TargetDestroyed(UTargetComponent* target, AController* causer, int targetValue)
{
	_Targets.Remove(target);
	_AmountRemaining--;
	BroadcastPointsScored(causer, targetValue);

	if(_AmountRemaining == 0)
	{
		BroadcastComplete();
	}
}



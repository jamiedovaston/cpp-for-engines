#include "MANAGERS/GameRules/GameRule_Base.h"

UGameRule_Base::UGameRule_Base()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGameRule_Base::Init()
{
	
}

void UGameRule_Base::BroadcastComplete()
{
	OnComplete.Broadcast();
}

void UGameRule_Base::BroadcastGameRuleValue(int points)
{
	OnGameRuleValueUpdated.Broadcast(points);
}



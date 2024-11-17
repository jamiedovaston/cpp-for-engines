#include "GameRule.h"

UGameRule::UGameRule()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGameRule::Init()
{
	
}

void UGameRule::BroadcastComplete()
{
	OnComplete.Broadcast();
}

void UGameRule::BroadcastGameRuleValue(int points)
{
	OnGameRuleValueUpdated.Broadcast(points);
}



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

void UGameRule::BroadcastPointsScored(int points)
{
	OnPointsScoredUpdated.Broadcast(points);
}



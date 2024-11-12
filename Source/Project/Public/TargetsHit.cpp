#include "TargetsHit.h"

#include "EngineUtils.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TargetComponent.h"

UTargetsHit::UTargetsHit()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTargetsHit::BeginPlay()
{
	Super::BeginPlay();
}


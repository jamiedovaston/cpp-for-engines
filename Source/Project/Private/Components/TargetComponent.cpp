#include "Components/TargetComponent.h"
#include "Components/HealthComponent.h"

UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	_PointsValue = 1;
}

void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* owner = GetOwner();
	_Health = owner->FindComponentByClass<UHealthComponent>();
	if(_Health == nullptr)
	{
		_Health = NewObject<UHealthComponent>(owner, TEXT("Health"));
		owner->AddInstanceComponent(_Health);
		_Health->RegisterComponent();
		owner->Modify();
	}

	_Health->OnDead.AddUniqueDynamic(this, &UTargetComponent::Handle_HealthDead);

	OnTargetRegistered.Broadcast(this);
}

void UTargetComponent::Handle_HealthDead(AController* causer)
{
	OnDestroyed.Broadcast(this, causer, _PointsValue);

	GetOwner()->Destroy();
}


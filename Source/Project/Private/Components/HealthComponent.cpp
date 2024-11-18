#include "Components/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	_MaxHealth = 100.f;
}

void UHealthComponent::UpdateBar() const
{
	OnHealthChangePercentage.Broadcast(_CurrentHealth / _MaxHealth);
}	

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	_CurrentHealth = _MaxHealth;
	OnDamaged.Broadcast(_CurrentHealth, _MaxHealth, 0.0f);

	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	const float change = FMath::Min(_CurrentHealth, Damage);
	_CurrentHealth -= change;
	OnDamaged.Broadcast(_CurrentHealth, _MaxHealth, change);
	UpdateBar();
	if(_CurrentHealth <= 0.0f)
	{
		OnDead.Broadcast(InstigatedBy);
	}
}
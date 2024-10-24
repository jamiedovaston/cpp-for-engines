#pragma once
 
#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "Weapon_Hitscan.generated.h"
 
UCLASS(Abstract)
class PROJECT_API AWeapon_Hitscan : public AWeapon_Base
{
	GENERATED_BODY()

public:
	virtual void Initialise(AActor* _Player, UCameraComponent* _Camera) override;
	virtual void Fire() override;
 
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _Damage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> ActorsToIgnore;
};

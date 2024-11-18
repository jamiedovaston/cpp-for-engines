#include "MANAGERS/GM_FPS.h"

#include "MANAGERS/GameRules/GameRule_Base.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
 
AActor* AGM_FPS::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if(_PlayerStarts.Num() == 0)
	{
		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), foundActors);
		for(AActor* actor : foundActors)
		{
			_PlayerStarts.Add(actor);
		}
	}
	if(_PlayerStarts.Num() > 0)
	{
		return _PlayerStarts[FMath::RandRange(0, _PlayerStarts.Num()-1)];
	}
	return nullptr;
}
 
void AGM_FPS::PostLogin(APlayerController* NewPlayer)
{
	_PlayerControllers.AddUnique(NewPlayer);
	Super::PostLogin(NewPlayer);
}
 
void AGM_FPS::Logout(AController* Exiting)
{
	_PlayerControllers.Remove(Exiting);
	Super::Logout(Exiting);
}

void AGM_FPS::Handle_GameRuleCompleted()
{
	UE_LOG(LogTemp, Display, TEXT("Match has ended!"));
	EndMatch();
}

void AGM_FPS::Handle_GameRuleValueChanged(AController* scorer, int points)
{
	OnEnemiesRemainingSignature.Broadcast(points);
}

void AGM_FPS::HandleMatchIsWaitingToStart()
{
	TArray<UActorComponent*> outComponents;
	GetComponents(outComponents);
	for(UActorComponent* comp : outComponents)
	{
		if(UGameRule_Base* rule = Cast<UGameRule_Base>(comp))
		{
			_GameRuleManagers.Add(rule);
			rule->Init(); 
			rule->OnComplete.AddUniqueDynamic(this, &AGM_FPS::Handle_GameRuleCompleted);
			_GameRulesLeft++;
		}
	}
    
	GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &AGM_FPS::DecreaseCountdown, 1.f, false);
	Super::HandleMatchIsWaitingToStart();
}

void AGM_FPS::DecreaseCountdown()
{
	_CountdownTimer--;
	UE_LOG(LogTemp, Display, TEXT("GAMEMODE Countdown: %d"), _CountdownTimer);
	if(_CountdownTimer == 0)
	{
		StartMatch();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &AGM_FPS::DecreaseCountdown, 1.f, false);
	}
}

void AGM_FPS::HandleMatchHasStarted()
{
	DefaultPawnClass = _MatchPawn;
	for(AController* controller : _PlayerControllers)
	{
		RestartPlayer(controller);
	}
	Super::HandleMatchHasStarted();
}

void AGM_FPS::HandleMatchHasEnded()
{
	UE_LOG(LogTemp, Display, TEXT("MATCH HAS ENDED!"));
	Super::HandleMatchHasEnded();
}

void AGM_FPS::OnMatchStateSet()
{
	FString output;
	if(MatchState == MatchState::WaitingToStart)
	{
		output = "Waiting To Start";
	}
	else if(MatchState == MatchState::InProgress)
	{
		output = "InProgress";
	}
	else if(MatchState == MatchState::WaitingPostMatch)
	{
		output = "Waiting Post Match";
	}
	else if(MatchState == MatchState::LeavingMap)
	{
		output = "Leaving Map";
	}
 
	UE_LOG(LogTemp, Display, TEXT("MATCH STATE CHANGED: %s"), *output);
    
	Super::OnMatchStateSet();
}
 
bool AGM_FPS::ReadyToStartMatch_Implementation() { return false; }
 
bool AGM_FPS::ReadyToEndMatch_Implementation() { return false; }
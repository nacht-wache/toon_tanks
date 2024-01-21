// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	auto * BasePawn = Cast<ABasePawn>(DeadActor);
	if (!BasePawn)
		return;

	BasePawn->HandleDestruction();
	if (DeadActor == Tank && TankPlayerController)
	{
		TankPlayerController->SetPLayerEnabledState(false);
		GameOver(false);
	}
	--TargetTowers;
	if (TargetTowers == 0)
		GameOver(true);
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	
	if (TankPlayerController)
	{
		TankPlayerController->SetPLayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		auto TimerDelegate = FTimerDelegate::CreateUObject(
			TankPlayerController,
			&AToonTanksPlayerController::SetPLayerEnabledState,
			true
			);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			TimerDelegate,
			StartDelay,
			false);	
		
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount() const
{
	TArray<AActor *> Towers; 
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}

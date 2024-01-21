// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATower::ATower()
	: FireRange(300.f)
{
}

bool ATower::IsTankInDistance() const
{
	return Tank && Tank->Alive && FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange;
}

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsTankInDistance())
		return;
	
	RotateTurret(Tank->GetActorLocation());
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

float ATower::GetInterpSpeed() const
{
	return 10.f;
}

void ATower::CheckFireCondition()
{
	if (!IsTankInDistance())
		return;

	Fire();
}

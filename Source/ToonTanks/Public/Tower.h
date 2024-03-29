// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	ATower();
	virtual void Tick(float DeltaSeconds) override;

	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

private:
	virtual float GetInterpSpeed() const override;

	void CheckFireCondition();
	bool IsTankInDistance() const;

private:
	TObjectPtr<ATank> Tank;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
};

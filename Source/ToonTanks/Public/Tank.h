// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UFloatingPawnMovement;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void HandleDestruction() override;

	APlayerController* GetTankPlayerController();
	
protected:
	virtual void BeginPlay() override;

private:
	void Move(float Value);
	void Rotate(float Value);

	virtual float GetInterpSpeed() const override;

public:
	bool Alive = true;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Camera Component")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Camera Component")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	TObjectPtr<APlayerController> PlayerController;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float TurnRate;
	
};

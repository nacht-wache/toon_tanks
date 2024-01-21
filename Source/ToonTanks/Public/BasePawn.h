// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class AProjectile;
class UCapsuleComponent;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RotateTurret(const FVector& LookAtTarget);
	void Fire();
	
private:
	virtual float GetInterpSpeed() const;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TObjectPtr<UParticleSystem> DeathParticles;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	TObjectPtr<USoundBase> DeathSound;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	TSubclassOf<UCameraShakeBase> DeathCameraShakeClass;
};


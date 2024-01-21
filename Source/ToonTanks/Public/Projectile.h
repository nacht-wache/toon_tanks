// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & HitResult);
private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	float InitialSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	float MaxSpeed;

	UPROPERTY(EditAnywhere, Category = Combat)
	float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TrailParticles, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystemComponent> ParticleSystemComponent;
	
	UPROPERTY(EditAnywhere, Category = Combat)
	TObjectPtr<UParticleSystem> HitParticle;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	TObjectPtr<USoundBase> LaunchSound;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	TObjectPtr<USoundBase> HitSound;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;
};

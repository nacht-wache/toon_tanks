// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
	: PlayerController(nullptr)
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(TurretMesh);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Rotate);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FHitResult HitResult;
	auto const res = PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if (!res)
		return;

	RotateTurret(HitResult.ImpactPoint);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	Alive = false;
}

APlayerController* ATank::GetTankPlayerController()
{
	return PlayerController;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
	Alive = true;
}

void ATank::Move(float Value)
{
	if (Controller && Value != 0.f)
	{
		FVector DeltaLocation(0.f);
		auto const DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
		DeltaLocation.X = Value * DeltaTime * Speed;
		AddActorLocalOffset(DeltaLocation, true);
	}
}

void ATank::Rotate(float Value)
{
	if (Controller && Value != 0.f)
	{
		FRotator DeltaRotation(0.f);
		auto const DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
		DeltaRotation.Yaw = Value * DeltaTime * TurnRate;
		AddActorLocalRotation(DeltaRotation);
	}
}

float ATank::GetInterpSpeed() const
{
	return 25.f;
}

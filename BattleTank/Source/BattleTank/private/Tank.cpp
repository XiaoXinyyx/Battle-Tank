// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ATank::AimAt(const FVector& HitLocation) {
	TankAimingComponent->AimAt(HitLocation, LauchSpeed);
}


void ATank::SetTankSkeletalReference(USkeletalMeshComponent* TankSkeletal) {
	if (TankSkeletal == nullptr) { return; }
	TankAimingComponent->SetTankSkeletalReference(TankSkeletal);
}


void ATank::Fire() const {
	UE_LOG(LogTemp, Warning, TEXT("Tank fires!"));
	return;
}


float ATank::GetTurretYaw() const {	return this->TurretYaw; }
float ATank::GetGunPitch() const { return this->GunPitch; }


void ATank::SetTurretYaw(float Yaw) { TurretYaw = Yaw; }
void ATank::SetGunPitch(float Pitch) { GunPitch = Pitch; }




// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(const FVector& HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTankSkeletalReference(USkeletalMeshComponent* TankSkeletal);

	UPROPERTY(BlueprintReadOnly, Category = Turret)
	float TurretYaw = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = Turret)
	float GunPitch = 0.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = TankProperty)
	float LauchSpeed = 100000.f; // TODO find sensible default

	// 炮台抬升速度与角度限制
	UPROPERTY(EditAnywhere, Category = TankProperty)
	float MaxElevationDegree = 50.f; 
	UPROPERTY(EditAnywhere, Category = TankProperty)
	float MinElevationDegree = -5.f;
	UPROPERTY(EditAnywhere, Category = TankProperty)
	float MaxEleDegreePerSec = 10.f;

	// 炮台水平旋转速度与角度限制
	UPROPERTY(EditAnywhere, Category = TankProperty)
	float MaxRotateDegree = 145.f;
	UPROPERTY(EditAnywhere, Category = TankProperty)
	float MinRotateDegree = -145.f;
	UPROPERTY(EditAnywhere, Category = TankProperty)
	float MaxRotDegreePerSec = 10.f;

};

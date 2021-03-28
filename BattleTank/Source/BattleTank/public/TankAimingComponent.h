// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class ATank;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties

	UTankAimingComponent();

	virtual void BeginPlay() override;

	void MoveTurretTowards(FVector& AimDirection);

	// -1 is max downward speed, and +1 is max upward speed
	void ElevateTurret(float RelativeSpeed);

	// -1 is max left speed, and +1 is max right speed
	void RotateTurret(float RelativeSpeed);

	void AimAt(const FVector& AimLocation, float LauchSpeed);

	void SetTankSkeletalReference(USkeletalMeshComponent* TankSkeletal);

private:
	USkeletalMeshComponent* TankSkeletal = nullptr;

	ATank* OwnerTank = nullptr;

	// 炮台抬升速度与角度限制
	UPROPERTY(EditAnywhere, Category = TurretProperty)
	float MaxElevationDegree = 40.f;
	UPROPERTY(EditAnywhere, Category = TurretProperty)
	float MinElevationDegree = -5.f;
	UPROPERTY(EditAnywhere, Category = TurretProperty)
	float MaxEleDegreePerSec = 5.f;

	// 炮台水平旋转速度与角度限制
	UPROPERTY(EditAnywhere, Category = TurretProperty)
	float MaxRotateDegree = 145.f;
	UPROPERTY(EditAnywhere, Category = TurretProperty)
	float MinRotateDegree = -145.f;
	UPROPERTY(EditAnywhere, Category = TurretProperty)
	float MaxRotDegreePerSec = 20.f;
};

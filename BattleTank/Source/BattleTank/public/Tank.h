// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(const FVector& HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTankSkeletalReference(USkeletalMeshComponent* TankSkeletal);

	UPROPERTY(BlueprintReadOnly, Category = Turret)
	float TurretYaw = 0.f;	// 当前炮台的水平旋转角度

	UPROPERTY(BlueprintReadOnly, Category = Turret)
	float GunPitch = 0.f;	// 当前炮台的抬升角度

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = TankProperty)
	float LauchSpeed = 8000.f; // TODO find sensible default
};

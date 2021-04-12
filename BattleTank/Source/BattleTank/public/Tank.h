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

	UFUNCTION(BlueprintCallable, Category = Input)
	void Fire() const;

	void SetTurretYaw(float Yaw);
	void SetGunPitch(float Pitch);
	
	UFUNCTION(BlueprintCallable, Category = Turret)
	float GetTurretYaw() const;
	UFUNCTION(BlueprintCallable, Category = Turret)
	float GetGunPitch() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UTankAimingComponent* TankAimingComponent;

private:
	UPROPERTY(EditAnywhere, Category = TankProperty)
	float LauchSpeed = 4000.f; 

	float TurretYaw = 0.f;	// 当前炮台的水平旋转角度
	float GunPitch = 0.f;	// 当前炮台的抬升角度
};

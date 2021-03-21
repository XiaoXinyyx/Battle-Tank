// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(const FVector& AimLocation, float LauchSpeed) {
	if (!TankSkeletal) {
		return;
	}
	FVector LauchVelocity; // OUT parameter
	FVector StartLocation = TankSkeletal->GetSocketLocation(FName(TEXT("Socket_BarrelFX")));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		GetWorld(),
		LauchVelocity,
		StartLocation,
		AimLocation,
		LauchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution) {
		FVector AimDirection = LauchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("Aim Direction: %s"), *AimDirection.ToString());
	}
	
}


void UTankAimingComponent::SetTankSkeletalReference(USkeletalMeshComponent* TankSkeletalToSet) {
	TankSkeletal = TankSkeletalToSet;
	if (!TankSkeletal) {
		UE_LOG(LogTemp, Error, TEXT("TankAimingComponent can't find skeletal mesh"));
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector& AimDirection) const {
	// �õ�Ŀ����̹�˲ο�ϵ�µ�����
	// 
	// �ı���̨ˮƽ�Ƕ�

	// �ı���̨�����Ƕ�
}
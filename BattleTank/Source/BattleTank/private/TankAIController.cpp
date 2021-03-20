// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	// Get AI controlled tank and log out
	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController possessing %s"), *ControlledTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController missing contolled tank"));
	}

	// Get player contolled tank and log out
	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController find player tank %s"), *PlayerTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIContoller missing player tank"));
	}

}


// Called every frame
void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	ATank* AITank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();
	if (AITank && PlayerTank) {
		AITank->AimAt(PlayerTank->GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("AI %s aiming at %s"), *AITank->GetName(), *PlayerTank->GetName());
	}
}


ATank* ATankAIController::GetControlledTank() const{
	return Cast<ATank, APawn>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

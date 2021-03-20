// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *ControlledTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController missing controlled tank"));
	}

	return;
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	AimTorwardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}


bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);

	// Screen location of crosshair
	FVector2D CrosshairLocation(
		CrossHairXLocation * (float)ViewportSizeX,
		CrossHairYLocation * (float)ViewportSizeY
	);

	FVector CrosshairDirection;
	if (GetLookDirection(CrosshairLocation, OUT CrosshairDirection)) {
		if (GetLookVectorHitLocation(CrosshairDirection, OUT HitLocation)) {
			return true;
		}
	}
	return false;
}


void ATankPlayerController::AimTorwardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(OUT HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
	}

	return;
}

bool ATankPlayerController::GetLookDirection(FVector2D& CrosshairLocation, OUT FVector& CrosshairDirection) const {
	FVector Temp;
	return DeprojectScreenPositionToWorld(
		CrosshairLocation.X,
		CrosshairLocation.Y,
		Temp,
		OUT CrosshairDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& LookDirection, OUT FVector& HitLocation) const {
	FHitResult HitResult;
	FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = CameraLocation + LookDirection * LineTraceRange;
	bool FLAG = GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		CameraLocation,
		LineTraceEnd,
		ECC_Visibility,
		FCollisionQueryParams(false),
		FCollisionResponseParams()
	);

	if(FLAG) { // LineTrace succeeded
		HitLocation = HitResult.Location;
		return true;
	}
	else { // LineTrace failed
		HitLocation = { 0.f, 0.f, 0.f };
		return false;
	}
}




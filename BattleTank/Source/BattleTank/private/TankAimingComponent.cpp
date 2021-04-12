
#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();
	OwnerTank = GetOwner<ATank>();
	if (OwnerTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("TankAimingComponent failed to get owner tank"));
	}
}


void UTankAimingComponent::AimAt(const FVector& AimLocation, float LauchSpeed) {
	if (TankSkeletal == nullptr) {
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
		MoveTurretTowards(AimDirection);
	}	
}


void UTankAimingComponent::SetTankSkeletalReference(USkeletalMeshComponent* TankSkeletalToSet) {
	if (TankSkeletalToSet == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("TankAimingComponent can't find skeletal mesh"));
		return;
	}
	TankSkeletal = TankSkeletalToSet;
}


void UTankAimingComponent::MoveTurretTowards(FVector& AimDirection) {
	// 坦克参考系下的瞄准方向
	FRotator RelativeAimDirection = AimDirection.Rotation() - GetOwner()->GetActorRotation();
	RelativeAimDirection.Yaw = FRotator::NormalizeAxis(RelativeAimDirection.Yaw); // Clamp the Angle to (-180, 180]

	// 改变炮台水平角度，根据帧率、最大旋转速度、旋转角度限制
	ElevateTurret(RelativeAimDirection.Pitch - OwnerTank->GetGunPitch());

	// 改变炮台俯仰角度，根据帧率、最大抬升速度、抬升角度限制
	RotateTurret(RelativeAimDirection.Yaw - OwnerTank->GetTurretYaw());
}


void UTankAimingComponent::ElevateTurret(float RelativeSpeed) {
	if (OwnerTank == nullptr) { return; }
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	float NewElevation = OwnerTank->GetGunPitch()
		+ RelativeSpeed * MaxEleDegreePerSec * GetWorld()->DeltaTimeSeconds;

	OwnerTank->SetGunPitch(FMath::Clamp<float>(NewElevation, MinElevationDegree, MaxElevationDegree));
}


void UTankAimingComponent::RotateTurret(float RelativeSpeed) {
	if (OwnerTank == nullptr) { return; }
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	float NewYaw = OwnerTank->GetTurretYaw()
		+ RelativeSpeed * MaxRotDegreePerSec * GetWorld()->DeltaTimeSeconds;

	OwnerTank->SetTurretYaw(FMath::Clamp<float>(NewYaw, MinRotateDegree, MaxRotateDegree));
}

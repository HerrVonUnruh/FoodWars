// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraTest.h"


// Sets default values
ACameraTest::ACameraTest()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltaTime = DeltaTime;
	RotateCamToCenter(DeltaTime); 
}

// Called to bind functionality to input
void ACameraTest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("InputAxis_Right", this,&ACameraTest::MoveCamera);
}

void::ACameraTest::MoveCamera(float Value)
{


	if (FMath::Abs(Value) > 0)
	{
		// Multiplizieren Sie mit DeltaTime, um die Rotationsgeschwindigkeit zu skalieren
		float RotationSpeedScaled = rotationSpeed * deltaTime;

		// Inkrementieren Sie den Rotationswinkel basierend auf der Skalierung und Benutzereingabe
		CurrentRotationAngle += RotationSpeedScaled * Value;

		// Berechnen Sie die neue Position der Kamera auf der Kreisbahn
		FVector NewCameraPosition = Center + FVector(moveCycleRadius * FMath::Cos(CurrentRotationAngle), moveCycleRadius * FMath::Sin(CurrentRotationAngle), 1000);

		// Setzen Sie die neue Position der Kamera
		SetActorLocation(NewCameraPosition);
	}
	
}	

void::ACameraTest::RotateCamToCenter(float DeltaTime)
{
	FRotator targetRotation = (Center - GetActorLocation()).Rotation();
	FRotator NewRot = FMath::RInterpTo(GetActorRotation(), targetRotation, DeltaTime, 1);
	SetActorRotation(NewRot);
}

float::ACameraTest::GetDeltaTime()
{
	return deltaTime; 
}

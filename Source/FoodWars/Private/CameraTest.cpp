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
	PlayerInputComponent->BindAxis("InputAxis_CameraUp", this, &ACameraTest::MoveCameraUp);
}

void ACameraTest::MoveCamera(float Value)
{
    if (FMath::Abs(Value) > 0)
    {
        float RotationSpeedScaled = rotationSpeed * deltaTime;
        CurrentRotationAngle += RotationSpeedScaled * Value;

        FVector NewCameraPosition;

        if (!isMovedUp)
        {
            // Bewegung auf der normalen Kreisbahn
            NewCameraPosition = Center + FVector(moveCycleRadius * FMath::Cos(CurrentRotationAngle), moveCycleRadius * FMath::Sin(CurrentRotationAngle), GetActorLocation().Z);
            maxDistance = FVector::Distance(Center, NewCameraPosition); // Speichern Sie die maximale Distanz
        }
        else
        {
            // Bewegung nach oben, Radius basierend auf prozentualem Anteil der maximalen Distanz �ndern
            float currentDistance = FVector::Distance(Center, GetActorLocation());
            float percentage = currentDistance / maxDistance;

            float newRadius = moveCycleRadius * percentage;
            NewCameraPosition = Center + FVector(newRadius * FMath::Cos(CurrentRotationAngle), newRadius * FMath::Sin(CurrentRotationAngle), GetActorLocation().Z);
        }

        SetActorLocation(NewCameraPosition);
        lowestPoint.X = NewCameraPosition.X;
        lowestPoint.Y = NewCameraPosition.Y;
    }
}



void ACameraTest::MoveCameraUp(float Value)
{
    if (Value != 0)
    {
        float distance;
        FVector dir;
        FVector targetPoint;

        if (Value > 0)
        {
            isMovedUp = true; 
            distance = FVector::Distance(HighestPoint, GetActorLocation());
            dir = HighestPoint - GetActorLocation();
            targetPoint = HighestPoint;
        }
        else
        {
            distance = FVector::Distance(lowestPoint, GetActorLocation());
            dir = lowestPoint - GetActorLocation();
            targetPoint = lowestPoint;
        }

        dir.Normalize();
        FVector DeltaMove = dir * deltaTime * moveSpeed * FMath::Abs(Value);
        if (distance > DeltaMove.Size())
        {
            SetActorLocation(GetActorLocation() + DeltaMove);
        }
        else
        {
            SetActorLocation(targetPoint);
            if(Value < 0)
            {
                isMovedUp = false; 
            }
        }
    }
}


void::ACameraTest::RotateCamToCenter(float DeltaTime)
{
	FRotator targetRotation = (Center - GetActorLocation()).Rotation();
	FRotator NewRot = FMath::RInterpTo(GetActorRotation(), targetRotation, DeltaTime, 1.3);
	SetActorRotation(NewRot);
}

float::ACameraTest::GetDeltaTime()
{
	return deltaTime; 
}

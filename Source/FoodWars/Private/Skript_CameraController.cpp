// Fill out your copyright notice in the Description page of Project Settings.


#include "Skript_CameraController.h"

// Sets default values
ASkript_CameraController::ASkript_CameraController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkript_CameraController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkript_CameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	changePlayerView(DeltaTime); 
 }

// Called to bind functionality to input
void ASkript_CameraController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    InputComponent->BindAction("ChangeTurn", IE_Pressed,  this, &ASkript_CameraController::OnChangeTurn); // Hier die Korrektur
}

void ASkript_CameraController::changePlayerView(float time)
{
    FVector currentLocation = GetActorLocation();
    FRotator currentRotation = GetActorRotation();
    FRotator newRotation;
    float alpha = 0.1f;
    if (FVector::Distance(currentLocation, playerPositions[posIndex]) < 10.0f)
    {
        if(changeTurn==true)
        {
            if (posIndex < 3)
            {
                posIndex++;
                changeTurn = false; 
            }
            else
            {
                posIndex = 0;
                changeTurn = false;
            }
        }
    }
    FVector direction = playerPositions[posIndex] - currentLocation;
    FVector dirNormalized = direction.GetSafeNormal();
    newRotation = FMath::Lerp(currentRotation, viewRotations[posIndex], alpha * time);
    currentLocation += dirNormalized * moveSpeed * time;
    SetActorLocation(currentLocation);
    SetActorRotation(newRotation);
}
void ASkript_CameraController::OnChangeTurn()
{
    changeTurn = true; 
}


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
    InputComponent->BindAction("ChangeTurn", IE_Pressed, this, &ASkript_CameraController::OnChangeTurn);
    InputComponent->BindAction("InputAction_RotationRight", IE_Pressed, this, &ASkript_CameraController::rotateRight);
    InputComponent->BindAction("InputAction_RotationLeft", IE_Pressed, this, &ASkript_CameraController::rotateLeft);
    InputComponent->BindAction("InputAction_RotationRight", IE_Released, this, &ASkript_CameraController::resetRotation);
    InputComponent->BindAction("InputAction_RotationLeft", IE_Released, this, &ASkript_CameraController::resetRotation);
}

void ASkript_CameraController::changePlayerView(float time)
{
    FVector currentLocation = GetActorLocation();
    FRotator currentRotation = GetActorRotation();
    FRotator newRotation;
    float alpha = 0.2f;
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
    if(isLookingAround == false)
    {
        newRotation = FMath::Lerp(currentRotation, viewRotations[posIndex], alpha * time);
        SetActorRotation(newRotation);
    }
    currentLocation += dirNormalized * moveSpeed * time;
    SetActorLocation(currentLocation);
}
void ASkript_CameraController::OnChangeTurn()
{
    changeTurn = true; 
}

void ASkript_CameraController::rotateRight()
{
    isLookingAround = true; 
    FRotator newRot = GetActorRotation(); 
    newRot.Yaw = newRot.Yaw + rotationSpeed * 10; 
    SetActorRotation(newRot);
   
}
void ASkript_CameraController::rotateLeft()
{
    isLookingAround = true;
    FRotator newRot = GetActorRotation();
    newRot.Yaw = newRot.Yaw + rotationSpeed * -10;
    SetActorRotation(newRot);

}

void ASkript_CameraController::resetRotation()
{
    isLookingAround = false;
}

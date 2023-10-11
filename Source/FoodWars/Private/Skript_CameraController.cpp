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
    InputComponent->BindAction("InputAction_RotationRight", IE_Pressed, this, &ASkript_CameraController::rotateRight); 
    InputComponent->BindAction("InputAction_RotationLeft", IE_Pressed, this, &ASkript_CameraController::rotateLeft);
    InputComponent->BindAction("InputAction_RotationRight", IE_Released, this, &ASkript_CameraController::stopPlayerRotating);
    InputComponent->BindAction("InputAction_RotationLeft", IE_Released, this, &ASkript_CameraController::stopPlayerRotating);
}

void ASkript_CameraController::changePlayerView(float time)
{
    FVector currentLocation = GetActorLocation();
    FRotator currentRotation = GetActorRotation();
    FRotator newRotation;
    float alpha = 0.1f;

    FVector direction = playerPositions[posIndex] - currentLocation;
    FVector dirNormalized = direction.GetSafeNormal();

    currentLocation += dirNormalized * 1000 * time;
    SetActorLocation(currentLocation);

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
    if(playerRotatesCam==false)
    {
        newRotation = FMath::Lerp(currentRotation, viewRotations[posIndex], alpha * time);
        SetActorRotation(newRotation);
    } 
    else if(playerRotatesCam == true && keyVal==1)
    {
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw += 10 * time;
        SetActorRotation(NewRotation);
    } else if(playerRotatesCam == true && keyVal == 2)
    {
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw -= 10*time;
        SetActorRotation(NewRotation);
    }    
}
void ASkript_CameraController::OnChangeTurn()
{
    changeTurn = true; 
}

void ASkript_CameraController::rotateRight()
{
    playerRotatesCam = true; 
    keyVal = 1; 
}

void ASkript_CameraController::rotateLeft()
{
    playerRotatesCam = true;
    keyVal = 2; 
}

void ASkript_CameraController::stopPlayerRotating()
{
    playerRotatesCam = false; 
    keyVal = 0; 
}

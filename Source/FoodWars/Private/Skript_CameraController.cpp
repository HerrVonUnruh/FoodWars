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
    //recieveing Input to change the player who is in Focus
    InputComponent->BindAction("InputAction_ChangeTurn", IE_Pressed,  this, &ASkript_CameraController::OnChangeTurn); // Hier die Korrektur

    //recieve input for camera rotation
    InputComponent->BindAction("InputAction_RotationRight", IE_Pressed, this, &ASkript_CameraController::rotateRight); 
    InputComponent->BindAction("InputAction_RotationLeft", IE_Pressed, this, &ASkript_CameraController::rotateLeft);
    InputComponent->BindAction("InputAction_RotationRight", IE_Released, this, &ASkript_CameraController::stopRotating);
    InputComponent->BindAction("InputAction_RotationLeft", IE_Released, this, &ASkript_CameraController::stopRotating);
    
    //recieve input for camera movement 
    PlayerInputComponent->BindAxis("InputAxis_Forward", this, &ASkript_CameraController::moveCameraForward);
    PlayerInputComponent->BindAxis("InputAxis_Right", this, &ASkript_CameraController::moveCameraRight);
    PlayerInputComponent->BindAxis("InputAxis_CameraUp", this, &ASkript_CameraController::moveCameraUp);
    
    //reset camera rotation and position
    InputComponent->BindAction("IputAction_CamToPlayerCorner", IE_Pressed, this, &ASkript_CameraController::resetCameraTransform);
    

}

void ASkript_CameraController::moveCameraForward(float Value)
{
    if (FMath::Abs(Value) > 0.0f)
    {
        playerInput = true;
        moveVector = GetActorLocation();
        FVector DeltaMove = GetActorForwardVector() * Value;
        moveVector += DeltaMove * 100;
        moveVector.Z = zPos; 
        SetActorLocation(moveVector);
        keyVal = 3;
    }
}

void ASkript_CameraController::moveCameraRight(float Value)
{
    if (FMath::Abs(Value) > 0.0f)
    {
        playerInput = true;
        moveVector = GetActorLocation();
        FVector DeltaMove = GetActorRightVector() * Value;
        moveVector += DeltaMove * 100;
        SetActorLocation(moveVector);
        keyVal = 3; 
    }
}


void ASkript_CameraController::changePlayerView(float time)
{
    FVector currentLocation = GetActorLocation();
    FRotator currentRotation = GetActorRotation();
    FRotator newRotation;
    float alpha = 0.1f;

    FVector direction = playerPositions[posIndex] - currentLocation;
    FVector dirNormalized = direction.GetSafeNormal();
    if(playerInput==false && !isOnPoint)
    {
        currentLocation += dirNormalized * 1000 * time;
        zPos = GetActorLocation().Z;
        SetActorLocation(currentLocation);
    }
    if (FVector::Distance(currentLocation, playerPositions[posIndex]) < 10.0f)
    {
        if(!isOnPoint)
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
        isOnPoint = true;
    }
    if(playerRotatesCam==false && keyVal == 0 && currentRotation != viewRotations[rotIndex])
    {
        newRotation = FMath::Lerp(currentRotation, viewRotations[rotIndex], alpha * time);

        SetActorRotation(newRotation);
    } 
    else if(playerRotatesCam == true && keyVal==1)
    {
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw += rotationSpeed * time;
        SetActorRotation(NewRotation);
    } else if(playerRotatesCam == true && keyVal == 2)
    {
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw -= rotationSpeed *time;
        SetActorRotation(NewRotation);
    }    
}
void ASkript_CameraController::OnChangeTurn()
{
    changeTurn = true; 
    isOnPoint = false; 
    playerRotatesCam = false;
    playerInput = false;
    rotIndex = posIndex; 
    keyVal = 0;
}

void ASkript_CameraController::rotateRight()
{
    playerRotatesCam = true; 
    keyVal = 1; 
}
void ASkript_CameraController::stopRotating()
{
    playerRotatesCam = false;
}

void ASkript_CameraController::rotateLeft()
{
    playerRotatesCam = true;
    keyVal = 2; 
}

/*
*********************Wir machen Kaffe******Metal*****wir machen alles ********* METAL*********************
*/
void ASkript_CameraController::moveCameraUp(float Value)
{
    if (FMath::Abs(Value) > 0.0f)
    {
        playerInput = true;
        moveVector = GetActorLocation();
        zPos += 1 * Value * 30;
       
        moveVector.Z = zPos;
        SetActorLocation(moveVector);
        keyVal = 4;
    }
}
void ASkript_CameraController::resetCameraTransform()
{
    playerRotatesCam = false; 
    playerInput = false; 
    keyVal = 0; 
}

void ASkript_CameraController::switchPlayerTurn()
{
    changeTurn = true;
    isOnPoint = false;
    playerRotatesCam = false;
    playerInput = false;
    if(posIndex < 3)
    {
        posIndex++; 
    } else 
    {
        posIndex = 0; 
    }
    rotIndex = posIndex;
    keyVal = 0;
}

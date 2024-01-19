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
    setPositionRef(); 
	
}

// Called every frame
void ASkript_CameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    deltaTime = DeltaTime;
	changePlayerView(DeltaTime);
 }

// Called to bind functionality to input
void ASkript_CameraController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    getPlayerMovementInput(PlayerInputComponent); 
    getPlayerRotationInput(PlayerInputComponent); 
}

//Handles the Input of the Player 
void ASkript_CameraController::getPlayerMovementInput(class UInputComponent* PlayerInputComponent)
{
    PlayerInputComponent->BindAxis("InputAxis_Forward", this, &ASkript_CameraController::moveCameraForward);
    PlayerInputComponent->BindAxis("InputAxis_Right", this, &ASkript_CameraController::moveCameraRight);
    PlayerInputComponent->BindAxis("InputAxis_CameraUp", this, &ASkript_CameraController::moveCameraUp);
}

void ASkript_CameraController::getPlayerRotationInput(class UInputComponent* PlayerInputComponent)
{
    InputComponent->BindAction("InputAction_RotationRight", IE_Pressed, this, &ASkript_CameraController::rotateRight);
    InputComponent->BindAction("InputAction_RotationLeft", IE_Pressed, this, &ASkript_CameraController::rotateLeft);
    InputComponent->BindAction("InputAction_RotationRight", IE_Released, this, &ASkript_CameraController::stopRotating);
    InputComponent->BindAction("InputAction_RotationLeft", IE_Released, this, &ASkript_CameraController::stopRotating);
}



//Camera Transform Handeling: 
void ASkript_CameraController::changePlayerView(float time)
{
    FVector currentLocation = GetActorLocation();
    FRotator currentRotation = GetActorRotation();
    moveCameraToNextPosition(currentLocation, time);
    adjustCameraRotationToNewPosition(currentRotation, time);
    applyPlayerInputToCameraRotation(time); 
}


//handels the Rotation of the Camera 
void ASkript_CameraController::adjustCameraRotationToNewPosition(FRotator camRot, float time)
{
    float alpha = 1.0f;
    FRotator newRot;
    if (playerRotatesCam == false && keyVal == 0 && camRot != viewRotations[rotIndex])
    {
        newRot = FMath::Lerp(camRot, viewRotations[rotIndex], alpha * time);
        SetActorRotation(newRot);
    }
}

void ASkript_CameraController::applyPlayerInputToCameraRotation(float time)
{
    if (playerRotatesCam == true && keyVal == 1)
    {
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw += rotationSpeed * time;
        SetActorRotation(NewRotation);
    }
    else if (playerRotatesCam == true && keyVal == 2)
    {
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw -= rotationSpeed * time;
        SetActorRotation(NewRotation);
    }
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

void ASkript_CameraController::moveCameraToNextPosition(FVector camPos, float time)
{
    FVector direction = playerPositions[posIndex] - camPos;
    FVector dirNormalized = direction.GetSafeNormal();
    if (playerInput == false && !isOnPoint)
    {
        camPos += dirNormalized * moveSpeed * time;
        zPos = GetActorLocation().Z;
        SetActorLocation(camPos);
    }
    if (FVector::Distance(camPos, playerPositions[posIndex]) < 10.0f)
    {
        isOnPoint = true;
    }
}
//camera movement handeling 
void ASkript_CameraController::moveCameraForward(float Value)
{
    if (FMath::Abs(Value) > 0.0f)
    {
        /*playerInput = true;
        moveVector = GetActorLocation();
        FVector DeltaMove = GetActorForwardVector() * Value;
        moveVector += DeltaMove * 100;
        moveVector.Z = zPos;
        SetActorLocation(moveVector);
        keyVal = 3;*/
        
        center.Z = zPos;
        keyVal = 3;
        moveVector.Z = zPos;
        playerInput = true;
           FVector CurrentLocation = GetActorLocation();

           // Die gewünschte Bewegungsrichtung (in diesem Beispiel wird der rechte Vektor verwendet)
           FVector DesiredDirection = GetActorForwardVector();

           // Die gewünschte Verschiebung basierend auf dem Eingabewert
           FVector DeltaMove = DesiredDirection * Value * moveSpeed*deltaTime;

           // Die neue Position, die erreicht werden soll
           FVector NewLocation = CurrentLocation + DeltaMove;

           // Die maximale erlaubte Entfernung


           // Überprüfen, ob die Bewegung die maximale Entfernung überschreitet
        if(FVector::Distance(center, NewLocation) < MaxDistance)
        {
            // Wenn die Bedingung erfüllt ist, führen Sie die Bewegung aus
            SetActorLocation(NewLocation);
        }
    }
}

void ASkript_CameraController::moveCameraRight(float Value)
{
    if (FMath::Abs(Value) > 0.0f)
    {
        /*playerInput = true;
        moveVector = GetActorLocation();
        FVector DeltaMove = GetActorRightVector() * Value;
        moveVector += DeltaMove * 100;
        SetActorLocation(moveVector);
        keyVal = 3;*/
        keyVal = 3;
        moveVector.Z = zPos;
        playerInput = true;
        // Die aktuelle Position des Actors
        center.Z = zPos;

           FVector CurrentLocation = GetActorLocation();

           // Die gewünschte Bewegungsrichtung (in diesem Beispiel wird der rechte Vektor verwendet)
           FVector DesiredDirection = GetActorRightVector();

           // Die gewünschte Verschiebung basierend auf dem Eingabewert
           FVector DeltaMove = DesiredDirection * Value * moveSpeed*deltaTime;

           // Die neue Position, die erreicht werden soll
           FVector NewLocation = CurrentLocation + DeltaMove;

           // Die maximale erlaubte Entfernung


           // Überprüfen, ob die Bewegung die maximale Entfernung überschreitet
        if(FVector::Distance(center, NewLocation) < MaxDistance)
        {
            // Wenn die Bedingung erfüllt ist, führen Sie die Bewegung aus
            SetActorLocation(NewLocation);
        }

    }
}

void ASkript_CameraController::moveCameraUp(float Value)
{
    if (FMath::Abs(Value) > 0.0f)
    {
        playerInput = true;
        moveVector = GetActorLocation();
        float oldZPos= zPos;
        zPos += 1 * Value * MoveSpeedUp;
       
        moveVector.Z = zPos;
        if(zPos < MaxDistance && zPos > 100)
        {
            SetActorLocation(moveVector);
        } else
        {
            zPos = oldZPos;
        }
        keyVal = 4;
    }
}

//game state stuff 
void ASkript_CameraController::resetCameraTransform()
{
    playerRotatesCam = false; 
    playerInput = false; 
    keyVal = 0; 
}

void ASkript_CameraController::OnChangeTurn()
{
    allowInput = false;
    changeTurn = true;
    isOnPoint = false;
    playerRotatesCam = false;
    playerInput = false;
}

void ASkript_CameraController::switchPlayerTurn()
{

    OnChangeTurn(); 
    if(posIndex < maxPlayer-1)
    {
        posIndex++; 
    } else 
    {
        posIndex = 0; 
    }
    rotIndex = posIndex;
    keyVal = 0;
}

//initiligiinz and helper stuff
void ASkript_CameraController::setPositionRef()
{
    for(int x = 0; x <=(maxPlayer-1); x++)
    {
        playerPositions[x] = cameraViewPos[x]->GetActorLocation(); 
        viewRotations[x] = cameraViewPos[x]->GetActorRotation();
    }
}
int ASkript_CameraController::getPlayerID()
{
    return posIndex+1; 
}

void ASkript_CameraController::setMaxPlayerIndex(int value)
{
    maxPlayerIndex = value; 
}

void ASkript_CameraController::resetPlayerPosition()
{
    isOnPoint = false;
    playerRotatesCam = false;
    playerInput = false;
}

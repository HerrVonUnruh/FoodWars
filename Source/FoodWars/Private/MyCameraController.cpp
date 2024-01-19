#include "MyCameraController.h"

// Sets default values
AMyCameraController::AMyCameraController()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyCameraController::BeginPlay()
{
    Super::BeginPlay();
    rotIndex = 0;
    deltaTime = 0;
    SetActorLocation(center);
    setPositionRef();
    resetPlayerPosition();
}

// Called every frame
void AMyCameraController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    deltaTime = DeltaTime;
    if(switchTurn || moveCameraToPos)
    {
        camAutoMovement(); 
        lookAt(); 
    }
}

// Called to bind functionality to input
void AMyCameraController::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("InputAxis_Right", this, &AMyCameraController::moveCameraHorizontal);
    PlayerInputComponent->BindAxis("InputAxis_CameraUp", this, &AMyCameraController::moveCameraUp);
}

void AMyCameraController::moveCameraHorizontal(float Value)
{
    if (Value != 0)
    {
        playerInput = true;
        FRotator playerRot = GetActorRotation();
        playerRot.Yaw += rotationSpeed * Value * deltaTime * -1;
        FRotator newRot = FMath::RInterpTo(GetActorRotation(), playerRot, deltaTime, 1.3);
        SetActorRotation(newRot);
    }
    else
    {
        playerInput = false;
    }
}

void AMyCameraController::lookAt()
{
    FVector CameraLocation = MyCamera->GetComponentLocation();
    FVector SceneRootLocation = GetActorLocation();
    FVector DirectionToSceneRoot = SceneRootLocation - CameraLocation;
    DirectionToSceneRoot.Normalize();
    FRotator TargetRotation = DirectionToSceneRoot.Rotation();
    FRotator NewRot = FMath::RInterpTo(GetActorRotation(), TargetRotation, deltaTime, 2);
    SetActorRotation(NewRot);
}

void AMyCameraController::camAutoMovement()
{
    FVector camPos = MyCamera->GetComponentLocation();
    FVector targetPos = cameraViewPos[rotIndex]->GetActorLocation();
    if (FVector::Distance(camPos,targetPos) > 10)
    {
        FVector dir = targetPos - camPos;
        dir.Normalize();
        camPos += dir * rotationSpeed;
        FVector newPos = FMath::VInterpTo(MyCamera->GetComponentLocation(), camPos, deltaTime, 1.3F);
        MyCamera->SetWorldLocation(newPos);
    } else 
    {
        switchTurn = false; 
        moveCameraToPos = false; 
        allowPlayerInput= true; 
    }
}
void AMyCameraController::moveCameraUp(float Value)
{
    if (Value != 0)
    {
        playerInput = true;
        FRotator playerRot = GetActorRotation();
        playerRot.Pitch += rotationSpeed * Value * deltaTime;
        playerRot.Pitch = FMath::ClampAngle(playerRot.Pitch, -45, 0);
        FRotator newRot = FMath::RInterpTo(GetActorRotation(), playerRot, deltaTime, 1.3);
        SetActorRotation(newRot);
    }
    else
    {
        playerInput = false;
    }
}

void AMyCameraController::switchPlayerTurn()
{
    if (rotIndex < maxPlayer - 1)
    {
        rotIndex++;
    }
    else
    {
        rotIndex = 0;
    }
    if (rotIndex >= 0 && rotIndex < cameraViewPos.Num())
    {
        switchTurn = true; 
        allowPlayerInput = false; 
    }
    else
    {
        allowPlayerInput = true;
        FString Message = FString::Printf(TEXT("couldnt find Actor in cameraViewPos at:  %d"), rotIndex);
        return;
    }
}

void AMyCameraController::setCamera(UCameraComponent *cam)
{
    MyCamera = cam;
}

void AMyCameraController::setPositionRef()
{
    for (int x = 0; x <= (maxPlayer - 1); x++)
    {
        if (x >= 0 && x < cameraViewPos.Num())
        {
            playerPositions.Add(cameraViewPos[x]->GetActorLocation());
            viewRotations.Add(cameraViewPos[x]->GetActorRotation());
        }
        else
        {
            FString Message = FString::Printf(TEXT("Initialize position failed at index %d"), x);
            break;
        }
    }
}

int AMyCameraController::getPlayerID()
{
    return rotIndex + 1;
}

void AMyCameraController::setMaxPlayerIndex(int value)
{
    maxPlayerIndex = value;
}

void AMyCameraController::resetPlayerPosition()
{
    if (playerInput == false)
    {
        if (rotIndex >= 0 && rotIndex < cameraViewPos.Num())
        {
            moveCameraToPos = true; 
        }
        else
        {
            moveCameraToPos=false; 
            FString Message = FString::Printf(TEXT("couldnt find Actor in cameraViewPos at:  %d"), rotIndex);
            return;
        }
    }
}

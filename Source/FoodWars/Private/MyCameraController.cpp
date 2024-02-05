#include "MyCameraController.h"

AMyCameraController::AMyCameraController()
{
    PrimaryActorTick.bCanEverTick = true;
    afkDetection = CreateDefaultSubobject<AAfkDetecter>(TEXT("AfkDetector"));
}

AMyCameraController::~AMyCameraController()
{
    delete camHelper;
}

void AMyCameraController::BeginPlay()
{
    Super::BeginPlay();
    rotIndex = 0;
    deltaTime = 0;
    SetActorLocation(center);
    setPositionRef();
    resetPlayerPosition();
}

void AMyCameraController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (myCamera != nullptr && camHelper == nullptr)
    {
        camHelper = new MyCameraHelper(myCamera, center);
    }
    if (cameraViewPos.Num() > 0 && settedCamPos==false)
    {
        for (AActor* pos : cameraViewPos)
        {
            pos->SetActorLocation(camHelper->setPlayerPositions(pos->GetActorLocation(), 2500));
        }
        settedCamPos=true; 
    }

    deltaTime = DeltaTime;
    afkDetection->IncreaseAFkTimer(DeltaTime);

    if (switchTurn || moveCameraToPos)
    {
        camAutoMovement();
        lookAt();
    }
}

void AMyCameraController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
        afkDetection->setRevievedInput(playerInput);
        FRotator playerRot = GetActorRotation();
        playerRot.Yaw += rotationSpeed * Value * deltaTime * -1;
        FRotator newRot = FMath::RInterpTo(GetActorRotation(), playerRot, deltaTime, 1.3);
        SetActorRotation(newRot);
    }
    else
    {
        playerInput = false;
        afkDetection->setRevievedInput(playerInput);
    }
}

void AMyCameraController::lookAt()
{
    if (myCamera != nullptr)
    {
        FVector CameraLocation = myCamera->GetComponentLocation();
        FVector SceneRootLocation = GetActorLocation();
        FVector DirectionToSceneRoot = SceneRootLocation - CameraLocation;
        DirectionToSceneRoot.Normalize();
        FRotator TargetRotation = DirectionToSceneRoot.Rotation();
        FRotator NewRot = FMath::RInterpTo(GetActorRotation(), TargetRotation, deltaTime, 2);
        SetActorRotation(NewRot);
    }
}

void AMyCameraController::camAutoMovement()
{
    if (myCamera == nullptr || cameraViewPos.Num() == 0)
    {
        return;
    }

    FVector camPos = myCamera->GetComponentLocation();
    FVector targetPos = cameraViewPos[rotIndex]->GetActorLocation();

    if (FVector::Distance(camPos, targetPos) > 1.0F)
    {
        if (camHelper != nullptr)
        {
            myCamera->SetWorldLocation(camHelper->setCameraPosition(2500.0F));
            lookAt();
        }

        FVector dir = targetPos - camPos;
        dir.Normalize();
        camPos += dir * rotationSpeed;
        FVector newPos = FMath::VInterpTo(myCamera->GetComponentLocation(), camPos, deltaTime, 1.3F);

        myCamera->SetWorldLocation(newPos);
    }
    else
    {
        switchTurn = false;
        moveCameraToPos = false;
        allowPlayerInput = true;
    }
}

void AMyCameraController::moveCameraUp(float Value)
{
    if (Value != 0)
    {
        playerInput = true;
        afkDetection->setRevievedInput(playerInput);
        FRotator playerRot = GetActorRotation();
        playerRot.Pitch += rotationSpeed * Value * deltaTime;
        playerRot.Pitch = FMath::ClampAngle(playerRot.Pitch, -55, -10);
        FRotator newRot = FMath::RInterpTo(GetActorRotation(), playerRot, deltaTime, 1.3);
        SetActorRotation(newRot);
    }
    else
    {
        playerInput = false;
        afkDetection->setRevievedInput(playerInput);
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

void AMyCameraController::setCamera(UCameraComponent* cam)
{
    myCamera = cam;
}

void AMyCameraController::setPositionRef()
{
    for (int x = 0; x < maxPlayer; x++)
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
    if (!playerInput)
    {
        if (rotIndex >= 0 && rotIndex < cameraViewPos.Num())
        {
            moveCameraToPos = true;
        }
        else
        {
            moveCameraToPos = false;
            FString Message = FString::Printf(TEXT("couldnt find Actor in cameraViewPos at:  %d"), rotIndex);
            return;
        }
    }
}

MyCameraHelper::MyCameraHelper(UCameraComponent* camera, FVector center)
    : m_Center(center)
{
    m_Camera = camera;
}

FVector MyCameraHelper::setCameraPosition(float distance)
{
    if (m_Camera == nullptr)
    {
        return FVector(0, 0, 0); // Early out!
    }

    FVector directionToCenter = m_Center - m_Camera->GetComponentLocation();
    directionToCenter.Normalize();
    FVector newCameraPos = m_Center - directionToCenter * distance;
    m_Camera->SetWorldLocation(newCameraPos);

    return newCameraPos;
}

FVector MyCameraHelper::setPlayerPositions(FVector position, float distance)
{
    FVector directionToCenter = m_Center - position;
    directionToCenter.Normalize();
    FVector newPos = m_Center - directionToCenter * distance;

    return newPos;
}

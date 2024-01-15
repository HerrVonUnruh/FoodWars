// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Skript_CameraController.generated.h"

UCLASS()
class FOODWARS_API ASkript_CameraController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASkript_CameraController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void changePlayerView(float time);
	void moveCameraForward(float Value); 
	void moveCameraRight(float Value);

	void OnChangeTurn();
	void rotateRight();
	void rotateLeft();

	void adjustCameraRotationToNewPosition(FRotator camRot, float time); 
	void moveCameraToNextPosition(FVector camPos, float time); 

	void stopRotating(); 
	void resetCameraTransform();

	void applyPlayerInputToCameraRotation(float time); 


	void getPlayerMovementInput(class UInputComponent* PlayerInputComponent);
	void getPlayerRotationInput(class UInputComponent* PlayerInputComponent);
	void moveCameraUp(float Value);

	//Blueprint functions
	UFUNCTION(BlueprintCallable)
	void switchPlayerTurn(); 

	UFUNCTION(BlueprintCallable)
	int getPlayerID(); 

	void setPositionRef(); 

	UFUNCTION(BlueprintCallable)
	void setMaxPlayerIndex(int value); 
    
    UFUNCTION(BlueprintCallable)
    void resetPlayerPosition();
    

private:
	UPROPERTY(EditAnywhere, Category = "Position Handler")
	bool changeTurn = false; 
	UPROPERTY(EditAnywhere, Category = "Position Handler")
	bool playerRotatesCam = false; 

	UPROPERTY(EditAnywhere, Category = "Position Handler")
	int maxPlayer = 3; 

	bool playerInput = false; 
	int32 keyVal = 0; 

	int maxPlayerIndex = 0; 

	bool isOnPoint = false; 
	float zPos = 1500.0f; 
    UPROPERTY(EditAnywhere, Category = "Position Limitation")
    float MaxDistanceUp = 5000.0f;
	UPROPERTY(EditAnywhere, Category = "Position Limitation")
	float MaxDistance = 5000.0f;
	UPROPERTY(EditAnywhere, Category = "Camera Movement Up")
	float MoveSpeedUp = 1000.0F; 
	UPROPERTY(EditAnywhere, Category = "Turn Change Speed")
	float rotationSpeed = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Turn Change Speed")
	float moveSpeed = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Camera Angle Adjustment")
	float cameraAngleAdjustment = 5.0f;

	bool reachedOneMaxHeight = false; 

	bool allowInput = false; 
	FVector moveVector; 
    
    UPROPERTY(EditAnywhere, Category = "Move Limitation")
    FVector center; 
	
	UPROPERTY(EditAnywhere, Category = "Position Handler")
	TArray<FVector> playerPositions;

	UPROPERTY(EditAnywhere, Category = "Rotation Handler")
	TArray<FRotator> viewRotations;
	
	UPROPERTY(EditAnywhere, Category = "Position Handler")
	TArray<AActor*> cameraViewPos; 
	int32 posIndex = 0;
	int32 rotIndex = 0; 
    
    float deltaTime; 


};

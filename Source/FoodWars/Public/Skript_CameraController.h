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

	void stopRotating(); 
	void resetCameraTransform(); 

	void moveCameraUp(float Value);

	//Blueprint functions
	UFUNCTION(BlueprintCallable)
	void switchPlayerTurn(); 

	UFUNCTION(BlueprintCallable)
	int getPlayerID(); 

private:
	UPROPERTY(EditAnywhere, Category = "Position Handler")
	bool changeTurn = false; 
	UPROPERTY(EditAnywhere, Category = "Position Handler")
	bool playerRotatesCam = false; 

	bool playerInput = false; 
	int32 keyVal = 0; 

	bool isOnPoint = false; 
	float zPos = 1500.0f; 

	UPROPERTY(EditAnywhere, Category = "Turn Change Speed")
	float rotationSpeed = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Turn Change Speed")
	float moveSpeed = 1.0f;

	FVector moveVector; 
	UPROPERTY(EditAnywhere, Category = "Position Handler")
	TArray<FVector> playerPositions;

	UPROPERTY(EditAnywhere, Category = "Rotation Handler")
	TArray<FRotator> viewRotations;
	int32 posIndex = 0;
	int32 rotIndex = 0; 
};

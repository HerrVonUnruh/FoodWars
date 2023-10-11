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

	void OnChangeTurn();

	void rotateRight(); 
	void rotateLeft();
	void resetRotation();
private:
	UPROPERTY(EditAnywhere, Category = "Position Handler")
	bool changeTurn = false; 

	bool isLookingAround = false; 

	UPROPERTY(EditAnywhere, Category = "Turn Change Speed")
	float rotationSpeed = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Turn Change Speed")
	float moveSpeed = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Position Handler")
	TArray<FVector> playerPositions;

	UPROPERTY(EditAnywhere, Category = "Rotation Handler")
	TArray<FRotator> viewRotations;
	int32 posIndex = 0;
};

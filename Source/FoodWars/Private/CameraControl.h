// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraControl.generated.h"

UCLASS()
class ACameraControl : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraControl();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category="Turn Change Speed")
	float rotationSpeed = 1.0f; 
	float moveSpeed = 1.0f; 

	UPROPERTY(EditAnywhere, Category = "Position Handler")
	FVector startPosition; 


};

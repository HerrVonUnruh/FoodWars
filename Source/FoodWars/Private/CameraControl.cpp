// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraControl.h"

// Sets default values
ACameraControl::ACameraControl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraControl::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACameraControl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	changePlayerView(DeltaTime);
}

void ACameraControl::changePlayerView(float time)
{
	FVector currentLocation = GetActorLocation();
	FRotator currentRotation = GetActorRotation();
	FRotator newRotation; 
	float alpha = 0.1f; 
	if(FVector::Distance(currentLocation, playerPositions[posIndex]) < 10.0f)
	{
		if(posIndex < 3)
		{
			posIndex++;
		} else 
		{
			posIndex = 0; 
		}
	} 
	FVector direction = playerPositions[posIndex] - currentLocation;
	FVector dirNormalized = direction.GetSafeNormal();
	newRotation = FMath::Lerp(currentRotation, viewRotations[posIndex], alpha*time);
	currentLocation += dirNormalized * moveSpeed * time;
	SetActorLocation(currentLocation);
	SetActorRotation(newRotation); 
; 
}

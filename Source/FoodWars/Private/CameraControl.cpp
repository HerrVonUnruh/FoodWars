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
	changePlayerView();
}

void ACameraControl::changePlayerView()
{
	FVector currentLocation = GetActorLocation();
	if(FVector::Distance(currentLocation, playerPositions[posIndex]) < 10.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Habe Punkt erreicht! CameraControl: %s"), *FString::Printf(TEXT("Wert: %d"), 42));

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
	currentLocation += dirNormalized * moveSpeed;
	SetActorLocation(currentLocation);
; 
}

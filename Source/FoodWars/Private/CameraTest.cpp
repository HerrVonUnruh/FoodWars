// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraTest.h"

// Sets default values
ACameraTest::ACameraTest()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltaTime = DeltaTime;

}

// Called to bind functionality to input
void ACameraTest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void::ACameraTest::MoveCamera()
{
	float angle = deltaTime * rotationSpeed;

	

}


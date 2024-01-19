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
}

// Called every frame
void ASkript_CameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
 }
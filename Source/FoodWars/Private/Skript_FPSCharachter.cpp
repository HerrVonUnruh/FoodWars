// Fill out your copyright notice in the Description page of Project Settings.


#include "Skript_FPSCharachter.h"

// Sets default values
ASkript_FPSCharachter::ASkript_FPSCharachter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkript_FPSCharachter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkript_FPSCharachter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkript_FPSCharachter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("InputAxis_Forward", this, &ASkript_FPSCharachter::moveForward);
	PlayerInputComponent->BindAxis("InputAxis_Right", this, &ASkript_FPSCharachter::moveRight);

}

void ASkript_FPSCharachter::moveForward(float value)
{
	moveVector = GetActorLocation(); 
	FVector deltaMove = GetActorForwardVector() * value; 
	moveVector += deltaMove * speed; 
	SetActorLocation(moveVector); 
}

void ASkript_FPSCharachter::moveRight(float value)
{
	moveVector = GetActorLocation();
	FVector deltaMove = GetActorRightVector() * value;
	moveVector += deltaMove * speed;
	SetActorLocation(moveVector);
}

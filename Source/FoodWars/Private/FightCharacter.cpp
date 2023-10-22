// Fill out your copyright notice in the Description page of Project Settings.


#include "FightCharacter.h"

// Sets default values
AFightCharacter::AFightCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFightCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFightCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFightCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("InputAxis_Right", this, &AFightCharacter::getMovementInput);
	PlayerInputComponent->BindAction("InputAction_Jump", IE_Pressed, this, &AFightCharacter::jumpPlayer); 
}

void AFightCharacter::getMovementInput(float Value)
{
	moveVector = body->GetActorLocation();
	FVector DeltaMove = body->GetActorRightVector() * Value;
	moveVector += DeltaMove * speed;
	body->SetActorLocation(moveVector);
}


void AFightCharacter::jumpPlayer()
{
	isJumping = false; 
	if(!isJumping)
	{
		isJumping = true; 
		moveVector = body->GetActorLocation();
		FVector jumpVec = body->GetActorUpVector() * jumpForce;
		moveVector += jumpVec;
		body->SetActorLocation(moveVector);
	}
}
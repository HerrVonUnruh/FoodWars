// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FightCharacter.generated.h"

UCLASS()
class FOODWARS_API AFightCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFightCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void getMovementInput(float Value); 
	void jumpPlayer();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	float speed = 10.0F;

	float jumpForce = 20.0F; 
	bool isJumping = false; 
	UPROPERTY(EditAnywhere)
	AActor* body;

	FVector moveVector; 
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
};

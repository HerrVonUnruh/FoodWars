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

	//movement input
	PlayerInputComponent->BindAxis("InputAxis_Forward", this, &ASkript_FPSCharachter::moveForward);
	PlayerInputComponent->BindAxis("InputAxis_Right", this, &ASkript_FPSCharachter::moveRight);
	PlayerInputComponent->BindAction("InputAction_Jump", IE_Pressed, this, &ASkript_FPSCharachter::jump);
	PlayerInputComponent->BindAction("InputAction_Jump", IE_Released, this, &ASkript_FPSCharachter::stopJumping);


	//mouse input
	PlayerInputComponent->BindAxis("InputAxis_MouseLookUp", this, &ASkript_FPSCharachter::rotateCameraUp);
	PlayerInputComponent->BindAxis("InputAxis_MouseLookRight", this, &ASkript_FPSCharachter::rotateRight);
}

void ASkript_FPSCharachter::moveForward(float value)
{
	if (FMath::Abs(value) > 0.0f)
	{
		moveVector = GetActorLocation();
		FVector deltaMove = GetActorForwardVector() * value;
		moveVector += deltaMove * speed;
		SetActorLocation(moveVector);
	}
}

void ASkript_FPSCharachter::moveRight(float value)
{
	if (FMath::Abs(value) > 0.0f)
	{
		moveVector = GetActorLocation();
		FVector deltaMove = GetActorRightVector() * value;
		moveVector += deltaMove * speed;
		SetActorLocation(moveVector);
	}
}

void ASkript_FPSCharachter::rotateCameraUp(float value)
{
	if (FMath::Abs(value) > 0.0f)
	{
		FRotator cameraRotation = camera->GetRelativeRotation();
		if (cameraRotation.Pitch < 90 && value > 0 || cameraRotation.Pitch > -90 && value < 0)
		{
			cameraRotation.Pitch +=  value;
			camera->SetRelativeRotation(cameraRotation);
		}
	} 
}

void ASkript_FPSCharachter::rotateRight(float value)
{
	if (FMath::Abs(value) > 0.0f)
	{
		FRotator playerRotation = GetActorRotation();
		playerRotation.Yaw += value;
		SetActorRotation(playerRotation);
	}
}


void ASkript_FPSCharachter::jump()
{
	if (!isJumping)
	{
		moveVector = GetActorLocation();
		isJumping = true;
		FVector jumpVec = GetActorUpVector() * jumpForce;
		moveVector += jumpVec;
		SetActorLocation(moveVector);
	}
}

void ASkript_FPSCharachter::stopJumping()
{
	isJumping = false; 
}
void ASkript_FPSCharachter::setCamera(UCameraComponent* cam)
{
	camera = cam; 
}

void ASkript_FPSCharachter::shoot(TSubclassOf<AActor> bulletClass, FVector barrel, bool debugBool, FRotator barrelRotation)
{
	bullet = GetWorld()->SpawnActor<AActor>(bulletClass, barrel, barrelRotation);
	UStaticMeshComponent* BulletSphereComponent = nullptr;
	TArray<UStaticMeshComponent*> MeshComponents;
	bullet->GetComponents<UStaticMeshComponent>(MeshComponents);

	if (MeshComponents.Num() > 0)
	{
		BulletSphereComponent = MeshComponents[0];
	}


	if (BulletSphereComponent)
	{
		FVector ImpulseDirection = BulletSphereComponent->GetUpVector();
		float ImpulseStrength = -50000.0f;
		UE_LOG(LogTemp, Warning, TEXT("Impulse Direction: %s"), *ImpulseDirection.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Impulse Strength: %f"), ImpulseStrength);
		BulletSphereComponent->AddImpulse(ImpulseDirection * ImpulseStrength);
	} else 
	{
		UE_LOG(LogTemp, Warning, TEXT("NO SPHERE!!!!! WARNING ACHTUNG!!!!!NO SPHERE %s"));
	
	}
}

void ASkript_FPSCharachter::moveBullet(float timeSpan,float deltaTime)
{
  while(timeSpan > 0)
  {

	  FVector bulletPos = bullet->GetActorLocation(); 
	  bulletPos += bullet->GetActorForwardVector() * 10.0F*deltaTime; 
	  bullet->SetActorLocation(bulletPos); 
	  timeSpan--; 
  } 
}

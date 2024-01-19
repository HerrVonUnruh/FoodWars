#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "MyCameraController.generated.h"

UCLASS()
class FOODWARS_API AMyCameraController : public APawn
{
	GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    AMyCameraController();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public: 
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    void moveCameraHorizontal(float Value);
    void moveCameraUp(float Value);
    void lookAt(); 
    //Blueprint functions
    UFUNCTION(BlueprintCallable)
    void switchPlayerTurn(); 

    UFUNCTION(BlueprintCallable)
    int getPlayerID(); 

    void setPositionRef(); 

    UFUNCTION(BlueprintCallable)
    void setMaxPlayerIndex(int value); 
    
    UFUNCTION(BlueprintCallable)
    void resetPlayerPosition();

    UFUNCTION(BlueprintCallable)
    void setCamera(UCameraComponent* cam);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* MyCamera;
    void camAutoMovement(); 

private:
    UPROPERTY(EditAnywhere, Category = "Position Handler")
    bool changeTurn = false; 
    UPROPERTY(EditAnywhere, Category = "Position Handler")
    bool playerRotatesCam = false; 

    UPROPERTY(EditAnywhere, Category = "Position Handler")
    int maxPlayer = 3; 

    bool playerInput = false; 
    int32 keyVal = 0; 


    int maxPlayerIndex = 0; 
    bool allowPlayerInput = true; 
    bool isOnPoint = false; 
    UPROPERTY(EditAnywhere, Category = "Turn Change Speed")
    float rotationSpeed = 1.0f;
    bool switchTurn = false; 
    bool moveCameraToPos = true; 
    
    bool allowInput = false; 
    
    UPROPERTY(EditAnywhere, Category = "Move Limitation")
    FVector center = FVector(0,0,0); 
    
    UPROPERTY(EditAnywhere, Category = "Position Handler")
    TArray<FVector> playerPositions;

    UPROPERTY(EditAnywhere, Category = "Rotation Handler")
    TArray<FRotator> viewRotations;
    
    UPROPERTY(EditAnywhere, Category = "Position Handler")
    TArray<AActor*> cameraViewPos; 
    int32 rotIndex = 0; 
    
    float deltaTime; 
};

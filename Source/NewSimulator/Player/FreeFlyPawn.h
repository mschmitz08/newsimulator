#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FreeFlyPawn.generated.h"

class UCameraComponent;
class USceneComponent;

UCLASS()
class NEWSIMULATOR_API AFreeFlyPawn : public APawn
{
    GENERATED_BODY()

public:
    AFreeFlyPawn();
    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USceneComponent> SceneRoot;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UCameraComponent> Camera;

    UPROPERTY(EditAnywhere, Category="Movement")
    float MoveSpeed = 1800.0f;

    UPROPERTY(EditAnywhere, Category="Movement")
    float SprintMultiplier = 3.0f;

    UPROPERTY(EditAnywhere, Category="Look")
    float LookSensitivity = 1.0f;

    float ForwardInput = 0.0f;
    float RightInput = 0.0f;
    float UpInput = 0.0f;
    bool bSprinting = false;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void MoveUp(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void SprintPressed();
    void SprintReleased();
    void ReleaseCursor();
    void CaptureCursor();
};

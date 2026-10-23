#include "Player/FreeFlyPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/PlayerController.h"

AFreeFlyPawn::AFreeFlyPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SceneRoot);
    Camera->bUsePawnControlRotation = true;

    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AFreeFlyPawn::BeginPlay()
{
    Super::BeginPlay();
    CaptureCursor();
}

void AFreeFlyPawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    const AController* PawnController = GetController();
    const FRotator ControlRotation = PawnController ? PawnController->GetControlRotation() : GetActorRotation();
    const FVector Forward = ControlRotation.Vector();
    const FVector Right = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Y);
    const FVector Up = FVector::UpVector;

    FVector Direction = Forward * ForwardInput + Right * RightInput + Up * UpInput;
    Direction = Direction.GetClampedToMaxSize(1.0f);

    const float Speed = MoveSpeed * (bSprinting ? SprintMultiplier : 1.0f);
    AddActorWorldOffset(Direction * Speed * DeltaSeconds, false);
}

void AFreeFlyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFreeFlyPawn::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFreeFlyPawn::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &AFreeFlyPawn::MoveUp);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AFreeFlyPawn::Turn);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AFreeFlyPawn::LookUp);
    PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AFreeFlyPawn::SprintPressed);
    PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AFreeFlyPawn::SprintReleased);
    PlayerInputComponent->BindAction(TEXT("ReleaseCursor"), IE_Pressed, this, &AFreeFlyPawn::ReleaseCursor);
    PlayerInputComponent->BindAction(TEXT("CaptureCursor"), IE_Pressed, this, &AFreeFlyPawn::CaptureCursor);
}

void AFreeFlyPawn::MoveForward(float Value) { ForwardInput = Value; }
void AFreeFlyPawn::MoveRight(float Value) { RightInput = Value; }
void AFreeFlyPawn::MoveUp(float Value) { UpInput = Value; }
void AFreeFlyPawn::SprintPressed() { bSprinting = true; }
void AFreeFlyPawn::SprintReleased() { bSprinting = false; }

void AFreeFlyPawn::Turn(float Value)
{
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        PC->AddYawInput(Value * LookSensitivity);
    }
}

void AFreeFlyPawn::LookUp(float Value)
{
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        PC->AddPitchInput(Value * LookSensitivity);
    }
}

void AFreeFlyPawn::ReleaseCursor()
{
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        PC->bShowMouseCursor = true;
        PC->SetInputMode(FInputModeGameAndUI());
    }
}

void AFreeFlyPawn::CaptureCursor()
{
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        PC->bShowMouseCursor = false;
        PC->SetInputMode(FInputModeGameOnly());
    }
}

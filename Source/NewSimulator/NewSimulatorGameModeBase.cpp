#include "NewSimulatorGameModeBase.h"

#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FreeFlyPawn.h"
#include "World/ProceduralCityActor.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"

ANewSimulatorGameModeBase::ANewSimulatorGameModeBase()
{
    DefaultPawnClass = nullptr;
}

void ANewSimulatorGameModeBase::StartPlay()
{
    Super::StartPlay();

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    if (!UGameplayStatics::GetActorOfClass(World, AProceduralCityActor::StaticClass()))
    {
        World->SpawnActor<AProceduralCityActor>(AProceduralCityActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
    }

    if (!UGameplayStatics::GetActorOfClass(World, ADirectionalLight::StaticClass()))
    {
        ADirectionalLight* Sun = World->SpawnActor<ADirectionalLight>(ADirectionalLight::StaticClass(), FVector::ZeroVector, FRotator(-45.0f, -35.0f, 0.0f));
        if (Sun && Sun->GetLightComponent())
        {
            Sun->GetLightComponent()->SetIntensity(100000.0f);
        }
    }

    if (!UGameplayStatics::GetActorOfClass(World, ASkyLight::StaticClass()))
    {
        ASkyLight* SkyLight = World->SpawnActor<ASkyLight>();
        if (SkyLight && SkyLight->GetLightComponent())
        {
            SkyLight->GetLightComponent()->SetRealTimeCapture(true);
        }
    }

    APlayerController* PC = World->GetFirstPlayerController();
    if (PC && !PC->GetPawn())
    {
        const FVector SpawnLocation(0.0f, -12000.0f, 2500.0f);
        const FRotator SpawnRotation(-8.0f, 0.0f, 0.0f);
        if (AFreeFlyPawn* Pawn = World->SpawnActor<AFreeFlyPawn>(AFreeFlyPawn::StaticClass(), SpawnLocation, SpawnRotation))
        {
            PC->Possess(Pawn);
        }
    }
}

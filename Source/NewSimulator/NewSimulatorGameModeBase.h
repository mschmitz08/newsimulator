#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NewSimulatorGameModeBase.generated.h"

UCLASS()
class NEWSIMULATOR_API ANewSimulatorGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ANewSimulatorGameModeBase();
    virtual void StartPlay() override;
};

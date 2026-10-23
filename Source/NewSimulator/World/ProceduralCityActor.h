#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralCityActor.generated.h"

class UMaterialInterface;
class USceneComponent;
class UStaticMesh;
class UStaticMeshComponent;

UCLASS()
class NEWSIMULATOR_API AProceduralCityActor : public AActor
{
    GENERATED_BODY()

public:
    AProceduralCityActor();
    UFUNCTION(CallInEditor, Category="Generation")
    void GenerateCity();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USceneComponent> SceneRoot;

    UPROPERTY()
    TObjectPtr<UStaticMesh> CubeMesh;

    UPROPERTY(EditAnywhere, Category="Layout", meta=(ClampMin="1"))
    int32 BlocksX = 5;

    UPROPERTY(EditAnywhere, Category="Layout", meta=(ClampMin="1"))
    int32 BlocksY = 5;

    UPROPERTY(EditAnywhere, Category="Layout", meta=(ClampMin="2000.0"))
    float BlockSize = 7000.0f;

    UPROPERTY(EditAnywhere, Category="Layout", meta=(ClampMin="500.0"))
    float RoadWidth = 1600.0f;

    UPROPERTY(EditAnywhere, Category="Layout", meta=(ClampMin="100.0"))
    float SidewalkWidth = 400.0f;

    UPROPERTY(EditAnywhere, Category="Buildings", meta=(ClampMin="1"))
    int32 BuildingsPerBlockSide = 3;

    UPROPERTY(EditAnywhere, Category="Buildings", meta=(ClampMin="300.0"))
    float MinBuildingHeight = 1200.0f;

    UPROPERTY(EditAnywhere, Category="Buildings", meta=(ClampMin="400.0"))
    float MaxBuildingHeight = 9000.0f;

    UPROPERTY(EditAnywhere, Category="Generation")
    int32 RandomSeed = 20261022;

    UPROPERTY(EditAnywhere, Category="Materials")
    TObjectPtr<UMaterialInterface> GroundMaterial;

    UPROPERTY(EditAnywhere, Category="Materials")
    TObjectPtr<UMaterialInterface> RoadMaterial;

    UPROPERTY(EditAnywhere, Category="Materials")
    TObjectPtr<UMaterialInterface> SidewalkMaterial;

    UPROPERTY(EditAnywhere, Category="Materials")
    TArray<TObjectPtr<UMaterialInterface>> BuildingMaterials;

    UPROPERTY(Transient)
    TArray<TObjectPtr<UStaticMeshComponent>> GeneratedComponents;

    void ClearGenerated();
    UStaticMeshComponent* CreateBox(const FString& Name, const FVector& Location, const FVector& Size, UMaterialInterface* Material);
    UMaterialInterface* ChooseBuildingMaterial(FRandomStream& Random) const;
};

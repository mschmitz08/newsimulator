#include "World/ProceduralCityActor.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"
#include "UObject/ConstructorHelpers.h"

AProceduralCityActor::AProceduralCityActor()
{
    PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeAsset.Succeeded())
    {
        CubeMesh = CubeAsset.Object;
    }
}

void AProceduralCityActor::BeginPlay()
{
    Super::BeginPlay();
    GenerateCity();
}

void AProceduralCityActor::GenerateCity()
{
    ClearGenerated();

    if (!CubeMesh)
    {
        UE_LOG(LogTemp, Error, TEXT("New Simulator: engine cube mesh could not be loaded."));
        return;
    }

    FRandomStream Random(RandomSeed);
    const float CellSize = BlockSize + RoadWidth;
    const float TotalX = BlocksX * CellSize + RoadWidth;
    const float TotalY = BlocksY * CellSize + RoadWidth;
    const float StartX = -TotalX * 0.5f;
    const float StartY = -TotalY * 0.5f;

    CreateBox(TEXT("Ground"), FVector::ZeroVector + FVector(0, 0, -50.0f), FVector(TotalX, TotalY, 100.0f), GroundMaterial);

    for (int32 X = 0; X <= BlocksX; ++X)
    {
        const float RoadX = StartX + RoadWidth * 0.5f + X * CellSize;
        CreateBox(FString::Printf(TEXT("Road_NS_%d"), X), FVector(RoadX, 0.0f, 5.0f), FVector(RoadWidth, TotalY, 10.0f), RoadMaterial);
    }

    for (int32 Y = 0; Y <= BlocksY; ++Y)
    {
        const float RoadY = StartY + RoadWidth * 0.5f + Y * CellSize;
        CreateBox(FString::Printf(TEXT("Road_EW_%d"), Y), FVector(0.0f, RoadY, 8.0f), FVector(TotalX, RoadWidth, 10.0f), RoadMaterial);
    }

    const float BlockOriginX = StartX + RoadWidth + BlockSize * 0.5f;
    const float BlockOriginY = StartY + RoadWidth + BlockSize * 0.5f;
    const int32 Lots = FMath::Max(1, BuildingsPerBlockSide);
    const float Usable = BlockSize - SidewalkWidth * 2.0f;
    const float LotSize = Usable / Lots;
    const float Footprint = LotSize * 0.72f;
    const float LotStart = -Usable * 0.5f + LotSize * 0.5f;

    for (int32 BX = 0; BX < BlocksX; ++BX)
    {
        for (int32 BY = 0; BY < BlocksY; ++BY)
        {
            const FVector BlockCenter(BlockOriginX + BX * CellSize, BlockOriginY + BY * CellSize, 0.0f);
            CreateBox(FString::Printf(TEXT("Sidewalk_%d_%d"), BX, BY), BlockCenter + FVector(0, 0, 15.0f), FVector(BlockSize, BlockSize, 30.0f), SidewalkMaterial);

            for (int32 LX = 0; LX < Lots; ++LX)
            {
                for (int32 LY = 0; LY < Lots; ++LY)
                {
                    const float Height = Random.FRandRange(MinBuildingHeight, MaxBuildingHeight);
                    const float Width = Footprint * Random.FRandRange(0.72f, 1.0f);
                    const float Depth = Footprint * Random.FRandRange(0.72f, 1.0f);
                    const FVector Location = BlockCenter + FVector(LotStart + LX * LotSize, LotStart + LY * LotSize, 30.0f + Height * 0.5f);
                    CreateBox(FString::Printf(TEXT("Building_%d_%d_%d_%d"), BX, BY, LX, LY), Location, FVector(Width, Depth, Height), ChooseBuildingMaterial(Random));
                }
            }
        }
    }
}

void AProceduralCityActor::ClearGenerated()
{
    for (UStaticMeshComponent* Component : GeneratedComponents)
    {
        if (IsValid(Component))
        {
            Component->DestroyComponent();
        }
    }
    GeneratedComponents.Reset();
}

UStaticMeshComponent* AProceduralCityActor::CreateBox(const FString& Name, const FVector& Location, const FVector& Size, UMaterialInterface* Material)
{
    UStaticMeshComponent* Component = NewObject<UStaticMeshComponent>(this, *Name);
    Component->SetupAttachment(SceneRoot);
    Component->SetStaticMesh(CubeMesh);
    Component->SetRelativeLocation(Location);
    Component->SetRelativeScale3D(Size / 100.0f);
    Component->SetMobility(EComponentMobility::Static);
    if (Material)
    {
        Component->SetMaterial(0, Material);
    }
    AddInstanceComponent(Component);
    Component->RegisterComponent();
    GeneratedComponents.Add(Component);
    return Component;
}

UMaterialInterface* AProceduralCityActor::ChooseBuildingMaterial(FRandomStream& Random) const
{
    if (BuildingMaterials.IsEmpty())
    {
        return nullptr;
    }
    return BuildingMaterials[Random.RandRange(0, BuildingMaterials.Num() - 1)];
}

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"

#include "OceanActor.generated.h"

UCLASS()
class OCEANSIM_API AOceanActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AOceanActor();

protected:
	virtual void BeginPlay() override;

private:
	void GenerateMesh();

public:
	UPROPERTY(EditAnywhere, Category = "Ocean")
	UProceduralMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Ocean")
	UMaterialInterface* OceanMat;

	UPROPERTY(EditAnywhere, Category = "Ocean")
	int32 GridSizeX = 256;
	UPROPERTY(EditAnywhere, Category = "Ocean")
	int32 GridSizeY = 256;
	UPROPERTY(EditAnywhere, Category = "Ocean")
	float QuadSize = 100.f;
};

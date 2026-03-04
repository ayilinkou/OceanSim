#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "OceanParameters.h"

#include "OceanActor.generated.h"

UCLASS()
class OCEANSIM_API AOceanActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AOceanActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void GenerateMesh();
	void UpdateMaterialParams();

public:
	UPROPERTY(EditAnywhere, Category = "Ocean")
	UProceduralMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Ocean")
	UMaterialInterface* OceanMat;
	UPROPERTY(BlueprintReadOnly, Category = "Ocean")
	UMaterialInstanceDynamic* DynamicMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ocean")
	FOceanParameters OceanParams;
	FOceanParameters PrevOceanParams;

	UPROPERTY(EditAnywhere, Category = "Ocean", meta = (ClampMin = "1"))
	int32 GridSize = 256;
	UPROPERTY(EditAnywhere, Category = "Ocean", meta = (ClampMin = "1.0"))
	float QuadSize = 100.f;
};

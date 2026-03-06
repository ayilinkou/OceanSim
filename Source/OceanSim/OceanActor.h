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

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	void GenerateMesh();
	void UpdateMaterialParams();

public:
	UPROPERTY(EditAnywhere, Category = "Ocean")
	UProceduralMeshComponent* Mesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Ocean")
	UMaterialInterface* OceanMat = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Ocean")
	UMaterialInstanceDynamic* DynamicMat = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ocean")
	FOceanParameters OceanParams;
	FOceanParameters PrevOceanParams;

	UPROPERTY(EditAnywhere, Category = "Ocean", meta = (ClampMin = "1"))
	int32 GridSize = 256;
	UPROPERTY(EditAnywhere, Category = "Ocean", meta = (ClampMin = "1.0"))
	float QuadSize = 100.f;
};

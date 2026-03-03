#include "OceanActor.h"

AOceanActor::AOceanActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Ocean Mesh"));
	RootComponent = Mesh;
}

void AOceanActor::BeginPlay()
{
	Super::BeginPlay();
	GenerateMesh();
}

void AOceanActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (OceanParams != PrevOceanParams)
	{
		UpdateMaterialParams();
	}
}

void AOceanActor::UpdateMaterialParams()
{
	DynamicMat->SetScalarParameterValue("Amplitude", OceanParams.Amplitude);
	DynamicMat->SetScalarParameterValue("Frequency", OceanParams.Frequency);
	DynamicMat->SetScalarParameterValue("AmplitudeMultiplier", OceanParams.AmplitudeMultiplier);
	DynamicMat->SetScalarParameterValue("FrequencyMultiplier", OceanParams.FrequencyMultiplier);
	DynamicMat->SetScalarParameterValue("NumOfWaves", (float)OceanParams.NumOfWaves);
	DynamicMat->SetVectorParameterValue("WaterColor", OceanParams.WaterColor);

	PrevOceanParams = OceanParams;
}

void AOceanActor::GenerateMesh()
{
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVs;

	// These three will be recalculated in the material every frame
	TArray<FVector> EmptyNormals;
	TArray<FProcMeshTangent> EmptyTangents;
	TArray<FColor> EmptyColors;

	const int32 NumVertsX = GridSize;
	const int32 NumVertsY = GridSize;

	float TotalSizeX = GridSize * QuadSize;
	float TotalSizeY = GridSize * QuadSize;

	float HalfSizeX = TotalSizeX * 0.5f;
	float HalfSizeY = TotalSizeY * 0.5f;

	for (int32 y = 0; y < NumVertsY; y++)
	{
		for (int32 x = 0; x < NumVertsX; x++)
		{
			float XPos = x * QuadSize - HalfSizeX;
			float YPos = y * QuadSize - HalfSizeY;

			Vertices.Add(FVector(XPos, YPos, 0.f));

			UVs.Add(FVector2D(
				(float)x / GridSize,
				(float)y / GridSize
			));
		}
	}

	for (int32 y = 0; y < GridSize; y++)
	{
		for (int32 x = 0; x < GridSize; x++)
		{
			int32 i0 = y * NumVertsX + x;
			int32 i1 = i0 + 1;
			int32 i2 = i0 + NumVertsX;
			int32 i3 = i2 + 1;

			Triangles.Add(i0);
			Triangles.Add(i2);
			Triangles.Add(i1);

			Triangles.Add(i1);
			Triangles.Add(i2);
			Triangles.Add(i3);
		}
	}
	
	int32 SectionIndex = 0;
	bool bCreateCollision = false;
	Mesh->CreateMeshSection(
		SectionIndex,
		Vertices,
		Triangles,
		EmptyNormals,
		UVs,
		EmptyColors,
		EmptyTangents,
		bCreateCollision
	);

	if (OceanMat)
	{
		DynamicMat = UMaterialInstanceDynamic::Create(OceanMat, this);
		Mesh->SetMaterial(0, DynamicMat);

		// need to wait a frame or so before attempting to update the material params
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, [this]()
		{
			UpdateMaterialParams();
		}, 0.1f, false);
	}
}
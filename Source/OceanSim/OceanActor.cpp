#include "OceanActor.h"

AOceanActor::AOceanActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Ocean Mesh"));
	RootComponent = Mesh;
}

void AOceanActor::BeginPlay()
{
	Super::BeginPlay();
	GenerateMesh();
}

void AOceanActor::GenerateMesh()
{
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FProcMeshTangent> Tangents;
	TArray<FColor> EmptyColors;

	const int32 NumVertsX = GridSizeX + 1;
	const int32 NumVertsY = GridSizeY + 1;

	float TotalSizeX = GridSizeX * QuadSize;
	float TotalSizeY = GridSizeY * QuadSize;

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
				(float)x / GridSizeX,
				(float)y / GridSizeY
			));

			Normals.Add(FVector::UpVector);
			Tangents.Add(FProcMeshTangent(1.f, 0.f, 0.f));
		}
	}

	for (int32 y = 0; y < GridSizeY; y++)
	{
		for (int32 x = 0; x < GridSizeX; x++)
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
		Normals,
		UVs,
		EmptyColors,
		Tangents,
		bCreateCollision
	);

	if (OceanMat)
		Mesh->SetMaterial(0, OceanMat);
}
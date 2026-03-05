#pragma once

#include "CoreMinimal.h"

#include "OceanParameters.generated.h"

USTRUCT(BlueprintType)
struct FOceanParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Parameters")
	FLinearColor WaterColor = FLinearColor(0.f, 0.5f, 1.f, 1.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Parameters", meta = (ClampMin = "0.01"))
	float Amplitude = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Parameters", meta = (ClampMin = "0.0001"))
	float Frequency = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Parameters", meta = (ClampMin = "1"))
	int32 Seed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fractal Controls", meta = (ClampMin = "1"))
	int32 NumOfWaves = 8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fractal Controls", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float AmplitudeMultiplier = 0.82f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fractal Controls", meta = (ClampMin = "1.0"))
	float FrequencyMultiplier = 1.18f;

	bool operator==(const FOceanParameters& Other) const
	{
		return FMath::IsNearlyEqual(Other.Amplitude, Amplitude)
			&& FMath::IsNearlyEqual(Other.Frequency, Frequency)
			&& FMath::IsNearlyEqual(Other.AmplitudeMultiplier, AmplitudeMultiplier)
			&& FMath::IsNearlyEqual(Other.FrequencyMultiplier, FrequencyMultiplier)
			&& NumOfWaves == Other.NumOfWaves
			&& Seed == Other.Seed
			&& WaterColor.Equals(Other.WaterColor, KINDA_SMALL_NUMBER);
	}
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GhostTrailActor.generated.h"

UCLASS()
class UE4_UNDERWORLD_API AGhostTrailActor : public AActor
{
	GENERATED_BODY()
	
public:
	AGhostTrailActor();
	virtual void Tick(float DeltaTime) override;

public:
	void Init(USkeletalMeshComponent* Pawn);

private:
	UPROPERTY(EditAnywhere)
		class UPoseableMeshComponent* PoseableMesh;
protected:
	UPROPERTY(EditAnywhere)
		UMaterialInstance* GhostMaterial;
	UPROPERTY(EditAnywhere)
		TArray<UMaterialInstanceDynamic*> Materials;

	bool IsSpawned = false;
	float FadeCountDown;
	float FadeOutTime = 0.5f;
};

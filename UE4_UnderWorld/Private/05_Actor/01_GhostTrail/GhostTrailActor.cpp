// Fill out your copyright notice in the Description page of Project Settings.


#include "05_Actor/01_GhostTrail/GhostTrailActor.h"

#include "Components/PoseableMeshComponent.h"
#include "Kismet/KismetMaterialLibrary.h"

AGhostTrailActor::AGhostTrailActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PoseableMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoserableMeshComponent"));
	RootComponent = PoseableMesh;
	//ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_PoseMesh(TEXT("SkeletalMesh'/Game/PP801_P3/Meshes/Characters/Combines/SK_PP801P3_G.SK_PP801P3_G'"));
	//if (SK_PoseMesh.Succeeded())
	//{
	//	PoseableMesh->SetSkeletalMesh(SK_PoseMesh.Object);
	//}
	//ConstructorHelpers::FObjectFinder<UMaterialInstance> M_GhostTail(TEXT("MaterialInstanceConstant'/Game/Blueprints/Player/MI_GhostTail.MI_GhostTail'"));
	//if (M_GhostTail.Succeeded())
	//{
	//	GhostMaterial = M_GhostTail.Object;
	//}
}

void AGhostTrailActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsSpawned)
	{
		FadeCountDown -= DeltaTime;
		for (int i = 0; i < Materials.Num(); i++)
		{
			Materials[i]->SetScalarParameterValue("Opacity", FadeCountDown / FadeOutTime);
		}
		if (FadeCountDown < 0)
		{
			Destroy();
		}
	}
}

void AGhostTrailActor::Init(USkeletalMeshComponent* Pawn)
{
	PoseableMesh->CopyPoseFromSkeletalComponent(Pawn);
	TArray<UMaterialInterface*> Mats = PoseableMesh->GetMaterials();

	for (int i = 0; i < Mats.Num(); i++)
	{
		Materials.Add(UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), GhostMaterial));
		PoseableMesh->SetMaterial(i, Materials[i]);
	}
	
	FadeCountDown = FadeOutTime;
	IsSpawned = true;
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

UCLASS()
class UE4_UNDERWORLD_API AProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere)
		class UCapsuleComponent* sphereComponent;					// ���� ������ �� �ݸ���
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* skeletalMeshComponent;		// ��ü ���
	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* projectileComponent;	
	UPROPERTY(EditAnywhere)
		class UAudioComponent* audioComponent;						// ����
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class UNiagaraComponent* niagaraSys;						// Niagara ȿ��
	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* particleComponent;			// ȿ��
public:
	class UProjectileMovementComponent* GetProjectileComponent() { return projectileComponent; }

protected:
	UPROPERTY(EditAnywhere)
		class UParticleSystem* hitParticle;			// overlap���� �� ������ ȿ��
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* hitParticle_Nia;		// overlap���� �� ������ ȿ��_Niagara
	UPROPERTY(EditAnywhere)
		class USoundBase* soundToPlay;				// overlap���� �� ����

	UPROPERTY(EditAnywhere)
		bool bHitSingle = true;				// �ϳ��� ��󿡸� ������� �� ���ΰ�
	UPROPERTY(EditAnywhere)
		bool bLifeSpan = true;				// �����ֱ� ����
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bLifeSpan == true"))
		float lifeSpanValue;				// �����ֱ� �� ����
	UPROPERTY(EditAnywhere)
		float damage;						// �����
	UPROPERTY(EditAnywhere)
		bool isSkill = false;				// ��ų�����ΰ�?(��ų or �⺻����)
	UPROPERTY(EditAnywhere)
		bool bIgnoreMyTeam = false;			// �� ���� �����ϰ� ������ ���ΰ�
	UPROPERTY(EditAnywhere)
		float falloffDistance = 1000.f;		// ���� ����

	UPROPERTY()
		TArray<class AActor*> hitActors;	// ������� ���� ActorList
	bool isExplored = false;				// �̹� �����°�?(��ø���� ������ �� ����)
public:
	// Overlap Event
	UFUNCTION()
		virtual void OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	void TurnOnCollision(bool bTurn);
	void SetDamage(float damageAmount) { damage = damageAmount; }	// ����� ����

	void Explored(FVector Location);
};


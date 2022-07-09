// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
#include "GameFramework/Actor.h"
#include "SkillRangeActor.generated.h"

UCLASS()
class UE4_UNDERWORLD_API ASkillRangeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillRangeActor();

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = CapsuleComponent)
		class UCapsuleComponent* CapsuleComponent;							// ���� ���� �ݸ���
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = DecalComponent)
		class UDecalComponent* DecalComponent;								// ���� ���� ��Į
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Sound)
		class UAudioComponent* audioComponent;								// ��ų ����
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Particle)
		class UParticleSystemComponent* SkillParticleComponent;				// ��ų ��ƼŬ

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere)
		float attackDelay = 3.f;			// ���� �� ���� ���� ������
	UPROPERTY(EditAnywhere)
		float cameraShakeScale = 1.f;		// ī�޶� ����ũ ������
	UPROPERTY(EditAnywhere)
		TArray<class AActor*> hitActors;	// �ǰ� ���

	UPROPERTY(EditAnywhere)
		EAttackType attackType = EAttackType::NORMAL;
	float damageAmount = 0.f;	// �����
	float damageValue = 0.f;	// ����� Value(���� Ÿ��, �˹� �Ŀ�) 
protected:
	void AttackRange();
public:
	void SetDamage(float damage);
	void SetValue(float value);
protected:
	UFUNCTION()
		void OnActorOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);
};

inline void ASkillRangeActor::SetValue(float value)
{
	damageValue = value;
}

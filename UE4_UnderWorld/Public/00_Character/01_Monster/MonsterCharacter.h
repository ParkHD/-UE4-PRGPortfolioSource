// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
#include "999_ETC/01_Types/MonsterType.h"
#include "MonsterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API AMonsterCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AMonsterCharacter();

protected:
	// Ÿ�� ����
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSourceComponent;
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Tick(float DeltaTime) override;
protected:
	// ���� Key
	UPROPERTY(EditAnywhere)
		FGameplayTag monsterTag;
	UPROPERTY(EditAnywhere)
		class UDataTable* monsterDataTable;		// ���� DT

	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AITree;			// AITree

	UPROPERTY(EditAnywhere) // TSubclassOf �������� �����ҋ� <>�ȿ� class�� ���ð���
		TSubclassOf<class UWidgetComponent> damageTextWidgetComponentClass;

	FTimerHandle HPBarTimerHandle;		// HPBar ���� Visible Ÿ�̸�
	FTimerHandle StunTimerHandle;		// ���� ���� Ÿ�̸�

	bool bodyAppearance = false;		// ���� �� ��ü �������
	float currentOpacity = 1.f;			// ��ü ����
	UPROPERTY(EditAnywhere)
		float opacityLerpSpeed = 0.1f;	// ��ü ������� �ӵ�

	UPROPERTY(EditAnywhere)
		bool isBoss = false;			// ������������ ����

	UPROPERTY(EditAnywhere, Category = "Animation")	
		TArray<class UAnimMontage*> attackMontageArray;		// ���� ��Ÿ��
public:
	FName GetMonsterTag() { return monsterTag.GetTagName(); }
	class UBehaviorTree* GetAIBehaviorTree() { return AITree; }

	const FMonsterInfo* GetMonsterInfo();
	// ���� ����
	//virtual void SetMoveState(EMoveState state) override;
	virtual void SetActionState(EActionState state) override;
	virtual void SetAttackState(EAttackState state) override;
	virtual void SetCharacterState(ECharacterState state) override;

	virtual void TakeAirborne(float airbornePower, float stunTime) override;
	virtual void TakeStun(float stunTime) override;
	virtual void StandUp() override;
	// �׾��� �� �̺�Ʈ
	virtual void OnDead() override;

	// Team����
	//virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;

	void SetDeadAppearance() { bodyAppearance = true; }

	// ����
	//virtual void TakeStun(float StunTime) override;

	// �ɷ�ġ ����
	void SetStat();
	// ���� ����
	
	// �Ϲ� ����
	virtual void NormalAttack();
	// �̵� ���� ���ϱ�
	//float GetMoveDirection();
	
	// ����� ���� �� ��������Ʈ ���ε� �Լ�
	/*UFUNCTION()
		void OnTakeDamageEvent(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);*/

protected:
	void TurnOnHPBarWidget();
	void CreateDamageWidget(float damageAmount);
};

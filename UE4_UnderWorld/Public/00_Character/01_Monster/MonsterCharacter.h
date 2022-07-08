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
	// 타겟 감지
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSourceComponent;
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Tick(float DeltaTime) override;
protected:
	// 몬스터 Key
	UPROPERTY(EditAnywhere)
		FGameplayTag monsterTag;
	UPROPERTY(EditAnywhere)
		class UDataTable* monsterDataTable;		// 몬스터 DT

	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AITree;			// AITree

	UPROPERTY(EditAnywhere) // TSubclassOf 블프에서 선택할떄 <>안에 class만 선택가능
		TSubclassOf<class UWidgetComponent> damageTextWidgetComponentClass;

	FTimerHandle HPBarTimerHandle;		// HPBar 위젯 Visible 타이머
	FTimerHandle StunTimerHandle;		// 몬스터 스턴 타이머

	bool bodyAppearance = false;		// 죽은 후 시체 사라지기
	float currentOpacity = 1.f;			// 시체 투명도
	UPROPERTY(EditAnywhere)
		float opacityLerpSpeed = 0.1f;	// 시체 사라지는 속도

	UPROPERTY(EditAnywhere)
		bool isBoss = false;			// 보스몬스터인지 설정

	UPROPERTY(EditAnywhere, Category = "Animation")	
		TArray<class UAnimMontage*> attackMontageArray;		// 공격 몽타주
public:
	FName GetMonsterTag() { return monsterTag.GetTagName(); }
	class UBehaviorTree* GetAIBehaviorTree() { return AITree; }

	const FMonsterInfo* GetMonsterInfo();
	// 상태 설정
	//virtual void SetMoveState(EMoveState state) override;
	virtual void SetActionState(EActionState state) override;
	virtual void SetAttackState(EAttackState state) override;
	virtual void SetCharacterState(ECharacterState state) override;

	virtual void TakeAirborne(float airbornePower, float stunTime) override;
	virtual void TakeStun(float stunTime) override;
	virtual void StandUp() override;
	// 죽었을 때 이벤트
	virtual void OnDead() override;

	// Team설정
	//virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;

	void SetDeadAppearance() { bodyAppearance = true; }

	// 스턴
	//virtual void TakeStun(float StunTime) override;

	// 능력치 설정
	void SetStat();
	// 몬스터 정보
	
	// 일반 공격
	virtual void NormalAttack();
	// 이동 방향 구하기
	//float GetMoveDirection();
	
	// 대미지 입을 때 델리게이트 바인딩 함수
	/*UFUNCTION()
		void OnTakeDamageEvent(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);*/

protected:
	void TurnOnHPBarWidget();
	void CreateDamageWidget(float damageAmount);
};

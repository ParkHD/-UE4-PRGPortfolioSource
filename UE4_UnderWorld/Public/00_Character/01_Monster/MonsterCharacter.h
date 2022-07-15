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
	UPROPERTY(EditAnywhere)
		class UDataTable* monsterDataTable;		// 몬스터 DT
	UPROPERTY(EditAnywhere)
		FGameplayTag monsterTag;			// 몬스터 Tag
		
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AITree;			// AITree

	UPROPERTY(EditAnywhere) // TSubclassOf 블프에서 선택할 <>안에 class만 선택가능
		TSubclassOf<class UWidgetComponent> damageTextWidgetComponentClass;	// 대미지 위젯

	FTimerHandle HPBarTimerHandle;				// HPBar 위젯 Visible 타이머

	bool bodyAppearance = false;				// 죽은 후 시체 사라지기
	float currentOpacity = 1.f;				// 시체 투명도
	UPROPERTY(EditAnywhere)
		float opacityLerpSpeed = 0.1f;			// 시체 사라지는 속도

	UPROPERTY(EditAnywhere, Category = "Animation")	
		TArray<class UAnimMontage*> attackMontageArray;		// 공격 몽타주 배열
public:
	FName GetMonsterTag() { return monsterTag.GetTagName(); }
	class UBehaviorTree* GetAIBehaviorTree() { return AITree; }

	// 몬스터 정보 가져오기
	const FMonsterInfo* GetMonsterInfo();
	// 상태 설정
	//virtual void SetMoveState(EMoveState state) override;
	virtual void SetActionState(EActionState state) override;
	virtual void SetAttackState(EAttackState state) override;
	virtual void SetCharacterState(ECharacterState state) override;
	
	// 에어본 함수
	virtual void TakeAirborne(float airbornePower, float stunTime) override;
	// 스턴 함수
	virtual void TakeStun(float stunTime) override;
	// 에어본 후 일어나는 함수
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
	
	// 일반 공격
	virtual void NormalAttack();
	// 이동 방향 구하기
	//float GetMoveDirection();
	
protected:
	// HPBar 위젯 활성화
	void TurnOnHPBarWidget();
	// 데미지 Text위젯 생성
	void CreateDamageWidget(float damageAmount);
};

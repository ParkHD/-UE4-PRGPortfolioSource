// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
#include "999_ETC/02_Interface/Interface_InterAction.h"
#include "PlayerCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FShakeDelegate, float);

UCLASS()
class UE4_UNDERWORLD_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class UCameraComponent* Camera;								// 카메라
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;							// 스프링 암
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Particle)
		class UParticleSystemComponent* ChargingParticleComponent;		 		// 차징 파티클

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Component)
		class UQuickSlotComponent* QuickSlotComponent;						// 퀵슬롯 컴포넌트
public:
	class UQuickSlotComponent* GetQuickSlotComponent() { return QuickSlotComponent; }
public:
	// 공격버튼 입력이 되었는가
	bool bInputComboAttack = false;
	// 스킬 차징 한 시간
	float chargingTime = 0.f;
public:
	const float GetChargingTime() { return chargingTime; }
protected:
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* DashMontage;		// 대쉬 몽타주

	IInterface_InterAction* interActionActor;		// 현재 캐릭터와 상호작용 가능한 Actor
private:
	// 키 조작 함수
	// 앞뒤 이동
	void MoveForward(float newAxisValue);
	// 왼쪽 오른쪽 이동
	void MoveRight(float newAxisValue);
	// 카메라 위아래 이동
	void LookUp(float newAxisValue);
	// 카메라 왼쪽 오른쪽 이동
	void Turn(float newAxisValue);
	// 대쉬
	void Dash();
	// 공격
	void PressAttack();
	// 퀵슬롯 사용 함수
#pragma region QuickSlotKey
	void PressQuickSlot1();
	void ReleaseQuickSlot1();
	void PressQuickSlot2();
	void ReleaseQuickSlot2();
	void PressQuickSlot3();
	void ReleaseQuickSlot3();
	void PressQuickSlot4();
	void ReleaseQuickSlot4();
	void PressQuickSlot5();
	void ReleaseQuickSlot5();
	void PressQuickSlot6();
	void ReleaseQuickSlot6();
	void PressQuickSlot7();
	void ReleaseQuickSlot7();
	void PressQuickSlot8();
	void ReleaseQuickSlot8();
	void PressQuickSlot9();
	void ReleaseQuickSlot9();
	void PressQuickSlot10();
	void ReleaseQuickSlot10();
	void PressQuickSlot11();
	void ReleaseQuickSlot11();
	void PressQuickSlot12();
	void ReleaseQuickSlot12();
	void PressQuickSlot13();
	void ReleaseQuickSlot13();
	void PressQuickSlot14();
	void ReleaseQuickSlot14();
	void PressQuickSlot15();
	void ReleaseQuickSlot15();
	void PressQuickSlot16();
	void ReleaseQuickSlot16();
#pragma endregion
	// 스킬 창 열기
	void PressSkillWindow();

	// 상호작용 키
	void PressInterActive();
public:
	// 플레이어 카메라 쉐이킹
	void CameraShakeDemo(float Scale);

	// Character State 설정
	// MoveState SetUp
	virtual void SetMoveState(EMoveState state) override;
	// ActionState SetUp
	virtual void SetActionState(EActionState state) override;
	// AttackState SetUp
	virtual void SetAttackState(EAttackState state) override;

	// 스턴 함수
	virtual void TakeStun(float stunTime) override;
	// 캐릭터 에어본 함수
	virtual void TakeAirborne(float airbornePower, float stunTime) override;
	// 캐릭터 에어본 후 다시 일어나는 함수
	virtual void StandUp() override;
	
	// 상호작용 가능 한 Actor 설정
	void SetInterActionActor(IInterface_InterAction* InterAction) { interActionActor = InterAction; }
private:
	// 카메라 쉐이크 BP
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShakeBase> CamSake;
};


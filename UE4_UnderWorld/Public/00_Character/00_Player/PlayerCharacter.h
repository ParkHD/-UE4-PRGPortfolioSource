// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
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


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Mesh)
		class USkeletalMeshComponent* WeaponSkeletalMesh;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class UCameraComponent* Camera;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class UParticleSystemComponent* particleSys;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class UNiagaraComponent* niagaraSys;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Component)
		class UQuickSlotComponent* QuickSlotComponent;
public:
	class UQuickSlotComponent* GetQuickSlotComponent() { return QuickSlotComponent; }
public:
	// 공격버튼 입력이 되었는가
	bool bInputComboAttack = false;

	bool bPressChargingSkill = false;
protected:
	float chargingTime = 0.f;
public:
	const float GetChargingTime() { return chargingTime; }
protected:
	UPROPERTY(EditAnywhere)
		float DashPlaySpeed = 1.f;
	UPROPERTY(EditAnywhere)
		float DashSpeed = 1000.f;

	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* DashMontage;
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* SkillMontage;
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* SkillMontage2;
private:
	void MoveForward(float newAxisValue);
	void MoveRight(float newAxisValue);
	void LookUp(float newAxisValue);
	void Turn(float newAxisValue);

	void Dash();

	void PressAttack();
	void ReleaseAttack();
	void PressSkill();
	void ReleaseSkill();
	void PressSkillWindow();
public:
	void CameraShakeDemo(float Scale);
	void InitChargingSkill();
private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShakeBase> CamSake;
};

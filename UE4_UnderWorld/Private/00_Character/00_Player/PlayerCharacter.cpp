// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "00_Character/00_Player/CustomController.h"
#include "03_Component/00_Character/QuickSlotComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Camera/CameraShakeBase.h"
#include "GameFramework/GameModeBase.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "03_Component/00_Character/StatusComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컨트롤러랑 Pawn이랑 같이 안 돌게 설정
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	ChargingParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ChargingParticleSystem"));
	ChargingParticleComponent->SetupAttachment(GetCapsuleComponent());

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;		// Controller에 맞춰서 SpringArm이 움직인다.

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);

	QuickSlotComponent = CreateDefaultSubobject<UQuickSlotComponent>(TEXT("QuickSlotComponent"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 플레이어 및 아군은 10으로 팀 설정
	SetGenericTeamId(10);
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// 플레이어 및 아군은 10으로 팀 설정
	SetGenericTeamId(10);
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	// 캐릭터가 에어본 상태가 아니고 행동을 안취하고 있으며 피격몽타주가 실행 되고 있지 않을 때만 피격 몽타주 실행
	if (characterState != ECharacterState::AIRBORNE
		&& actionState == EActionState::NORMAL)
		GetMesh()->GetAnimInstance()->Montage_Play(hitMontage);

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 차징 시간++
	if (attackState == EAttackState::CHARGING)
	{
		chargingTime += DeltaTime;
		chargingTime = FMath::Clamp(chargingTime, 1.f, 2.f);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 키 입력 관련 함수 바인드
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressAttack);
	PlayerInputComponent->BindAction("Dash", EInputEvent::IE_Pressed, this, &APlayerCharacter::Dash);
	PlayerInputComponent->BindAction("InterAction", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressInterActive);

	//PlayerInputComponent->BindAction<FShakeDelegate>("Attack", EInputEvent::IE_Pressed, this, &APlayerCharacter::CameraShakeDemo, 1.0f);
	PlayerInputComponent->BindAction<FShakeDelegate>("RightClick", EInputEvent::IE_Pressed, this, &APlayerCharacter::CameraShakeDemo, 0.1f);
#pragma region QuickSlotKey
	PlayerInputComponent->BindAction("Quick1", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot1);
	PlayerInputComponent->BindAction("Quick2", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot2);
	PlayerInputComponent->BindAction("Quick3", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot3);
	PlayerInputComponent->BindAction("Quick4", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot4);
	PlayerInputComponent->BindAction("Quick5", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot5);
	PlayerInputComponent->BindAction("Quick6", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot6);
	PlayerInputComponent->BindAction("Quick7", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot7);
	PlayerInputComponent->BindAction("Quick8", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot8);
	PlayerInputComponent->BindAction("Quick9", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot9);
	PlayerInputComponent->BindAction("Quick10", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot10);
	PlayerInputComponent->BindAction("Quick11", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot11);
	PlayerInputComponent->BindAction("Quick12", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot12);
	PlayerInputComponent->BindAction("Quick13", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot13);
	PlayerInputComponent->BindAction("Quick14", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot14);
	PlayerInputComponent->BindAction("Quick15", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot15);
	PlayerInputComponent->BindAction("Quick16", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressQuickSlot16);

	PlayerInputComponent->BindAction("Quick1", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot1);
	PlayerInputComponent->BindAction("Quick2", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot2);
	PlayerInputComponent->BindAction("Quick3", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot3);
	PlayerInputComponent->BindAction("Quick4", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot4);
	PlayerInputComponent->BindAction("Quick5", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot5);
	PlayerInputComponent->BindAction("Quick6", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot6);
	PlayerInputComponent->BindAction("Quick7", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot7);
	PlayerInputComponent->BindAction("Quick8", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot8);
	PlayerInputComponent->BindAction("Quick9", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot9);
	PlayerInputComponent->BindAction("Quick10", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot10);
	PlayerInputComponent->BindAction("Quick11", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot11);
	PlayerInputComponent->BindAction("Quick12", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot12);
	PlayerInputComponent->BindAction("Quick13", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot13);
	PlayerInputComponent->BindAction("Quick14", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot14);
	PlayerInputComponent->BindAction("Quick15", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot15);
	PlayerInputComponent->BindAction("Quick16", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseQuickSlot16);

#pragma endregion
	PlayerInputComponent->BindAction("SkillWindow", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressSkillWindow);
}


void APlayerCharacter::MoveForward(float newAxisValue)
{
	// 아무것도 안하고 있는 상태에서만 이동가능
	if (actionState == EActionState::NORMAL
		&& characterState == ECharacterState::NORMAL)
	{
		FRotator newRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector direction = FRotationMatrix(newRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, newAxisValue);
	}
}
void APlayerCharacter::MoveRight(float newAxisValue)
{
	// 아무것도 안하고 있는 상태에서만 이동가능
	if (actionState == EActionState::NORMAL
			&& characterState == ECharacterState::NORMAL)
	{
		FRotator newRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector direction = FRotationMatrix(newRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, newAxisValue);
	}
}
void APlayerCharacter::LookUp(float newAxisValue)
{
	AddControllerPitchInput(newAxisValue);
}
void APlayerCharacter::Turn(float newAxisValue)
{
	AddControllerYawInput(newAxisValue);
}

void APlayerCharacter::Dash()
{
	// 아무것도 안하고 있는 상태에서만 이동가능
	if(actionState == EActionState::NORMAL
			&& StatusComponent->CheckStamina(20))
	{
		// 스테미너 소모
		StatusComponent->AddStamina(-25.f);
		// 상태 변경
		SetMoveState(EMoveState::IDLE);
		SetActionState(EActionState::DASH);
		
		// 키 입력 방향으로 캐릭터 회전하기
		// 왼쪽 오른쪽 키 입력
		float moveRight = InputComponent->GetAxisValue("MoveRight");
		// 위 아래 키 입력
		float moveForward = InputComponent->GetAxisValue("MoveForward");
		// 키 입력을 벡터로 치환
		FVector keyDir = { moveForward, moveRight, 0 };
		FRotator keyRotator = keyDir.Rotation();
		keyRotator.Yaw += GetControlRotation().Yaw;
		SetActorRotation(keyRotator);

		// 대쉬 후 characterState Normal로 변경
		float animtime = GetMesh()->GetAnimInstance()->Montage_Play(DashMontage, 1.5f, EMontagePlayReturnType::Duration);
		FTimerHandle dashTimer;
		FTimerDelegate dashDelegate = FTimerDelegate::CreateUObject(this, &ABaseCharacter::SetActionState, EActionState::NORMAL);
		GetWorldTimerManager().SetTimer(
			dashTimer,
			dashDelegate,
			animtime,
			false);
	}
}

void APlayerCharacter::PressAttack()
{
	if (AttackMontage != nullptr 
			&& characterState == ECharacterState::NORMAL)
	{
		// 이미 공격 중이라면 콤보 공격
		if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
			bInputComboAttack = true;
		// 공격 중이 아니라면 공격 실행
		else
		{
			if(actionState == EActionState::NORMAL)
			{
				SetActionState(EActionState::ATTACK);
				GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage, 1.3f);
			}
		}
	}
}
#pragma region QuickSlotKey

void APlayerCharacter::PressQuickSlot1()
{
	GetQuickSlotComponent()->PressQuickSlot(0);
}

void APlayerCharacter::ReleaseQuickSlot1()
{
	
		GetQuickSlotComponent()->ReleaseQuickSlot(0);
}

void APlayerCharacter::PressQuickSlot2()
{
	GetQuickSlotComponent()->PressQuickSlot(1);
}

void APlayerCharacter::ReleaseQuickSlot2()
{
		GetQuickSlotComponent()->ReleaseQuickSlot(1);
}
void APlayerCharacter::PressQuickSlot3()
{
	GetQuickSlotComponent()->PressQuickSlot(2);
}

void APlayerCharacter::ReleaseQuickSlot3()
{
		GetQuickSlotComponent()->ReleaseQuickSlot(2);
}
void APlayerCharacter::PressQuickSlot4()
{
	GetQuickSlotComponent()->PressQuickSlot(3);
}

void APlayerCharacter::ReleaseQuickSlot4()
{
		GetQuickSlotComponent()->ReleaseQuickSlot(3);
}
void APlayerCharacter::PressQuickSlot5()
{
	GetQuickSlotComponent()->PressQuickSlot(4);
}

void APlayerCharacter::ReleaseQuickSlot5()
{
		GetQuickSlotComponent()->ReleaseQuickSlot(4);
}
void APlayerCharacter::PressQuickSlot6()
{
	GetQuickSlotComponent()->PressQuickSlot(5);
}

void APlayerCharacter::ReleaseQuickSlot6()
{
	GetQuickSlotComponent()->ReleaseQuickSlot(5);
}
void APlayerCharacter::PressQuickSlot7()
{
	GetQuickSlotComponent()->PressQuickSlot(6);
}

void APlayerCharacter::ReleaseQuickSlot7()
{
		GetQuickSlotComponent()->ReleaseQuickSlot(6);
}
void APlayerCharacter::PressQuickSlot8()
{
	GetQuickSlotComponent()->PressQuickSlot(7);
}

void APlayerCharacter::ReleaseQuickSlot8()
{
		GetQuickSlotComponent()->ReleaseQuickSlot(7);
}
void APlayerCharacter::PressQuickSlot9()
{
	GetQuickSlotComponent()->PressQuickSlot(8);
}

void APlayerCharacter::ReleaseQuickSlot9()
{
		GetQuickSlotComponent()->ReleaseQuickSlot(8);
}
void APlayerCharacter::PressQuickSlot10()
{
	GetQuickSlotComponent()->PressQuickSlot(9);
}

void APlayerCharacter::ReleaseQuickSlot10()
{
		GetQuickSlotComponent()->ReleaseQuickSlot(9);
}
void APlayerCharacter::PressQuickSlot11()
{
	GetQuickSlotComponent()->PressQuickSlot(10);
}

void APlayerCharacter::ReleaseQuickSlot11()
{
		GetQuickSlotComponent()->ReleaseQuickSlot(10);
}
void APlayerCharacter::PressQuickSlot12()
{
	GetQuickSlotComponent()->PressQuickSlot(11);
}

void APlayerCharacter::ReleaseQuickSlot12()
{
		GetQuickSlotComponent()->ReleaseQuickSlot(11);
}
void APlayerCharacter::PressQuickSlot13()
{
	GetQuickSlotComponent()->PressQuickSlot(12);
}

void APlayerCharacter::ReleaseQuickSlot13()
{
		GetQuickSlotComponent()->ReleaseQuickSlot(12);
}
void APlayerCharacter::PressQuickSlot14()
{
	GetQuickSlotComponent()->PressQuickSlot(13);
}

void APlayerCharacter::ReleaseQuickSlot14()
{
		GetQuickSlotComponent()->ReleaseQuickSlot(13);
}
void APlayerCharacter::PressQuickSlot15()
{
	GetQuickSlotComponent()->PressQuickSlot(14);
}

void APlayerCharacter::ReleaseQuickSlot15()
{
		GetQuickSlotComponent()->ReleaseQuickSlot(14);
}
void APlayerCharacter::PressQuickSlot16()
{
	GetQuickSlotComponent()->PressQuickSlot(15);
}

void APlayerCharacter::ReleaseQuickSlot16()
{
		GetQuickSlotComponent()->ReleaseQuickSlot(15);
}
#pragma endregion

void APlayerCharacter::PressSkillWindow()
{
	// 스킬 창 켜기
	Cast<ACustomController>(GetController())->OpenSkillWindow();
}

void APlayerCharacter::PressInterActive()
{
	// 상호작용 가능 한 Actor가 있는지 확인 후 상호작용
	if(interActionActor != nullptr)
		interActionActor->InterAction(this);
}


void APlayerCharacter::CameraShakeDemo(float scale)
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake( CamSake, scale);
}


void APlayerCharacter::SetMoveState(EMoveState state)
{
	moveState = state;

	switch(state)
	{
	case EMoveState::IDLE:
		break;
	}
}

void APlayerCharacter::SetActionState(EActionState state)
{
	actionState = state;

	switch (state)
	{
	case EActionState::NORMAL:
		// AttackState 및 차징 시간 초기화
		SetAttackState(EAttackState::NORMAL);
		chargingTime = 0.f;
		break;
	}
}

void APlayerCharacter::SetAttackState(EAttackState state)
{
	Super::SetAttackState(state);

	switch(state)
	{
	case EAttackState::NORMAL:
		// 차징 Particle 끄기
		ChargingParticleComponent->Deactivate();
		break;
	case EAttackState::CHARGING:
		// 차징 Particle 켜기
		ChargingParticleComponent->Activate();
		break;
	case EAttackState::ATTACK:

		break;
	}
}

void APlayerCharacter::TakeStun(float stunTime)
{
	Super::TakeStun(stunTime);

	// 마지막 스턴을 기준으로 타이머 시간 설정
	if (GetWorldTimerManager().TimerExists(StunTimerHandle))
	{
		float remainTime = GetWorldTimerManager().GetTimerRemaining(StunTimerHandle);
		if (remainTime < stunTime)
		{
			GetWorldTimerManager().ClearTimer(StunTimerHandle);

			// 죽지 않았다면 일정 시간 후에 로직 재시작 타이머 설정
			FTimerDelegate hitDelegate;
			hitDelegate.BindUObject(this, &ABaseCharacter::SetCharacterState, ECharacterState::NORMAL);
			GetWorldTimerManager().SetTimer(StunTimerHandle, hitDelegate, stunTime, false);
		}
	}
	else
	{
		// 스턴 타이머 설정
		FTimerDelegate hitDelegate;
		hitDelegate.BindUObject(this, &ABaseCharacter::SetCharacterState, ECharacterState::NORMAL);
		GetWorldTimerManager().SetTimer(StunTimerHandle, hitDelegate, stunTime, false);
	}
}

void APlayerCharacter::TakeAirborne(float airbornePower, float stunTime)
{
	Super::TakeAirborne(airbornePower, stunTime);

	// 이미 스턴이 돌고 있다면 현재 스턴의 남은 시간과 새로 들어온 스턴 시간 중 더 큰 것을 타이머 시간으로 설정
	float time = stunTime;
	if (GetWorldTimerManager().TimerExists(StunTimerHandle))
	{
		float remainTimer = GetWorldTimerManager().GetTimerRemaining(StunTimerHandle);;
		if (remainTimer > time)
			time = remainTimer;
		GetWorldTimerManager().ClearTimer(StunTimerHandle);
	}

	// 죽지 않았다면 일정 시간 후에 로직 재시작 타이머 설정
	if (!isDead)
	{
		FTimerDelegate hitDelegate;
		hitDelegate.BindUObject(this, &APlayerCharacter::StandUp);
		GetWorldTimerManager().SetTimer(StunTimerHandle, hitDelegate, stunTime, false);
	}
}

void APlayerCharacter::StandUp()
{
	Super::StandUp();
}


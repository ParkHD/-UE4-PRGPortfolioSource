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
#include "Blueprint/AIBlueprintHelperLibrary.h"

APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컨트롤러랑 Pawn이랑 같이 돌것인가
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	WeaponSkeletalMesh->SetupAttachment(GetMesh(), "S_Sword");

	niagaraSys = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraSystem"));
	niagaraSys->SetupAttachment(GetCapsuleComponent());

	ChargingParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ChargingParticleSystem"));
	ChargingParticleComponent->SetupAttachment(GetCapsuleComponent());
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;	// Controller에 맞춰서 SpringArm이 움직인다.
	//SpringArm->bInheritPitch = true;			// Y Controller에서 Y축은 안받아옴
	//SpringArm->bInheritRoll = true;				// X
	//SpringArm->bInheritYaw = true;				// Z
	SpringArm->bDoCollisionTest = true;			// 시야에 방해물이 있으면 확대기능

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);

	QuickSlotComponent = CreateDefaultSubobject<UQuickSlotComponent>(TEXT("QuickSlotComponent"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->FallingLateralFriction = 8.f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	//PlayerInputComponent->BindAction("Move", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseMove);

	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressAttack);
	PlayerInputComponent->BindAction("Dash", EInputEvent::IE_Pressed, this, &APlayerCharacter::Dash);
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

void APlayerCharacter::PlayChargingParticle()
{
	ChargingParticleComponent->Activate(false);
}

void APlayerCharacter::MoveForward(float newAxisValue)
{
	if (actionState == EActionState::NORMAL)
	{
		FRotator newRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector direction = FRotationMatrix(newRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, newAxisValue);
	}
}
void APlayerCharacter::MoveRight(float newAxisValue)
{
	if (actionState == EActionState::NORMAL)
	{
		FRotator newRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector direction = FRotationMatrix(newRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), newAxisValue);
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
void APlayerCharacter::ReleaseMove()
{
	if(actionState == EActionState::NORMAL)
	{
		FHitResult hit;
		if (GetController<APlayerController>()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, hit))
		{
			//// 이미 클릭 효과가 실행되고 있다면 중단 하고 새롭게 클릭된 곳에 효과 실행
			//if (clickNiagaraComponent != nullptr)
			//{
			//	clickNiagaraComponent->DeactivateImmediate();
			//}
			//clickNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), clickParticle, hit.Location);
			// 캐릭터 이동
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), hit.Location);
		}
	}
}
void APlayerCharacter::Dash()
{
	if(actionState == EActionState::NORMAL)
	{
		SetMoveState(EMoveState::IDLE);
		SetActionState(EActionState::DASH);
		TurnToCursor();
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
	if (AttackMontage != nullptr)
	{
		if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
			bInputComboAttack = true;
		else
		{
			if(actionState == EActionState::NORMAL)
			{
				SetActionState(EActionState::ATTACK);
				TurnToCursor();
				GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
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
	Cast<ACustomController>(GetController())->OpenSkillWindow();
}

void APlayerCharacter::TurnToCursor()
{/*
	FHitResult hit;
	if (GetController<APlayerController>()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, hit))
	{
		FVector dirCursor = hit.Location - GetActorLocation();
		FRotator newRotation(0.f, dirCursor.Rotation().Yaw, 0.f);
		SetActorRotation(newRotation);
	}*/
}

void APlayerCharacter::CameraShakeDemo(float scale)
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake( CamSake, scale);
}
void APlayerCharacter::InitChargingSkill()
{
	chargingTime = 0.f;
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
		ChargingParticleComponent->Deactivate();
		break;
	case EAttackState::CHARGING:
		ChargingParticleComponent->Activate();
		break;
	case EAttackState::ATTACK:

		break;
	}
}


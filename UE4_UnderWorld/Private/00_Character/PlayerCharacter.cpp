// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"

APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컨트롤러랑 Pawn이랑 같이 돌것인가
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	niagaraSys = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraSystem"));
	niagaraSys->SetupAttachment(GetCapsuleComponent());

	particleSys = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	particleSys->SetupAttachment(GetCapsuleComponent());
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

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->FallingLateralFriction = 8.f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressAttack);
	PlayerInputComponent->BindAction("Dash", EInputEvent::IE_Pressed, this, &APlayerCharacter::Dash);
}

void APlayerCharacter::MoveForward(float newAxisValue)
{
	FRotator newRotation(0.0f, GetControlRotation().Yaw, 0.0f);
	FVector direction = FRotationMatrix(newRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(direction, newAxisValue);
}
void APlayerCharacter::MoveRight(float newAxisValue)
{
	FRotator newRotation(0.0f, GetControlRotation().Yaw, 0.0f);
	FVector direction = FRotationMatrix(newRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), newAxisValue);
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
	GetMesh()->GetAnimInstance()->Montage_Play(DashMontage, 1.5f);
	LaunchCharacter(GetActorForwardVector().GetSafeNormal() * DashSpeed, true, true);
}

void APlayerCharacter::PressAttack()
{
	if (AttackMontage != nullptr)
	{
		if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
			bInputComboAttack = true;
		else
		{
			FRotator newRotation(0.f, GetControlRotation().Yaw, 0.f);
			SetActorRotation(newRotation);
			GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
		}
	}
}
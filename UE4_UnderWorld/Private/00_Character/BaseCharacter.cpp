// Fill out your copyright notice in the Description page of Project Settings.

#include "00_Character/BaseCharacter.h"
#include "Components/ChildActorComponent.h"
#include "03_Component/00_Character/StatusComponent.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
	SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("SkillComponent"));
	
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	// 소리 범위 설정
	USoundAttenuation* soundAtt = NewObject<USoundAttenuation>();
	FSoundAttenuationSettings setting;
	setting.FalloffDistance = falloffDistance;
	soundAtt->Attenuation = setting;
	AudioComponent->AttenuationSettings = soundAtt;

	WeaponChildActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	WeaponChildActorComponent->SetupAttachment(GetMesh(), FName("Weapon_Socket"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	StatusComponent->AddHP(-DamageAmount);
	AudioComponent->SetSound(hitSound);
	AudioComponent->Activate();

	return DamageAmount;
}
void ABaseCharacter::BeginHitStop()
{
	CustomTimeDilation = 0.001f;
	//
	float hitstopTime = hitstopModifier;
	GetWorld()->GetTimerManager().SetTimer(hitstopTimerHandle, this, &ABaseCharacter::EndHitStop, hitstopTime, false);
}
void ABaseCharacter::EndHitStop()
{
	CustomTimeDilation = 1.f;

}

void ABaseCharacter::SetActionState(EActionState state)
{
	actionState = state;
	switch (state)
	{
	case EActionState::ATTACK:
		SetMoveState(EMoveState::IDLE);
		break;
	case EActionState::SKILL:
		SetMoveState(EMoveState::IDLE);
		break;
	}
}

void ABaseCharacter::SetMoveState(EMoveState state)
{
	moveState = state;
	switch(state)
	{
	case EMoveState::IDLE:
		GetCharacterMovement()->Velocity = FVector::ZeroVector;
		break;
	}
}

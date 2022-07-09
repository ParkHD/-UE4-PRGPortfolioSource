// Fill out your copyright notice in the Description page of Project Settings.

#include "00_Character/BaseCharacter.h"
#include "Components/ChildActorComponent.h"
#include "03_Component/00_Character/StatusComponent.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
	SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("SkillComponent"));

	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	WeaponSkeletalMesh->SetupAttachment(GetMesh(), "S_Sword");

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	// 소리 범위 설정
	USoundAttenuation* soundAtt = NewObject<USoundAttenuation>();
	FSoundAttenuationSettings setting;
	setting.FalloffDistance = falloffDistance;
	soundAtt->Attenuation = setting;
	AudioComponent->AttenuationSettings = soundAtt;

	WeaponChildActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	WeaponChildActorComponent->SetupAttachment(GetMesh(), FName("Weapon_Socket"));

	HPBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HPBarWidgetComponent->SetDrawSize(FVector2D(100.f, 10.f));
	HPBarWidgetComponent->SetupAttachment(RootComponent);
	HPBarWidgetComponent->SetVisibility(false);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;	// 움직이는 방향으로 캐릭터 회전
	GetCharacterMovement()->FallingLateralFriction = 8.f;		// 공중에서도 마찰 높이기

	GetCharacterMovement()->RotationRate = { 0,720.f,0 };
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

	if(isAirborne)
	{
		LaunchMesh(200, 5.f);
		UE_LOG(LogTemp, Log, TEXT("0"));
	}

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (isDead)
		return 0.f;
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 피격 애님
	if (characterState != ECharacterState::AIRBORNE
			&& actionState == EActionState::NORMAL)
		GetMesh()->GetAnimInstance()->Montage_Play(hitMontage);

	StatusComponent->AddHP(-DamageAmount);
	AudioComponent->SetSound(hitSound);
	AudioComponent->Activate();

	// 힛스탑
	BeginHitStop();

	return DamageAmount;
}

float ABaseCharacter::CustomTakeDamage(EAttackType type, float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser, float value)
{
	float damage = TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(!isDead)
	{
		switch(type)
		{
		case EAttackType::NORMAL:
			{
			
			}
			break;
		case EAttackType::KNOCKBACK:
			{
				
				FVector knockbackDir = GetActorLocation() - DamageCauser->GetActorLocation();
				LaunchCharacter(knockbackDir.GetSafeNormal(1.f) * value, true, true);
			}
			break;
		case EAttackType::AIRBORNE :
			{
				TakeAirborne(200, value);
				LaunchMesh(200, 5.f);
			}
			break;
		}
	}

	return damage;
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

void ABaseCharacter::SetAttackState(EAttackState state)
{
	attackState = state;
}

void ABaseCharacter::SetCharacterState(ECharacterState state)
{
	characterState = state;
}

void ABaseCharacter::TakeStun(float stunTime)
{
	if(characterState == ECharacterState::NORMAL)
		SetCharacterState(ECharacterState::STUN);
}

void ABaseCharacter::TakeAirborne(float airbornePower, float stunTime)
{
	if (GetWorldTimerManager().IsTimerActive(standUpTimer))
		GetWorldTimerManager().ClearTimer(standUpTimer);

	GetMesh()->GetAnimInstance()->Montage_Stop(1.f);

	SetCharacterState(ECharacterState::AIRBORNE);

	isAirborne = true;
	isLevitate = true;
}

void ABaseCharacter::OnDead()
{
}

void ABaseCharacter::InitState()
{
	moveState = EMoveState::IDLE;
	actionState = EActionState::NORMAL;
	attackState = EAttackState::CHARGING;
}

void ABaseCharacter::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	myTeam = TeamID;
}

void ABaseCharacter::LaunchMesh(float zValue, float interpSpeed)
{
	FVector newLocation = GetMesh()->GetRelativeLocation();

	if(isLevitate)
		newLocation.Z += interpSpeed;
	else
		newLocation.Z -= interpSpeed;

	GetMesh()->SetRelativeLocation(newLocation);

	if (GetMesh()->GetRelativeLocation().Z > zValue)
		isLevitate = false;
	else if(GetMesh()->GetRelativeLocation().Z <= -90)
		isAirborne = false;
}

void ABaseCharacter::StandUp()
{
	float time = GetMesh()->GetAnimInstance()->Montage_Play(StandUpMontage);
	// 로직 멈추기
	FTimerDelegate standUpdelegate = FTimerDelegate::CreateUObject(
		this, &ABaseCharacter::SetCharacterState, ECharacterState::NORMAL);

	GetWorldTimerManager().SetTimer(standUpTimer, standUpdelegate, time, false);
}

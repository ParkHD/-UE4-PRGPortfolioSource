// Fill out your copyright notice in the Description page of Project Settings.

#include "00_Character/BaseCharacter.h"

#include "00_Character/00_Player/PlayerCharacter.h"
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
	
	// 무기 스켈레탈 설정
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

	// HPBar 위젯 설정
	HPBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HPBarWidgetComponent->SetDrawSize(FVector2D(100.f, 10.f));
	HPBarWidgetComponent->SetupAttachment(RootComponent);
	HPBarWidgetComponent->SetVisibility(false);

	bUseControllerRotationYaw = false;				// 컨트롤러와 캐릭터가 같이 움직일 것인가? X
	GetCharacterMovement()->bOrientRotationToMovement = true;	// 움직이는 방향으로 캐릭터 회전
	GetCharacterMovement()->FallingLateralFriction = 8.f;		// 공중에서도 마찰 높이기
	// 회전 속도 설정
	GetCharacterMovement()->RotationRate = { 0,720.f,0 };
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	StatusComponent->Init();			// 스텟 초기화
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 에어본 상태라면 캐릭터의 스켈레탈 매쉬를 위로 띄운다.
	if(isAirborne)
	{
		LaunchMesh(200, 5.f);
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 캐릭터가 죽어있는 상태인지 확인
	if (isDead)
		return 0.f;
	
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// HP 설정
	StatusComponent->AddHP(-DamageAmount);
	
	// 사운드 설정 및 플레이
	AudioComponent->SetSound(hitSound);
	AudioComponent->Activate();

	// 힛스탑 실행
	BeginHitStop();

	return DamageAmount;
}

float ABaseCharacter::CustomTakeDamage(EAttackType type, float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser, float value)
{
	float damage = TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 죽었는 지 확인
	if(!isDead)
	{
		switch(type)
		{
		// 기본 공격 타입이라면
		case EAttackType::NORMAL:
			{
				// 플레이어에게 대미지를 입었다면 플레이어의 MP 충전
				if (DamageCauser->IsA<APlayerCharacter>())
					Cast<APlayerCharacter>(DamageCauser)->GetStatusComponent()->AddMP(5.f);
			}
			break;
		// 넉백 타입의 공격
		case EAttackType::KNOCKBACK:
			{
				// 보스 캐릭터가 아니라면 캐릭터 넉백
				if(!isBoss)
				{
					FVector knockbackDir = GetActorLocation() - DamageCauser->GetActorLocation();
					LaunchCharacter(knockbackDir.GetSafeNormal(1.f) * value, true, true);
				}
			}
			break;
		// 에어본 타입의 공격
		case EAttackType::AIRBORNE :
			{
				// 보스 캐릭터가 아니라면 캐릭터 에어본
				if(!isBoss)
				{
					TakeAirborne(200, value);
					LaunchMesh(200, 5.f);
				}
			}
			break;
		}
	}

	return damage;
}

void ABaseCharacter::BeginHitStop()
{
	// 캐릭터의 속도를 낮춰서 멈춰있는 것처럼 표현
	CustomTimeDilation = 0.001f;
	// 일정시간 후에 캐릭터를 다시 원래 속도록 재생
	float hitstopTime = hitstopModifier;
	GetWorld()->GetTimerManager().SetTimer(hitstopTimerHandle, this, &ABaseCharacter::EndHitStop, hitstopTime, false);
}
void ABaseCharacter::EndHitStop()
{
	// 캐릭터 속도 원상복귀
	CustomTimeDilation = 1.f;
}

void ABaseCharacter::SetActionState(EActionState state)
{
	actionState = state;
	
	// AciontState를 설정하면 행동상태 초기화
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
	// 이동 상태에 따른 캐릭터 속도 설정
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
	// 현재 일어나려고 하는 중이라면 다시 초기화
	if (GetWorldTimerManager().IsTimerActive(standUpTimer))
		GetWorldTimerManager().ClearTimer(standUpTimer);

	// 실행 중인 몽타주 종류
	GetMesh()->GetAnimInstance()->Montage_Stop(1.f);

	SetCharacterState(ECharacterState::AIRBORNE);
	
	// 에어본 설정
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

	// 일정 높이만큼 캐릭터를 띄우고 일정 높이가 넘으면 캐릭터를 아래로 내려놓는다.
	if(isLevitate)
		newLocation.Z += interpSpeed;
	else
		newLocation.Z -= interpSpeed;

	GetMesh()->SetRelativeLocation(newLocation);

	// 캐릭터가 띄어진 높이에 따른 설정	
	if (GetMesh()->GetRelativeLocation().Z > zValue)
		isLevitate = false;
	else if(GetMesh()->GetRelativeLocation().Z <= -90)
		isAirborne = false;
}

void ABaseCharacter::StandUp()
{
	// 일어나는 몽타주 실행 후 캐릭터 상태 초기화
	float time = GetMesh()->GetAnimInstance()->Montage_Play(StandUpMontage);
	FTimerDelegate standUpdelegate = FTimerDelegate::CreateUObject(
		this, &ABaseCharacter::SetCharacterState, ECharacterState::NORMAL);
	GetWorldTimerManager().SetTimer(standUpTimer, standUpdelegate, time, false);
}

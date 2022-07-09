// Fill out your copyright notice in the Description page of Project Settings.


#include "05_Actor/02_SkillRangeActor/SkillRangeActor.h"

#include "NiagaraComponent.h"
#include "00_Character/BaseCharacter.h"
#include "99_GameMode/MyGameMode.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASkillRangeActor::ASkillRangeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;
	CapsuleComponent->SetCollisionProfileName("NoCollision");

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	DecalComponent->SetupAttachment(RootComponent);
	DecalComponent->SetRelativeRotation({ 90.f, 0.f, 0.f });

	SkillParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	SkillParticleComponent->SetupAttachment(RootComponent);
	SkillParticleComponent->bAutoActivate = false;

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	audioComponent->SetupAttachment(RootComponent);
	audioComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ASkillRangeActor::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddUniqueDynamic(this, &ASkillRangeActor::OnActorOverlapEvent);

	// 타이머를 이용 해서 일정 시간후에 콜리전을 켜서 상대에게 대미지를 준다.
	FTimerHandle attackTimer;
	FTimerDelegate  attackDelegate = FTimerDelegate::CreateUObject(
		this, &ASkillRangeActor::AttackRange);
	GetWorldTimerManager().SetTimer(
		attackTimer,
		attackDelegate,
		attackDelay,
		false);
}

void ASkillRangeActor::OnActorOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	// overlap되면 대미지를 준다.
	if(OtherActor->IsA<ABaseCharacter>())
	{
		auto target = Cast<ABaseCharacter>(OtherActor);
		auto owner = GetOwner<ABaseCharacter>();
		if(target != nullptr && owner != nullptr)
		{
			// 처음 공격한 대상이며 적군인지 검사
			if(target->GetGenericTeamId() != owner->GetGenericTeamId()
				&& !hitActors.Contains(target))
			{
				target->CustomTakeDamage(attackType, damageAmount, FDamageEvent(), owner->GetController(), owner, damageValue);
				hitActors.Emplace(target);
			}
		}
	}
}

// Called every frame
void ASkillRangeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkillRangeActor::AttackRange()
{
	CapsuleComponent->SetCollisionProfileName("Projectile");

	SkillParticleComponent->Activate(false);
	
	DecalComponent->Deactivate();
	DecalComponent->SetVisibility(false);
	audioComponent->Activate();

	CapsuleComponent->SetCollisionProfileName("NoCollision");

	// 카메라 쉐이크
	Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->CameraShake(cameraShakeScale);

	//Destroy();
}

void ASkillRangeActor::SetDamage(float damage)
{
	damageAmount = damage;
}

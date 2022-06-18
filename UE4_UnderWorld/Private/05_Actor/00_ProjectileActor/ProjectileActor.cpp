// Fill out your copyright notice in the Description page of Project Settings.


#include "05_Actor/00_ProjectileActor/ProjectileActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystem.h"
#include "00_Character/BaseCharacter.h"
#include "Components/AudioComponent.h"
#include "NiagaraComponent.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SphereComponent"));
	sphereComponent->SetCollisionProfileName("NoCollision");
	RootComponent = sphereComponent;

	skeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	skeletalMeshComponent->SetCollisionProfileName("NoCollision");
	skeletalMeshComponent->SetupAttachment(RootComponent);

	particleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	particleComponent->SetupAttachment(RootComponent);
	niagaraSys = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraSystem"));
	niagaraSys->SetupAttachment(RootComponent);

	projectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	projectileComponent->ProjectileGravityScale = 0.f;

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	audioComponent->SetupAttachment(RootComponent);
	audioComponent->bOverrideAttenuation = true;

	// 이동방향으로 회전
	projectileComponent->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	sphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AProjectileActor::OnComponentBeginOverlapEvent);
	if (bLifeSpan)
	{
		// 생명주기 설정
		SetLifeSpan(lifeSpanValue);
	}
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileActor::OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto myCharacter = Cast<ABaseCharacter>(GetOwner());
	if (myCharacter != OtherActor)
	{
		if (!hitActors.Contains(OtherActor))
		{
			hitActors.Emplace(OtherActor);
			// overlap 효과 재생
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitParticle, SweepResult.Location, FRotator::ZeroRotator, true);

			// 멀티공격이 아니라면 콜리전을 꺼서 다중공격 방지
			if (bHitSingle)
			{
				sphereComponent->SetCollisionProfileName("NoCollision");
				projectileComponent->Velocity = FVector::ZeroVector;
				audioComponent->VolumeMultiplier = 0.f;
			}

			if (OtherActor->IsA<ABaseCharacter>())
			{
				// 캐릭터라면 대미지 주기
				auto targetCharacter = Cast<ABaseCharacter>(OtherActor);
				//if (targetCharacter != myCharacter && targetCharacter->GetGenericTeamId() != myCharacter->GetGenericTeamId())
				//{
				//	FDamageEvent damageEvent;
				//	/*EDamageType damageType = isSkill ? EDamageType::SKILL : EDamageType::NORMAL;
				//	targetCharacter->TakeDamageType(damageType, skillDamage
				//		, damageEvent, myCharacter->GetController(), myCharacter);*/
				//}
			}
		}

	}
}

void AProjectileActor::TurnOnCollision(bool bTurn)
{
	//sphereComponent->SetCollisionProfileName("Weapon");
}
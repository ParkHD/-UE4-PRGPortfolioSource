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
#include "NiagaraFunctionLibrary.h"
#include "99_GameMode/MyGameMode.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SphereComponent"));
	//sphereComponent->SetCollisionProfileName("NoCollision");
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
	
	// 자신을 제외한 캐릭터에 대미지를 줄것이다.
	// owner가 같다면 반응을 안한다.
	if (OtherActor->GetOwner() != GetOwner() && myCharacter != OtherActor)
	{
		// 지형지물에 닿았다면 destroy
		if (OtherComp->GetCollisionObjectType() == ECC_WorldStatic)
			Destroy();
		// 대미지 중복 방지
		if (!hitActors.Contains(OtherActor))
		{
			hitActors.Emplace(OtherActor);

			// overlap 효과 재생
			if (!isExplored)
			{
				// 터지는 Particle 재생
				if(hitParticle != nullptr)
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitParticle, SweepResult.Location, FRotator::ZeroRotator, true);
				else if(hitParticle_Nia != nullptr)
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitParticle_Nia, SweepResult.Location);
				// 소리 범위 설정
				USoundAttenuation* soundAtt = NewObject<USoundAttenuation>();
				FSoundAttenuationSettings setting;
				setting.FalloffDistance = falloffDistance;
				soundAtt->Attenuation = setting;
				// 터지는 사운드 재생
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), soundToPlay, SweepResult.Location, FRotator::ZeroRotator,
					1.f, 1.f, 0.f, soundAtt);

				// 카메라 쉐이크
				Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->CameraShake(1.f);
				isExplored = true;
			}

			// 멀티공격이 아니라면 콜리전을 꺼서 다중공격 방지
			if (bHitSingle)
			{
				sphereComponent->SetCollisionProfileName("NoCollision");
				projectileComponent->Velocity = FVector::ZeroVector;
				audioComponent->VolumeMultiplier = 0.f;
				Destroy();
			}
			
			// 대상이 캐릭터라면 대미지 주기
			if (OtherActor->IsA<ABaseCharacter>())
			{
				auto targetCharacter = Cast<ABaseCharacter>(OtherActor);
				//targetCharacter->TakeDamage(damage, FDamageEvent(), myCharacter->GetController(), myCharacter);
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
	if(bTurn)
		sphereComponent->SetCollisionProfileName("Projectile");
	else
		sphereComponent->SetCollisionProfileName("NoCollision");
}
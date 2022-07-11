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

	

	// �̵��������� ȸ��
	projectileComponent->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	sphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AProjectileActor::OnComponentBeginOverlapEvent);

	if (bLifeSpan)
	{
		// �����ֱ� ����
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
	if (myCharacter != nullptr)
	{
		
		// ĳ���Ͷ��?
		if(OtherActor->IsA<ABaseCharacter>())
		{
			// �� ĳ���Ϳ��� ������� �ش�.
			auto target = Cast<ABaseCharacter>(OtherActor);
			if(target != nullptr
				&& target->GetGenericTeamId() != myCharacter->GetGenericTeamId())
			{
				// ����� �ߺ� ����
				if (!hitActors.Contains(target))
				{
					hitActors.Emplace(target);
					target->CustomTakeDamage(EAttackType::NORMAL, damage, FDamageEvent(), myCharacter->GetController(), myCharacter, 0);

					Explored(SweepResult.Location);

					// ��Ƽ������ �ƴ϶�� �ݸ����� ���� ���߰��� ����
					if (bHitSingle)
					{
						sphereComponent->SetCollisionProfileName("NoCollision");
						projectileComponent->Velocity = FVector::ZeroVector;
						audioComponent->VolumeMultiplier = 0.f;
						Destroy();
					}
				}
			}
		}
		else
		{
			Explored(SweepResult.Location);
			Destroy();
		}
	}
}
void AProjectileActor::Explored(FVector Location)
{
	// overlap ȿ�� ���
	if (!isExplored)
	{
		// ������ Particle ���
		if (hitParticle != nullptr)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitParticle, Location, FRotator::ZeroRotator, true);
		else if (hitParticle_Nia != nullptr)
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitParticle_Nia, Location);
		// �Ҹ� ���� ����
		USoundAttenuation* soundAtt = NewObject<USoundAttenuation>();
		FSoundAttenuationSettings setting;
		setting.FalloffDistance = falloffDistance;
		soundAtt->Attenuation = setting;
		// ������ ���� ���
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), soundToPlay, Location, FRotator::ZeroRotator,
			1.f, 1.f, 0.f, soundAtt);

		// ī�޶� ����ũ
		Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->CameraShake(1.f);
		isExplored = true;
	}
}

void AProjectileActor::TurnOnCollision(bool bTurn)
{
	if(bTurn)
		sphereComponent->SetCollisionProfileName("Projectile");
	else
		sphereComponent->SetCollisionProfileName("NoCollision");
}


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
	
	// �ڽ��� ������ ĳ���Ϳ� ������� �ٰ��̴�.
	// owner�� ���ٸ� ������ ���Ѵ�.
	if (OtherActor->GetOwner() != GetOwner() && myCharacter != OtherActor)
	{
		// ���������� ��Ҵٸ� destroy
		if (OtherComp->GetCollisionObjectType() == ECC_WorldStatic)
			Destroy();
		// ����� �ߺ� ����
		if (!hitActors.Contains(OtherActor))
		{
			hitActors.Emplace(OtherActor);
			// overlap ȿ�� ��� �ѹ���
			if (!isExplored)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitParticle, SweepResult.Location, FRotator::ZeroRotator, true);
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitParticle_Nia, SweepResult.Location);
			
				Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->CameraShake(1.f);
				isExplored = true;
			}
			// ��Ƽ������ �ƴ϶�� �ݸ����� ���� ���߰��� ����
			if (bHitSingle)
			{
				sphereComponent->SetCollisionProfileName("NoCollision");
				projectileComponent->Velocity = FVector::ZeroVector;
				audioComponent->VolumeMultiplier = 0.f;
			}
			
			// ĳ���Ͷ�� ����� �ֱ�
			if (OtherActor->IsA<ABaseCharacter>())
			{
				auto targetCharacter = Cast<ABaseCharacter>(OtherActor);
				targetCharacter->TakeDamage(damage, FDamageEvent(), myCharacter->GetController(), myCharacter);
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
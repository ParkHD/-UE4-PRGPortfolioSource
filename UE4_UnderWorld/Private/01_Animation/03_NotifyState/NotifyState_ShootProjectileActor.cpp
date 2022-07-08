// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/03_NotifyState/NotifyState_ShootProjectileActor.h"

#include "00_Character/BaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/01_Monster/MonsterController.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "03_Component/00_Character/StatusComponent.h"
#include "05_Actor/00_ProjectileActor/ProjectileActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
void UNotifyState_ShootProjectileActor::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp != nullptr)
	{
		owner = MeshComp->GetOwner<ABaseCharacter>();
		if (owner != nullptr)
		{
			FVector spawnLocation;	// 스폰할 위치
			FRotator spawnRotator;	// 스폰할 회전값

			// 소켓네임이 없다면 캐릭터의 일정거리 앞으로 생성할 위치 설정
			if (spawnSocketName.IsNone())
			{
				// 캐릭터의 일정거리 앞으로 생성
				spawnLocation = owner->GetActorLocation() + owner->GetActorForwardVector() * 150.f;
				spawnRotator = owner->GetActorRotation() + spawnRotation;
			}
			// 소켓네임이 있다면 소켓을 기준으로 생성할 위치 설정
			else
			{
				// 입력받은 소켓의 위치로 생성
				spawnLocation = MeshComp->GetSocketLocation(spawnSocketName);
				spawnRotator = MeshComp->GetSocketRotation(spawnSocketName);
			}

			// ProjectileActor 소환 및 설정
			projectileActor = owner->GetWorld()->SpawnActor<AProjectileActor>(ActorToSpawn);
			if (spawnSocketName.IsNone())
			{
				projectileActor->SetActorLocation(spawnLocation);
				projectileActor->SetActorRotation(spawnRotator);
			}
			else
			{
				projectileActor->AttachToComponent(MeshComp, FAttachmentTransformRules::KeepRelativeTransform, spawnSocketName);
			}
			projectileActor->SetOwner(owner);

			// ProjectileActor의 대미지 계산 및 적용
			float damage = owner->GetStatusComponent()->GetStat().Damage;
			if(isSkill)
			{
				auto skillInfo = owner->GetSkillComponent()->GetSkillInfo(skill_Tag);
				if (skillInfo != nullptr)
					damage = damage * skillInfo->skill_Damage / 100;
			}
			projectileActor->SetDamage(damage);
			projectileDir = GetShotDir(owner);
		}
	}
}

void UNotifyState_ShootProjectileActor::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UNotifyState_ShootProjectileActor::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (owner != nullptr)
	{
		// 발사할 방향 설정
		if (spawnSocketName.IsNone())
		{
			// 입력받은 소켓이름이 없다면 캐릭터의 Forward방향으로 발사
			projectileDir = owner->GetActorForwardVector();
		}
		else
		{
			//projectileDir = GetShotDir(owner);
			// 발사하기 전에 소켓에서 떼어내기
			projectileActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		}

		// ProjectileActor 콜리전 활성화 및 발사
		projectileActor->TurnOnCollision(true);
		projectileActor->GetProjectileComponent()->Velocity = projectileDir * projectileSpeed;
	}
}

FVector UNotifyState_ShootProjectileActor::GetShotDir(ABaseCharacter* characterOwner)
{
	FVector shotDir;
	// owner가 player라면 카메라가 바라보고 있는 방향으로 Ray를 쏴서 Hit된 Actor를 기준으로 방향 설정 
	if (characterOwner->IsA<APlayerCharacter>())
	{
		
	}
	// owner가 AI라면 블랙보드에서 타겟을 기준으로 방향을 설정
	else if (characterOwner->IsA<AMonsterCharacter>())
	{
		auto monController = characterOwner->GetController<AMonsterController>();
		if (monController != nullptr)
		{
			auto target = monController->GetBlackboardComponent()->GetValueAsObject("Target");
			if (target != nullptr)
			{
				// 블랙보드에 저장된 타겟 방향으로 발사
				shotDir = Cast<AActor>(target)->GetActorLocation() - characterOwner->GetActorLocation();
				shotDir = shotDir.GetUnsafeNormal();
			}
			// 블랙보드에 저장된 타겟이 없다면 정면으로 발사
			else
			{
				shotDir = characterOwner->GetActorForwardVector();
				shotDir = shotDir.GetUnsafeNormal();
			}
		}
	}
	return shotDir;
}
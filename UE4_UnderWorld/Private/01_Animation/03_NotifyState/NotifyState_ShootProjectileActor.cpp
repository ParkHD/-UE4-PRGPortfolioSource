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
			FVector spawnLocation;	// ������ ��ġ
			FRotator spawnRotator;	// ������ ȸ����

			// ���ϳ����� ���ٸ� ĳ������ �����Ÿ� ������ ������ ��ġ ����
			if (spawnSocketName.IsNone())
			{
				// ĳ������ �����Ÿ� ������ ����
				spawnLocation = owner->GetActorLocation() + owner->GetActorForwardVector() * 150.f;
				spawnRotator = owner->GetActorRotation() + spawnRotation;
			}
			// ���ϳ����� �ִٸ� ������ �������� ������ ��ġ ����
			else
			{
				// �Է¹��� ������ ��ġ�� ����
				spawnLocation = MeshComp->GetSocketLocation(spawnSocketName);
				spawnRotator = MeshComp->GetSocketRotation(spawnSocketName);
			}

			// ProjectileActor ��ȯ �� ����
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

			// ProjectileActor�� ����� ��� �� ����
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
		// �߻��� ���� ����
		if (spawnSocketName.IsNone())
		{
			// �Է¹��� �����̸��� ���ٸ� ĳ������ Forward�������� �߻�
			projectileDir = owner->GetActorForwardVector();
		}
		else
		{
			//projectileDir = GetShotDir(owner);
			// �߻��ϱ� ���� ���Ͽ��� �����
			projectileActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		}

		// ProjectileActor �ݸ��� Ȱ��ȭ �� �߻�
		projectileActor->TurnOnCollision(true);
		projectileActor->GetProjectileComponent()->Velocity = projectileDir * projectileSpeed;
	}
}

FVector UNotifyState_ShootProjectileActor::GetShotDir(ABaseCharacter* characterOwner)
{
	FVector shotDir;
	// owner�� player��� ī�޶� �ٶ󺸰� �ִ� �������� Ray�� ���� Hit�� Actor�� �������� ���� ���� 
	if (characterOwner->IsA<APlayerCharacter>())
	{
		
	}
	// owner�� AI��� �����忡�� Ÿ���� �������� ������ ����
	else if (characterOwner->IsA<AMonsterCharacter>())
	{
		auto monController = characterOwner->GetController<AMonsterController>();
		if (monController != nullptr)
		{
			auto target = monController->GetBlackboardComponent()->GetValueAsObject("Target");
			if (target != nullptr)
			{
				// �����忡 ����� Ÿ�� �������� �߻�
				shotDir = Cast<AActor>(target)->GetActorLocation() - characterOwner->GetActorLocation();
				shotDir = shotDir.GetUnsafeNormal();
			}
			// �����忡 ����� Ÿ���� ���ٸ� �������� �߻�
			else
			{
				shotDir = characterOwner->GetActorForwardVector();
				shotDir = shotDir.GetUnsafeNormal();
			}
		}
	}
	return shotDir;
}
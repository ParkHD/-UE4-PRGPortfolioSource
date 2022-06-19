// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/03_NotifyState/NotifyState_LaunchActor.h"
#include "00_Character/BaseCharacter.h"
#include "05_Actor/00_ProjectileActor/ProjectileActor.h"
#include "03_Component/00_Character/StatusComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
void UNotifyState_LaunchActor::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp != nullptr)
	{
		owner = MeshComp->GetOwner<ABaseCharacter>();
		if (owner != nullptr)
		{
			FVector center = owner->GetActorLocation() + owner->GetActorForwardVector().GetSafeNormal() * fowardDistance + owner->GetActorUpVector().GetSafeNormal() * upDistance;
			for (int i = 0; i < spawnCount; i++)
			{
				float X = FMath::FRandRange(center.X - radius, center.X + radius);
				float Y = FMath::FRandRange(center.Y - radius, center.Y + radius);

				targetLocation.Emplace(X, Y, center.Z);
			}
		}
	}
	//if (MeshComp != nullptr)
	//{
	//	owner = MeshComp->GetOwner<ABaseCharacter>();
	//	if (owner != nullptr)
	//	{
	//		FVector spawnLocation;	// ������ ��ġ
	//		FRotator spawnRotator;	// ������ ȸ����

	//		// ���ϳ����� ���ٸ� ĳ������ �����Ÿ� ������ ������ ��ġ ����
	//		if (spawnSocketName.IsNone())
	//		{
	//			// ĳ������ �����Ÿ� ������ ����
	//			spawnLocation = owner->GetActorLocation() + owner->GetActorForwardVector() * 150.f;
	//			spawnRotator = owner->GetActorRotation() + spawnRotation;
	//		}
	//		// ���ϳ����� �ִٸ� ������ �������� ������ ��ġ ����
	//		else
	//		{
	//			// �Է¹��� ������ ��ġ�� ����
	//			spawnLocation = MeshComp->GetSocketLocation(spawnSocketName);
	//			spawnRotator = MeshComp->GetSocketRotation(spawnSocketName);
	//		}

	//		// ProjectileActor ��ȯ �� ����
	//		projectileActor = owner->GetWorld()->SpawnActor<AProjectileActor>(ActorToSpawn);
	//		if (spawnSocketName.IsNone())
	//		{
	//			projectileActor->SetActorLocation(spawnLocation);
	//			projectileActor->SetActorRotation(spawnRotator);
	//		}
	//		else
	//		{
	//			projectileActor->AttachToComponent(MeshComp, FAttachmentTransformRules::KeepRelativeTransform, spawnSocketName);
	//		}
	//		projectileActor->SetOwner(owner);

	//		//// ProjectileActor�� ����� ��� �� ����
	//		//auto skillInfo = owner->GetSkillComponent()->GetSkillInfo(skill_Tag);
	//		//if (skillInfo != nullptr)
	//		//{
	//		//	float ownerDamage = owner->GetStatusComponent()->GetStat().Damage;
	//		//	float skillDamage = ownerDamage * skillInfo->skill_Damage / 100;
	//		//	projectileActor->SetSkillDamage(skillDamage);
	//		//}

	//	}
	//}
}

void UNotifyState_LaunchActor::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (owner != nullptr)
	{
		time += FrameDeltaTime;
		if (time >= intervalTime && index < spawnCount)
		{
			if (targetLocation.Num() > index)
			{
				UE_LOG(LogTemp, Log, TEXT("%d"), index);
				auto Actor = owner->GetWorld()->SpawnActor<AProjectileActor>(ActorToSpawn);
				Actor->SetOwner(owner);
				Actor->SetActorLocation(targetLocation[index]);

				float damage = owner->GetStatusComponent()->GetStat().Damage;
				if (bSkillAttack)
				{

				}
				Actor->SetDamage(damage);
				Actor->GetProjectileComponent()->Velocity = -Actor->GetActorUpVector() * projectileSpeed;
				index++;
				time = 0.f;

			}
		}
	}
}

void UNotifyState_LaunchActor::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (owner != nullptr)
	{
		time = 0.f;
		index = 0;
		targetLocation.Empty();
		//// �߻��� ���� ����
		//FVector projectileDir;
		//if (spawnSocketName.IsNone())
		//{
		//	// �Է¹��� �����̸��� ���ٸ� ĳ������ Forward�������� �߻�
		//	projectileDir = owner->GetActorForwardVector();
		//}
		//else
		//{
		//	projectileDir = GetShotDir(owner);
		//	// �߻��ϱ� ���� Actor���� �����
		//	projectileActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		//}

		//// ProjectileActor �ݸ��� Ȱ��ȭ �� �߻�
		//projectileActor->TurnOnCollision(true);
		//projectileActor->GetProjectileComponent()->Velocity = projectileDir * projectileSpeed;
	}
}

//FVector UNotifyState_LaunchActor::GetShotDir(ABaseCharacter* characterOwner)
//{
//	FVector shotDir;
//	// owner�� player��� ī�޶� �ٶ󺸰� �ִ� �������� Ray�� ���� Hit�� Actor�� �������� ���� ���� 
//	if (characterOwner->IsA<APlayerCharacter>())
//	{
//		// ī�޶� ���� ���⿡�� ~ (�ʳ������� ����)
//		FVector start = Cast<APlayerCharacter>(characterOwner)->GetCameraComponent()->GetComponentLocation();
//		FVector end = start + characterOwner->GetControlRotation().Vector() * 100000.f;
//
//		// WorldStatic�� BattleCharacter�� Hit�ǵ��� ����
//		TArray<TEnumAsByte<EObjectTypeQuery>> objects;
//		objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel9));
//		objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
//
//		FHitResult hit;
//		if (UKismetSystemLibrary::LineTraceSingleForObjects(
//			characterOwner->GetWorld(),
//			start,
//			end,
//			objects,
//			false,
//			TArray<AActor*>(),
//			EDrawDebugTrace::ForDuration,
//			hit,
//			true))
//		{
//			// Hit�� Actor�������� �߻�
//			FVector startLocation = characterOwner->GetMesh()->GetSocketLocation(spawnSocketName);
//			FVector targetLocation = hit.Location;
//			shotDir = (targetLocation - startLocation);
//		}
//		else
//		{
//			FVector startLocation = characterOwner->GetMesh()->GetSocketLocation(spawnSocketName);
//			FVector targetLocation = end;
//			shotDir = (targetLocation - startLocation);
//		}
//		// ������ �븻����
//		shotDir = shotDir.GetUnsafeNormal();
//	}
//	// owner�� AI��� �����忡�� Ÿ���� �������� ������ ����
//	else if (characterOwner->IsA<AMonsterBaseCharacter>())
//	{
//		auto monController = characterOwner->GetController<AMonsterAIController>();
//		if (monController != nullptr)
//		{
//			auto target = monController->GetBlackboardComponent()->GetValueAsObject("Target");
//			if (target != nullptr)
//			{
//				// �����忡 ����� Ÿ�� �������� �߻�
//				shotDir = Cast<AActor>(target)->GetActorLocation() - characterOwner->GetMesh()->GetSocketLocation(spawnSocketName);
//				shotDir = shotDir.GetUnsafeNormal();
//			}
//			// �����忡 ����� Ÿ���� ���ٸ� �������� �߻�
//			else
//			{
//				shotDir = characterOwner->GetActorForwardVector();
//				shotDir = shotDir.GetUnsafeNormal();
//			}
//		}
//	}
//	return shotDir;
//}
//

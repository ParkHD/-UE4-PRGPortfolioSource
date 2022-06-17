// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/03_NotifyState/NotifyState_AttackCollision.h"
#include "00_Character/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "00_Character/PlayerCharacter.h"
#include "03_Component/00_Character/StatusComponent.h"

void UNotifyState_AttackCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp != nullptr)
	{
		owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if (owner != nullptr)
		{
			startLocation = owner->GetActorLocation();
			startRotator = owner->GetActorRotation();

			// �ݸ����� ������ ���� ���� (���� ���⿡ ���� �ٸ�)
			angle = bRightStart ? range : -range;			
		}
	}

}
void UNotifyState_AttackCollision::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (owner != nullptr)
	{
		// collision�� EndLocation ���ϱ�
		FRotator tempRotator = startRotator;
		tempRotator.Yaw = angle;
		FRotator dirRotator = tempRotator + startRotator;	// ĳ���ͱ������� ȸ���� z���� angle���� ȸ�������� �� Rotator
		FVector endLocation = dirRotator.Vector() * length + owner->GetActorLocation();
		if (bChargingAttack)
		{
			APlayerCharacter* player = Cast<APlayerCharacter>(owner);
			if (player != nullptr)
			{
				UE_LOG(LogTemp, Log, TEXT("%d"), player->GetChargingTime());
				endLocation = dirRotator.Vector() * length * player->GetChargingTime() + owner->GetActorLocation();
			}
		}
		// ���� angle������ �ݸ��� ����
		TArray<FHitResult> hits;
		FCollisionQueryParams Params;
		TArray<TEnumAsByte<EObjectTypeQuery>> objects;
		TArray<AActor*> ignoreActor;
		ignoreActor.Emplace(owner);
		objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		if (UKismetSystemLibrary::SphereTraceMultiForObjects(
			owner,
			owner->GetActorLocation(),
			endLocation,
			collisionRadius,
			objects,
			false,
			ignoreActor,
			EDrawDebugTrace::ForDuration,
			hits,
			true))
		{
			for (FHitResult& hit : hits)
			{
				ABaseCharacter* target = Cast<ABaseCharacter>(hit.GetActor());

				if (target != nullptr)
				{
					if (!hitActors.Contains(target))
					{
						hitActors.Emplace(target);
						
						APlayerCharacter* player = Cast<APlayerCharacter>(owner);
						target->BeginHitStop();

						float damageAmount = owner->GetStatusComponent()->GetStat().Damage;
						if (player != nullptr)
						{
							damageAmount *= player->GetChargingTime();
							player->CameraShakeDemo(1.f);
							player->BeginHitStop();
						}

						target->TakeDamage(damageAmount, FDamageEvent(), owner->GetController(), owner);
						//FDamageEvent damageEvent;
						//auto skillInfo = owner->GetSkillComponent()->GetSkillInfo(skill_Tag);
						//if (skillInfo != nullptr)
						//{
						//	// ����� ���
						//	float ownerDamage = owner->GetStatusComponent()->GetStat().Damage;
						//	float skillDamage = ownerDamage * skillInfo->skill_Damage / 100;
						//	// Hit�� Actor�� ����� ����
						//	target->TakeDamageType(EDamageType::SKILL, skillDamage, damageEvent, target->GetController(), target);
						//}
					}
				}
			}
		}

		// angle ������Ʈ
		angle = FMath::Clamp(angle + ( bRightStart ? - interpSpeed : interpSpeed), -range, range);
		//angle = FMath::FInterpTo(angle, bRightStart ? -range : range, FrameDeltaTime, interpSpeed);
	}
}

void UNotifyState_AttackCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);


	if (owner != nullptr)
		hitActors.Empty();
}


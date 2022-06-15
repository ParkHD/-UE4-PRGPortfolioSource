// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/03_NotifyState/NotifyState_AttackCollision.h"
#include "00_Character/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "00_Character/PlayerCharacter.h"

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
			for (FHitResult hit : hits)
			{
				ABaseCharacter* target = Cast<ABaseCharacter>(hit.GetActor());

				if (target != nullptr)
				{
					if (hitActors.Emplace(target))
					{
						APlayerCharacter* player = Cast<APlayerCharacter>(owner);
						
						if (player != nullptr)
						{
							player->CameraShakeDemo(1.f);
						}
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


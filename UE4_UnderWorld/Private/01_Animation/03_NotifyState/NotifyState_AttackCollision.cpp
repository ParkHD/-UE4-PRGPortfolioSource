// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/03_NotifyState/NotifyState_AttackCollision.h"
#include "Kismet/GameplayStatics.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "03_Component/00_Character/StatusComponent.h"

void UNotifyState_AttackCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp != nullptr)
	{
		owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if (owner != nullptr)
		{
			// ������ ������ ��ġ�� �����Ѵ�.
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
		if (!startSocketName.IsNone())
			startLocation = MeshComp->GetSocketLocation(startSocketName);
		// collision�� EndLocation ���ϱ�(���� ����)
		FRotator tempRotator = startRotator;
		tempRotator.Yaw = angle;
		FRotator dirRotator = tempRotator + startRotator;	// ĳ���ͱ������� ȸ���� z���� angle���� ȸ�������� �� Rotator
		
		FVector endLocation = dirRotator.Vector() * length + owner->GetActorLocation();
		if (!endSocketName.IsNone())
		{
			endLocation = MeshComp->GetSocketLocation(endSocketName);
		}
		// ��¡ ������ ��쿡�� ��¡ �ð��� ���� �ݸ��� ũ�Ⱑ �����Ѵ�.(��Ÿ� ����)
		if (bChargingAttack)
		{
			APlayerCharacter* player = Cast<APlayerCharacter>(owner);
			if (player != nullptr)
			{
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
			startLocation,
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
					// �̹� ������� �� ������� Ȯ��
					if (!hitActors.Contains(target))
					{
						
						hitActors.Emplace(target);

						// ���� �����
						float damageAmount = owner->GetStatusComponent()->GetStat().Damage;
						// ������ü�� �÷��̾����� Ȯ��
						APlayerCharacter* player = Cast<APlayerCharacter>(owner);
						if (player != nullptr)
						{
							// ��¡�ð��� ���� ����� ����
							if(bChargingAttack)
								damageAmount *= player->GetChargingTime();
							// ī�޶� ����ũ
							player->CameraShakeDemo(1.f);
							// �÷��̾� hitStop
							player->BeginHitStop();
							// ���� ��ġ�� hitparticle ��ȯ
							UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetWorld(), hitParticle, hit.Location, FRotator::ZeroRotator, true);
						}
						

						float value = 0;
						if(isSkillAttack)
						{
							auto skillInfo = owner->GetSkillComponent()->GetSkillInfo(skill_Tag);
							if (skillInfo != nullptr)
							{
								// ����� ���
								damageAmount = damageAmount * skillInfo->skill_Damage / 100;
								value = skillInfo->skill_value;
							}
						}

						

						target->CustomTakeDamage(attackType, damageAmount, FDamageEvent(), owner->GetController(), owner, value);
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

	// ������ ��� �ʱ�ȭ
	if (owner != nullptr)
		hitActors.Empty();
}


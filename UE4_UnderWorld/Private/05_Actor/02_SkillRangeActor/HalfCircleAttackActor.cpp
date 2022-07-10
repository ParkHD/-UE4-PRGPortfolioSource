// Fill out your copyright notice in the Description page of Project Settings.


#include "05_Actor/02_SkillRangeActor/HalfCircleAttackActor.h"

void AHalfCircleAttackActor::OnActorOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	// overlap�ǰ� actor ��ġ���� �ݿ��� �ش��ϴ� �κп� ������ ������� �ش�.
	if (OtherActor->IsA<ABaseCharacter>())
	{
		auto target = Cast<ABaseCharacter>(OtherActor);
		auto owner = GetOwner<ABaseCharacter>();
		if (target != nullptr && owner != nullptr)
		{
			// ó�� ������ ����̸� �������� �˻�
			if (target->GetGenericTeamId() != owner->GetGenericTeamId()
				&& !hitActors.Contains(target))
			{
				// �ݿ� ���� �ִ��� �˻�
				// Ÿ�ٰ��� ���� ���ϱ�
				FVector dirVector = target->GetActorLocation() - owner->GetActorLocation();
				float angle = dirVector.Rotation().Yaw - owner->GetActorRotation().Yaw;
				if (angle > 180)
					angle -= 360.f;
				else if (angle < -180)
					angle += 360.f;
				if (angle >= -90 && angle <= 90)
				{
					target->CustomTakeDamage(attackType, damageAmount, FDamageEvent(), owner->GetController(), owner, damageValue);
					hitActors.Emplace(target);
				}
			}
		}
	}
}

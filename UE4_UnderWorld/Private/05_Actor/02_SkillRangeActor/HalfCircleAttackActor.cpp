// Fill out your copyright notice in the Description page of Project Settings.


#include "05_Actor/02_SkillRangeActor/HalfCircleAttackActor.h"

void AHalfCircleAttackActor::OnActorOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	// overlap되고 actor 위치에서 반원에 해당하는 부분에 있으면 대미지를 준다.
	if (OtherActor->IsA<ABaseCharacter>())
	{
		auto target = Cast<ABaseCharacter>(OtherActor);
		auto owner = GetOwner<ABaseCharacter>();
		if (target != nullptr && owner != nullptr)
		{
			// 처음 공격한 대상이며 적군인지 검사
			if (target->GetGenericTeamId() != owner->GetGenericTeamId()
				&& !hitActors.Contains(target))
			{
				// 반원 위에 있는지 검사
				// 타겟과의 각도 구하기
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

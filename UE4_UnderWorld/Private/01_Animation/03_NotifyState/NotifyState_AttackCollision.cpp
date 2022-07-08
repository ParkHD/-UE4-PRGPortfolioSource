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
			// 공격을 시작한 위치를 저장한다.
			startLocation = owner->GetActorLocation();
			startRotator = owner->GetActorRotation();

			// 콜리전이 생성될 시작 각도 (공격 방향에 따라 다름)
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
		// collision의 EndLocation 구하기(공격 범위)
		FRotator tempRotator = startRotator;
		tempRotator.Yaw = angle;
		FRotator dirRotator = tempRotator + startRotator;	// 캐릭터기준으로 회전값 z축을 angle각도 회전시켰을 때 Rotator
		
		FVector endLocation = dirRotator.Vector() * length + owner->GetActorLocation();
		if (!endSocketName.IsNone())
		{
			endLocation = MeshComp->GetSocketLocation(endSocketName);
		}
		// 차징 공격일 경우에는 차징 시간에 따라 콜리전 크기가 증가한다.(사거리 증가)
		if (bChargingAttack)
		{
			APlayerCharacter* player = Cast<APlayerCharacter>(owner);
			if (player != nullptr)
			{
				endLocation = dirRotator.Vector() * length * player->GetChargingTime() + owner->GetActorLocation();
			}
		}

		// 현재 angle각도에 콜리전 생성
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
					// 이미 대미지를 준 대상인지 확인
					if (!hitActors.Contains(target))
					{
						
						hitActors.Emplace(target);

						// 공격 대미지
						float damageAmount = owner->GetStatusComponent()->GetStat().Damage;
						// 공격주체가 플레이어인지 확인
						APlayerCharacter* player = Cast<APlayerCharacter>(owner);
						if (player != nullptr)
						{
							// 차징시간에 따른 대미지 증가
							if(bChargingAttack)
								damageAmount *= player->GetChargingTime();
							// 카메라 쉐이크
							player->CameraShakeDemo(1.f);
							// 플레이어 hitStop
							player->BeginHitStop();
							// 맞은 위치에 hitparticle 소환
							UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetWorld(), hitParticle, hit.Location, FRotator::ZeroRotator, true);
						}
						

						float value = 0;
						if(isSkillAttack)
						{
							auto skillInfo = owner->GetSkillComponent()->GetSkillInfo(skill_Tag);
							if (skillInfo != nullptr)
							{
								// 대미지 계산
								damageAmount = damageAmount * skillInfo->skill_Damage / 100;
								value = skillInfo->skill_value;
							}
						}

						

						target->CustomTakeDamage(attackType, damageAmount, FDamageEvent(), owner->GetController(), owner, value);
					}
				}
			}
		}

		// angle 업데이트
		angle = FMath::Clamp(angle + ( bRightStart ? - interpSpeed : interpSpeed), -range, range);
		//angle = FMath::FInterpTo(angle, bRightStart ? -range : range, FrameDeltaTime, interpSpeed);
	}
}

void UNotifyState_AttackCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	// 공격한 대상 초기화
	if (owner != nullptr)
		hitActors.Empty();
}


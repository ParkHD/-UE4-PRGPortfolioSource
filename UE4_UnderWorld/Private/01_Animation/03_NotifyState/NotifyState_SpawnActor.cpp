// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/03_NotifyState/NotifyState_SpawnActor.h"

#include "00_Character/BaseCharacter.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/01_Monster/MonsterController.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "03_Component/00_Character/StatusComponent.h"
#include "05_Actor/02_SkillRangeActor/SkillRangeActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UNotifyState_SpawnActor::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                          float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if(MeshComp != nullptr)
	{
		owner = MeshComp->GetOwner<ABaseCharacter>();
	}
}

void UNotifyState_SpawnActor::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UNotifyState_SpawnActor::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if(owner != nullptr)
	{
		SetSpawnLocation();

		if(!spawnLocation.IsZero())
		{
			auto spawnedActor = owner->GetWorld()->SpawnActor<AActor>(actorToSpawn, spawnLocation, spawnRotator);
			spawnedActor->SetOwner(owner);
			float damage = owner->GetStatusComponent()->GetStat().Damage;
			if (isSkillAttack)
			{
				auto skillInfo = owner->GetSkillComponent()->GetSkillInfo(skill_Tag);
				if (skillInfo != nullptr)
				{
					// 대미지 계산
					damage += damage * (skillInfo->skill_Damage / 100);
					Cast<ASkillRangeActor>(spawnedActor)->SetValue(skillInfo->skill_value);
					UE_LOG(LogTemp, Log, TEXT("%f"), skillInfo->skill_value);
				}
			}
			Cast<ASkillRangeActor>(spawnedActor)->SetDamage(damage);
		}
	}
}

void UNotifyState_SpawnActor::SetSpawnLocation()
{
	if(owner != nullptr)
	{
		FVector startLocation;
		FVector endLocation;

		if (spawnTarget == ETarget::TARGET)
		{
			if (owner->IsA<AMonsterCharacter>())
			{
				auto monController = owner->GetController<AMonsterController>();
				if (monController != nullptr)
				{
					auto target = monController->GetBlackboardComponent()->GetValueAsObject("Target");
					if (target != nullptr)
					{
						auto targetActor = Cast<AActor>(target);
						if (targetActor != nullptr)
						{
							startLocation = targetActor->GetActorLocation();
							endLocation = targetActor->GetActorLocation() - targetActor->GetActorUpVector() * rayLength;
						}
					}
				}
			}
		}
		else if (spawnTarget == ETarget::ME)
		{
			startLocation = owner->GetActorLocation();
			endLocation = owner->GetActorLocation() - owner->GetActorUpVector() * rayLength;

			spawnRotator = owner->GetActorRotation();
		}
			
		FHitResult OutHit;
		TArray<TEnumAsByte<EObjectTypeQuery>> objects;
		objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
		if (UKismetSystemLibrary::LineTraceSingleForObjects(
			owner->GetWorld(),
			startLocation,
			endLocation,
			objects,
			false,
			TArray<AActor*>(),
			EDrawDebugTrace::ForDuration,
			OutHit,
			true))
		{
			spawnLocation = OutHit.Location;
		}
	}
}

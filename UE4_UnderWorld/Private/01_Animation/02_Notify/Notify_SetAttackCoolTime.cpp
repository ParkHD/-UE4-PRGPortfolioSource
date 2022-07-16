// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/02_Notify/Notify_SetAttackCoolTime.h"

#include "00_Character/BaseCharacter.h"
#include "03_Component/00_Character/StatusComponent.h"

void UNotify_SetAttackCoolTime::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if(MeshComp != nullptr)
	{
		ABaseCharacter* owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if(owner != nullptr)
		{
			// 공격 실행 후 캐릭터의 공격 쿨타임 돌리기
			owner->SetAttackState(EAttackState::COOLTIME);
			FTimerHandle attackCoolTime;
			FTimerDelegate attackDelegate = FTimerDelegate::CreateUObject(owner, &ABaseCharacter::SetAttackState, EAttackState::NORMAL);
			owner->GetWorldTimerManager().SetTimer(
				attackCoolTime,
				attackDelegate,
				owner->GetStatusComponent()->GetStat().AttackSpeed,
				false);
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/02_Notify/Notify_PlayNiagaraEffect.h"
#include "00_Character/PlayerCharacter.h"

void UNotify_PlayNiagaraEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != nullptr)
	{
		owner = MeshComp->GetOwner<APlayerCharacter>();
	}
	Super::Notify(MeshComp, Animation);

}
UFXSystemComponent* UNotify_PlayNiagaraEffect::SpawnEffect(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (owner != nullptr)
		Scale = {1.f * owner->GetChargingTime(),1.f * owner->GetChargingTime(),1.f * owner->GetChargingTime() };
	return Super::SpawnEffect(MeshComp, Animation);
}
void UNotify_PlayNiagaraEffect::SetScale(FVector scale)
{
	if (owner != nullptr)
	{
		Scale = scale * owner->GetChargingTime();
	}
}
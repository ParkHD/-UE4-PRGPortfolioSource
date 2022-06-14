// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/02_Notify/Notify_PlaySound.h"
#include "Kismet/GameplayStatics.h"

void UNotify_PlaySound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp != nullptr && soundToPlay != nullptr)
	{
		if (bAttenuation)
		{
			// 소리 범위 설정
			USoundAttenuation* soundAtt = NewObject<USoundAttenuation>();
			FSoundAttenuationSettings setting;
			setting.FalloffDistance = falloffDistance;
			soundAtt->Attenuation = setting;

			// 사운드 재생
			UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), soundToPlay, MeshComp->GetComponentLocation(), FRotator::ZeroRotator,
				1.f, 1.f, 0.f, soundAtt);
		}
		else
		{
			// 사운드 재생
			UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), soundToPlay, MeshComp->GetComponentLocation());
		}
	}
}

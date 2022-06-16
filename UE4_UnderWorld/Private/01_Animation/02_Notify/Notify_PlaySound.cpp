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
			// �Ҹ� ���� ����
			USoundAttenuation* soundAtt = NewObject<USoundAttenuation>();
			FSoundAttenuationSettings setting;
			setting.FalloffDistance = falloffDistance;
			soundAtt->Attenuation = setting;

			// ���� ���
			UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), soundToPlay, MeshComp->GetComponentLocation(), FRotator::ZeroRotator,
				1.f, 1.f, 0.f, soundAtt);
		}
		else
		{
			// ���� ���
			UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), soundToPlay, MeshComp->GetComponentLocation());
		}
	}
}
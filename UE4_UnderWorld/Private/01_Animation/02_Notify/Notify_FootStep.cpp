// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/02_Notify/Notify_FootStep.h"

#include "00_Character/BaseCharacter.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"

UNotify_FootStep::UNotify_FootStep()
{
	
}

void UNotify_FootStep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp != nullptr)
	{
		// �� ������ Ray ����
		FVector FootLocation = MeshComp->GetSocketLocation(footSocketName);
		FVector EndLocation = FootLocation - MeshComp->GetUpVector() * rayLength;
		FHitResult Hit;
		TArray<TEnumAsByte<EObjectTypeQuery>> object;
		object.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));

		if (UKismetSystemLibrary::LineTraceSingleForObjects(
			MeshComp->GetWorld(),
			FootLocation,
			EndLocation,
			object,
			false,
			TArray<AActor*>(),
			EDrawDebugTrace::None,
			Hit,
			true
		))
		{
			// ������ SurfaceType�˻� �� Type�� ���� �ٸ� ���ڱ� �� �Ҹ� ����
			switch (UGameplayStatics::GetSurfaceType(Hit))
			{
			case EPhysicalSurface::SurfaceType1:	// �Ϲ� ����
			{
				UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetWorld(), footStep.GroundFootParticle, FootLocation, FRotator::ZeroRotator, true);
				if (bAttenuation)	// �Ҹ� ���� ����
				{
					FSoundAttenuationSettings setting;
					setting.FalloffDistance = falloffDistance;
					USoundAttenuation* soundAtt = NewObject<USoundAttenuation>();
					soundAtt->Attenuation = setting;

					// ���� ���
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.GroundFootSound, FootLocation,
						FRotator::ZeroRotator,
						1.f, 1.f, 0.f, soundAtt);
				}
				else
				{
					// ���� ���
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.GroundFootSound, FootLocation);
				}
				break;
			}
			case EPhysicalSurface::SurfaceType2:	// �� ����
			{
				UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetWorld(), footStep.SnowFootParticle, FootLocation, FRotator::ZeroRotator, true);
				if (bAttenuation)	// �Ҹ� ���� ����
				{
					FSoundAttenuationSettings setting;
					setting.FalloffDistance = falloffDistance;
					USoundAttenuation* soundAtt = NewObject<USoundAttenuation>();
					soundAtt->Attenuation = setting;

					// ���� ���
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.SnowFootSound, FootLocation,
						FRotator::ZeroRotator,
						1.f, 1.f, 0.f, soundAtt);
				}
				else
				{
					// ���� ���
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.SnowFootSound, FootLocation);
				}
				break;
			}
			case EPhysicalSurface::SurfaceType3:	// �� ����
			{
				UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetWorld(), footStep.WaterFootParticle, FootLocation, FRotator::ZeroRotator, true);
				if (bAttenuation)	// �Ҹ� ���� ����
				{
					FSoundAttenuationSettings setting;
					setting.FalloffDistance = falloffDistance;
					USoundAttenuation* soundAtt = NewObject<USoundAttenuation>();
					soundAtt->Attenuation = setting;

					// ���� ���
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.WaterFootSound, FootLocation,
						FRotator::ZeroRotator,
						1.f, 1.f, 0.f, soundAtt);
				}
				else
				{
					// ���� ���
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.WaterFootSound, FootLocation);
				}
				break;
			}
			default:
				UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetWorld(), footStep.GroundFootParticle, FootLocation, FRotator::ZeroRotator, true);
				if (bAttenuation)	// �Ҹ� ���� ����
				{
					FSoundAttenuationSettings setting;
					setting.FalloffDistance = falloffDistance;
					USoundAttenuation* soundAtt = NewObject<USoundAttenuation>();
					soundAtt->Attenuation = setting;

					// ���� ���
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.GroundFootSound, FootLocation,
						FRotator::ZeroRotator,
						1.f, 1.f, 0.f, soundAtt);
				}
				else
				{
					// ���� ���
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.GroundFootSound, FootLocation);
				}
				break;
			}
		}

	}
}

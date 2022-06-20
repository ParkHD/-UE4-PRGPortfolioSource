// Fill out your copyright notice in the Description page of Project Settings.


#include "99_GameMode/MyGameMode.h"

void AMyGameMode::CameraShake(float Scale)
{
	UE_LOG(LogTemp, Log, TEXT("00"));
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CamSake, Scale);
}

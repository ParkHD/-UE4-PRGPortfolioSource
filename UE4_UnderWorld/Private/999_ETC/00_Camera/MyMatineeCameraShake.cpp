// Fill out your copyright notice in the Description page of Project Settings.


#include "999_ETC/00_Camera/MyMatineeCameraShake.h"

UMyMatineeCameraShake::UMyMatineeCameraShake()
{
	OscillationDuration = 0.25f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(5.f, 10.f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(25.f, 35.f);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(5.f, 10.f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(25.f, 35.f);
}
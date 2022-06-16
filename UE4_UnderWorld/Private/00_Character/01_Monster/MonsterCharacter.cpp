// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/MonsterCharacter.h"
#include "Components/WidgetComponent.h"
#include "02_Widget/DamageTextWidget.h"

float AMonsterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (damageTextWidgetComponentClass != nullptr)
	{
		// 동적생성 // NewObject vs CreateDefault
		UWidgetComponent* DamageWidgetComp = NewObject<UWidgetComponent>(this, damageTextWidgetComponentClass);
		DamageWidgetComp->RegisterComponent();
		DamageWidgetComp->InitWidget();

		auto damageWidget = DamageWidgetComp->GetUserWidgetObject();
		if (damageWidget != nullptr)
		{
			Cast<UDamageTextWidget>(damageWidget)->SetUp(DamageAmount);
			DamageWidgetComp->SetWorldLocation( GetActorLocation());
		}

		// 여기만든이유 일회용이라서 헤더에다 하면 덮어써져서 안 없어지는 오류 생긴다.
		FTimerHandle damageTextTimerHandle;
		// 파라미터없는 함수 호출
		// actor를 상속받았으면
		FTimerDelegate DamageTextTimerDel = FTimerDelegate::CreateUObject(
			DamageWidgetComp, &UWidgetComponent::DestroyComponent, false);

		GetWorldTimerManager().SetTimer(
			damageTextTimerHandle,
			DamageTextTimerDel,
			1.f,
			false
		);
	}

	return 0.0f;
}

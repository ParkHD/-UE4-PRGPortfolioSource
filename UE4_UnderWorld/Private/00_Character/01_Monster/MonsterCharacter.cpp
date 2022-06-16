// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/MonsterCharacter.h"
#include "Components/WidgetComponent.h"
#include "02_Widget/DamageTextWidget.h"

float AMonsterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (damageTextWidgetComponentClass != nullptr)
	{
		// �������� // NewObject vs CreateDefault
		UWidgetComponent* DamageWidgetComp = NewObject<UWidgetComponent>(this, damageTextWidgetComponentClass);
		DamageWidgetComp->RegisterComponent();
		DamageWidgetComp->InitWidget();

		auto damageWidget = DamageWidgetComp->GetUserWidgetObject();
		if (damageWidget != nullptr)
		{
			Cast<UDamageTextWidget>(damageWidget)->SetUp(DamageAmount);
			DamageWidgetComp->SetWorldLocation( GetActorLocation());
		}

		// ���⸸������ ��ȸ���̶� ������� �ϸ� ��������� �� �������� ���� �����.
		FTimerHandle damageTextTimerHandle;
		// �Ķ���;��� �Լ� ȣ��
		// actor�� ��ӹ޾�����
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

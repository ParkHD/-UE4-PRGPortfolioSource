// Fill out your copyright notice in the Description page of Project Settings.


#include "05_Actor/03_Dungeon/DungeonStarter.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "02_Widget/02_InterAction/InterActionWidget.h"
#include "99_GameMode/MyGameMode.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADungeonStarter::ADungeonStarter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CAPSULECOMPONENT"));
	SphereComponent->SetCollisionProfileName("Item");
	RootComponent = SphereComponent;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLESYSTEMCOMPONENT"));
	ParticleSystemComponent->SetupAttachment(RootComponent);
	ParticleSystemComponent->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	ParticleSystemComponent->SetWorldLocation(FVector(0.f, 0.f, -30.f));

	InterActiveWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	InterActiveWidget->SetupAttachment(RootComponent);
	InterActiveWidget->SetVisibility(false);
	InterActiveWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InterActiveWidget->SetDrawSize(FVector2D(25.f, 25.f));
}

// Called when the game starts or when spawned
void ADungeonStarter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADungeonStarter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InterActiveWidget->InitWidget();
	if (InterActiveWidget != nullptr)
	{
		auto interActionWidget = Cast<UInterActionWidget>(InterActiveWidget->GetUserWidgetObject());
		if (interActionWidget != nullptr)
		{
			const FString str("Start Dungeon");
			FText text = FText::FromString(str);
			interActionWidget->SetItemText(FText::FromString(str));
		}
	}

	OnActorBeginOverlap.AddUniqueDynamic(this, &ADungeonStarter::OnActorBeginOverlapEvent);
	OnActorEndOverlap.AddUniqueDynamic(this, &ADungeonStarter::OnActorEndOverlapEvent);
}

// Called every frame
void ADungeonStarter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonStarter::OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	// 주위에 플레이어가 들어가면 위젯 활성화
	APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
	if (player != nullptr)
	{
		InterActiveWidget->SetVisibility(true);
		player->SetInterActionActor(this);
	}
}

void ADungeonStarter::OnActorEndOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	// 주위에 플레이어가 들어가면 위젯 비 활성화
	APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
	if (player != nullptr)
	{
		InterActiveWidget->SetVisibility(false);
		player->SetInterActionActor(nullptr);
	}
}

const FText ADungeonStarter::GetName()
{
	return IInterface_InterAction::GetName();
}

void ADungeonStarter::InterAction(APlayerCharacter* caller)
{
	IInterface_InterAction::InterAction(caller);
	Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->StartStage(0);

	SetActorHiddenInGame(true);
}


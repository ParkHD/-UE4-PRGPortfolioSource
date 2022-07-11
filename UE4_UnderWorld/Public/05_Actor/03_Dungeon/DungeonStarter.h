// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "999_ETC/02_Interface/Interface_InterAction.h"
#include "GameFramework/Actor.h"
#include "DungeonStarter.generated.h"

UCLASS()
class UE4_UNDERWORLD_API ADungeonStarter : public AActor, public IInterface_InterAction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonStarter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
		class USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* ParticleSystemComponent;
	UPROPERTY(EditAnywhere)
		class UWidgetComponent* InterActiveWidget;				// InterAction 위젯

protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag Dungeon_Tag;				// 던전 Tag

private:
	UFUNCTION()
		void OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void OnActorEndOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);

public:
	// Interface 함수
	virtual const FText GetName() override;								// 이름
	virtual void InterAction(class APlayerCharacter* caller) override;	// 상호작용
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEffect.h"

#include "Components/SceneComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

// Sets default values
AMyEffect::AMyEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_sceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	_niagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");

	RootComponent = _sceneComponent;
	_niagaraComponent->SetupAttachment(_sceneComponent);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> test(TEXT("/Script/Niagara.NiagaraSystem'/Game/Graphics/Effect/Vefects/Free_Fire/Shared/Particles/NS_Fire_Big.NS_Fire_Big'"));

	if (test.Succeeded())
	{
		_niagaraComponent->SetAsset(test.Object);
	}
}

// Called when the game starts or when spawned
void AMyEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


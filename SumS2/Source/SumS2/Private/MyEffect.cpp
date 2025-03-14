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

void AMyEffect::SetParticle(UNiagaraSystem* particle)
{
	if (particle->IsValidLowLevel())
	{
		_niagaraComponent->SetAsset(particle);
		_niagaraComponent->OnSystemFinished.AddDynamic(this, &AMyEffect::Finished);
	}
}

void AMyEffect::Stop()
{
	_niagaraComponent->DeactivateImmediate();
}

void AMyEffect::Play(FVector pos)
{
	_niagaraComponent->Activate(true);
	SetActorLocation(pos);
}

bool AMyEffect::IsActive()
{
	return _niagaraComponent->IsActive();
}

void AMyEffect::Finished(UNiagaraComponent* PSystem)
{
	PSystem->DeactivateImmediate();
}


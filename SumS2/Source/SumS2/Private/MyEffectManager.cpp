// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEffectManager.h"

#include "NiagaraSystem.h"

// Sets default values
AMyEffectManager::AMyEffectManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> particle(TEXT("/Script/Niagara.NiagaraSystem'/Game/Graphics/Effect/Vefects/Free_Fire/Shared/Particles/NS_Fire_Big_Simple.NS_Fire_Big_Simple'"));

	if (particle.Succeeded())
	{
		_particleTable.Add(TEXT("BigFire"), particle.Object);
		//_paticleTable[TEXT("BigFire")] = particle.Object;
	}
}

// Called when the game starts or when spawned
void AMyEffectManager::BeginPlay()
{
	Super::BeginPlay();
	
	// 풀링
	for (auto particle : _particleTable)
	{
		FString name = particle.Key;
		_effectTable.Add(name);

		for (int i = 0; i < 5; i++)
		{
			auto effect = GetWorld()->SpawnActor<AMyEffect>(FVector::ZeroVector, FRotator::ZeroRotator);
			effect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			effect->SetParticle(_particleTable[TEXT("BigFire")]);
			effect->Stop();

			_effectTable[name]._effects.Add(effect);
		}
	}
}

// Called every frame
void AMyEffectManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyEffectManager::PlayEffect(FString key, FVector pos)
{
	auto effects = _effectTable.Find(key);
	if(effects == nullptr)
		return;

	// 꺼져있는 얘 찾기
	auto iter = effects->_effects.FindByPredicate([](AMyEffect* effect)->bool 
	{
		if(!effect->IsActive())
			return true;
		return false;
	});

	// 꺼져있는 얘가 있다.
	if (iter)
	{
		(*iter)->Play(pos);
	}
}


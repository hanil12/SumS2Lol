// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDecalActor.h"

AMyDecalActor::AMyDecalActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyDecalActor::BeginPlay()
{
	Super::BeginPlay();

	FVector scale = FVector(1.0f, 0.0f, 0.0f);
	SetActorScale3D(scale);
	_runTime = 0.0f;
}

void AMyDecalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// runTime을 증가시키면서... delayTime보다 커지면
	_runTime += DeltaTime;
	FVector curScale = GetActorScale();

	// 이벤트 터짐
	if (_runTime > _delayTime)
	{
		if(_attackEvent.IsBound())
			_attackEvent.Broadcast();

		curScale.Y = 0.0f;
		curScale.Z = 0.0f;

		SetActorScale3D(curScale);

		if (_bLoop)
		{
			_runTime = 0.0f;
		}

		return;
	}

	// 서서히 크기가 증가
	curScale.Y = (_runTime / _delayTime) * _areaRadius;
	curScale.Z = (_runTime / _delayTime) * _areaRadius;

	SetActorScale3D(curScale);
}

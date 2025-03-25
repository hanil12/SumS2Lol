// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "MyDecalActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FFieldEnd);
/**
 * 
 */
UCLASS()
class SUMS2_API AMyDecalActor : public ADecalActor
{
	GENERATED_BODY()
	
public:
	AMyDecalActor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Play(FVector pos);
	void DeActiveEvent();

	FFieldEnd _endEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
	bool _bisPlay = false;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
	float _areaRadius = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
	float _delayTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
	float _runTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
	bool _bLoop = false;
};

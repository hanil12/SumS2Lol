// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyEffect.h"

#include "MyEffectManager.generated.h"

USTRUCT()
struct FEffects
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AMyEffect*> _effects;
};

UCLASS()
class SUMS2_API AMyEffectManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyEffectManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PlayEffect(FString key, FVector pos);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<FString, class UNiagaraSystem*> _particleTable;

	UPROPERTY()
	TMap<FString, FEffects> _effectTable;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MySceneUI.generated.h"

/**
 * 
 */
UCLASS()
class SUMS2_API UMySceneUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* MiniMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UMyButton* MyButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UMyHpBar* MyHpBar;
};

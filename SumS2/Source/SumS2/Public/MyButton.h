// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "MyButton.generated.h"

/**
 * 
 */
UCLASS()
class SUMS2_API UMyButton : public UButton
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetCurIndex();

	// Inventory 없이는 쓸 수가 없는 클래스
	// => 결합도가 높아진다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMyInvenUI* widget;

	int32 _curIndex;
};

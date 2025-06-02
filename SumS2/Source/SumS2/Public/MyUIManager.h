// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Blueprint/UserWidget.h"

#include "MyUIManager.generated.h"
/**
 * 
 */
UCLASS(config = Game, DefaultConfig)
class SUMS2_API UMyUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UMyUIManager();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void AddUI_Constructor(FString name, FString path);
	void PrintHello();

	bool IsOpen(FString name);
	TSubclassOf<UUserWidget> GetUIClass(FString name);
	UUserWidget* ShowPopUp(FString name);
	void ClosePopUp(FString name);
	void ClosePopUp();
	void CloseAllPopUp();

private:
	int32 _zOrder = 1;

	UPROPERTY()
	TMap<FString, TSubclassOf<UUserWidget>> _widgets;

	UPROPERTY()
	TArray<UUserWidget*> _widgetStack;


};

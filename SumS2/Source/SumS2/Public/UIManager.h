// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Blueprint/UserWidget.h"

#define UI GetGameInstance()->GetSubsystem<UUIManager>()

#include "UIManager.generated.h"

/**
* UGameInstanceSubsystem : 
 - GameInstance에서 자동으로 인스턴스화, 초기화
 - GameInstance와 수명을 같이함

 - 블루프린트화 시킬 수 없으며, 강제로 블루프린트화를 해도 cpp로 인스턴스화 된다.
 * 
 */

UCLASS()
class SUMS2_API UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UUIManager();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void WidgetNum();

	bool IsOpen(FString name);
	UUserWidget* GetOrShowPopUp(FString name);
	void ClosePopUp(FString name);
	void ClosePopUp();
	void CloseAll();

	UUserWidget* GetOrShowSceneUI(TSubclassOf<UUserWidget> widgetClass);
	void CloseSceneUI();

private:
	void AddUI_Constructor(FString name, FString path);
	TSubclassOf<UUserWidget> GetUIClass(FString name);

private:
	// "Inven" , UMyInvenUI 설계도
	UPROPERTY()
	TMap<FString, TSubclassOf<UUserWidget>> _widgetMap;

	int32 _zOrder = 1;
	UPROPERTY()
	TArray<UUserWidget*> _widgetStack;

	UPROPERTY()
	TSubclassOf<UUserWidget> _sceneUIClass;

	UPROPERTY()
	UUserWidget* _sceneUI;
};

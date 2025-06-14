// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyItem.h"
#include "MyInvenUI.generated.h"

class UInvenComponent;
/**
 * 
 */
UCLASS()
class SUMS2_API UMyInvenUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	// 동기화
	void SyncInvenComp(UMyInvenComponent* invenComp);
	void SetItem_Index(int32 index, FMyItemInfo info);
	UFUNCTION()
	void SetTextBox();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* Grid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Drop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UImage*> _slotImages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UButton*> _slotButtons;

	// #TODO
	UPROPERTY()
	UTexture2D* _defaultTexture;
	UPROPERTY()
	UTexture2D* _potionTexture;

	UPROPERTY();
	UMyInvenComponent* _invenComp;

	int32 _curIndex = -1;
};

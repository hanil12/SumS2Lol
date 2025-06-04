// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInvenUI.h"
#include "Components/UniformGridPanel.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MyInvenComponent.h"
#include "MyButton.h"

bool UMyInvenUI::Initialize()
{
	Super::Initialize();

	auto array = Grid->GetAllChildren();

	int index = 0;
	for (auto widget : array)
	{
		auto button = Cast<UMyButton>(widget);
		// 다이나믹 멀티캐스트 델레게이트는 람다식을 쓸 수가 없다.
		// => UFUNCTION() 키워드를 붙힐 수 없기 때문.
		if (button)
		{
			button->OnClicked.AddDynamic(button, &UMyButton::SetCurIndex);
			button->OnClicked.AddDynamic(this, &UMyInvenUI::SetTextBox);
			button->widget = this;
			button->_curIndex = index;
			index++;
		}

		auto image = Cast<UImage>(button->GetChildAt(0));
		if (image)
		{
			_slotImages.Add(image);
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Image Size : %d"), _slotImages.Num());
	if(_slotImages.Num() == 0)
		return false;

	_potionTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Graphics/UI/Items/Tex_seeds_06.Tex_seeds_06'"));
	_defaultTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Graphics/UI/Items/Tex_Default.Tex_Default'"));

	return true;
}

void UMyInvenUI::SyncInvenComp(UMyInvenComponent* invenComp)
{
	_invenComp = invenComp;
	if(_invenComp == nullptr)
		return;

	auto items = _invenComp->GetItems();

	int index = 0;
	for (auto item : items)
	{
		if (item == nullptr)
		{
			SetItem_Index(index, FMyItemInfo());
			index++;
			continue;
		}

		SetItem_Index(index, item->GetInfo());
		index++;
	}
}

void UMyInvenUI::SetItem_Index(int32 index, FMyItemInfo info)
{
	if (info.itemId == -1 && info.type == MyItemType::NONE)
		_slotImages[index]->SetBrushFromTexture(_defaultTexture);

	if(info.itemId == 1 && info.type == MyItemType::POTION)
		_slotImages[index]->SetBrushFromTexture(_potionTexture);
}

void UMyInvenUI::SetTextBox()
{
	if(_invenComp == nullptr)
		return;

	auto info = _invenComp->GetItemInfo_Index(_curIndex);
	
	if (info.itemId == -1 && info.type == MyItemType::NONE)
	{
		ItemInfo->SetText(FText::FromString(TEXT("ItemType : NONE \n ItemID : -1")));
	}

	if (info.itemId == 1 && info.type == MyItemType::POTION)
	{
		ItemInfo->SetText(FText::FromString(TEXT("ItemType : POTION \n ItemID : 1")));
	}
}


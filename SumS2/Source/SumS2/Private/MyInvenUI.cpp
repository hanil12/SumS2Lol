// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInvenUI.h"
#include "Components/UniformGridPanel.h"
#include "Components/Image.h"
#include "Components/Button.h"

bool UMyInvenUI::Initialize()
{
	Super::Initialize();

	auto array = Grid->GetAllChildren();

	for (auto widget : array)
	{
		auto button = Cast<UButton>(widget);
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

void UMyInvenUI::SetItem_Index(int32 index, FMyItemInfo info)
{
	if(info.itemId == 1 && info.type == MyItemType::POTION)
		_slotImages[index]->SetBrushFromTexture(_potionTexture);
}

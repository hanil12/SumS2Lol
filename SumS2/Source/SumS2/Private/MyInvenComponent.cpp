// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInvenComponent.h"

#include "MyItem.h"

// Sets default values for this component's properties
UMyInvenComponent::UMyInvenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	_items.SetNum(9);
}


// Called when the game starts
void UMyInvenComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyInvenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FMyItemInfo UMyInvenComponent::GetItemInfo_Index(int32 index)
{
	if(index < 0 || index >= _items.Num())
		return FMyItemInfo();

	if(_items[index] == nullptr)
		return FMyItemInfo();

	return _items[index]->GetInfo();
}

void UMyInvenComponent::AddItem(AMyItem* item)
{
	auto target = _items.FindByPredicate([](AMyItem* item)-> bool
	{
		if(item == nullptr)
			return true;
		return false;
	});

	// 빈칸이 없음
	if(target == nullptr)
		return;

	*target = item;
	// TODO : InventoryUI
	int32 targetIndex = 0;

	int64 temp1 = (int64)target;
	int64 temp2 = (int64)(&_items[0]);
	targetIndex = (temp1 - temp2) / sizeof(int64);

	itemAddEvent.Broadcast(targetIndex, item->GetInfo());
}

AMyItem* UMyInvenComponent::DropItem()
{
	return nullptr;
}

AMyItem* UMyInvenComponent::DropItem(int32 index)
{
	if(index >= _items.Num() || index < 0)
		return nullptr;

	if(_items[index] == nullptr)
		return nullptr;

	AMyItem* dropItem = _items[index];
	_items[index] = nullptr;
	// TODO : 실제 아이템이 바닥에 떨어지게
	// 1. GetOwner() -> Player
	// => Cast<MyPlayer> 
	// => MyPlayer의 Drop함수를 호출
	// player->DropItem(dropItem);

	// 2. ItemDropEvent를 만들어서
	// => MyPlayer의 Drop함수를 바인딩해서 간접호출

	return dropItem;
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"

UUIManager::UUIManager()
{
	AddUI_Constructor("Inven", TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrints/BP_MyInven.BP_MyInven_C'"));
	AddUI_Constructor("HpBar", TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrints/BP_MyHpbar.BP_MyHpbar_C'"));
}

void UUIManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUIManager::WidgetNum()
{
	UE_LOG(LogTemp, Error, TEXT("widget Classes %d"), _widgetMap.Num());
}

bool UUIManager::IsOpen(FString name)
{
	TSubclassOf<UUserWidget> widgetClass = GetUIClass(name);
	if(widgetClass == nullptr)
		return false;

	for (auto& widget : _widgetStack)
	{
		if(widget->GetClass() == widgetClass)
			return true;
	}

	return false;
}

UUserWidget* UUIManager::GetOrShowPopUp(FString name)
{
	TSubclassOf<UUserWidget> widgetClass = GetUIClass(name);
	if(widgetClass == nullptr)
		return nullptr;

	// 현재 켜져있는 UI인지 확인
	for (auto& widget : _widgetStack)
	{
		if(widget->GetClass() == widgetClass)
			return widget;
	}

	// 켜져있지 않다면 킨다.
	UUserWidget* widget = CreateWidget(GetWorld(), widgetClass);
	if (widget)
	{
		widget->AddToViewport(_zOrder);
		_zOrder++;
		_widgetStack.Push(widget);
	}

	return widget;
}

void UUIManager::ClosePopUp(FString name)
{
	TSubclassOf<UUserWidget> widgetClass = GetUIClass(name);
	if(widgetClass == nullptr)
		return;

	UUserWidget* target = nullptr;
	for (auto& widget : _widgetStack)
	{
		if (widget->GetClass() == widgetClass)
		{
			widget->RemoveFromParent();
			target = widget;
			break;
		}
	}

	if (target != nullptr)
	{
		_widgetStack.Remove(target);
	}
}

void UUIManager::ClosePopUp()
{
	if(_widgetStack.IsEmpty() == true)
		return;

	_widgetStack.Last()->RemoveFromParent();
	_widgetStack.Pop();
	_zOrder--;
}

void UUIManager::CloseAll()
{
	for (auto& widget : _widgetStack)
	{
		widget->RemoveFromParent();
	}

	_widgetStack.Empty();
	_zOrder = 1;
}

void UUIManager::AddUI_Constructor(FString name, FString path)
{
	ConstructorHelpers::FClassFinder<UUserWidget> bp(*path);

	if (bp.Succeeded())
	{
		_widgetMap.Add(name, bp.Class);
	}
}

TSubclassOf<UUserWidget> UUIManager::GetUIClass(FString name)
{
	if(_widgetMap.Find(name) == nullptr)
		return nullptr;

	return _widgetMap[name];
}

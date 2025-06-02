// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUIManager.h"

UMyUIManager::UMyUIManager()
{
	AddUI_Constructor("Inven", TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrints/BP_MyInven.BP_MyInven_C'"));
	AddUI_Constructor("HPBar", TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrints/BP_MyHpbar.BP_MyHpbar_C'"));
}

void UMyUIManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMyUIManager::AddUI_Constructor(FString name, FString path)
{
	ConstructorHelpers::FClassFinder<UUserWidget> widget(*path);
	if (widget.Succeeded())
	{
		_widgets.Add(name, widget.Class);
	}
}

void UMyUIManager::PrintHello()
{
	UE_LOG(LogTemp, Warning, TEXT("UIManager Test Count : %d"), _widgets.Num());
}

bool UMyUIManager::IsOpen(FString name)
{
	auto widgetClass = GetUIClass(name);
	if(widgetClass == nullptr)
		return false;

	for (auto& widget : _widgetStack)
	{
		if (widget->GetClass() == widgetClass)
			return true;
	}

	return false;
}

TSubclassOf<UUserWidget> UMyUIManager::GetUIClass(FString name)
{
	if(_widgets.Find(name) == nullptr)
		return nullptr;

	return _widgets[name];
}

UUserWidget* UMyUIManager::ShowPopUp(FString name)
{
	TSubclassOf<UUserWidget> widgetClass = *_widgets.Find(name);
	if(widgetClass == nullptr)
		return nullptr;

	for (auto& widget : _widgetStack)
	{
		if(widget->GetClass() == widgetClass)
			return widget;
	}

	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), widgetClass);
	if (widget)
	{
		widget->AddToViewport(_zOrder);
		_widgetStack.Add(widget);
		_zOrder++;
	}

	return widget;
}

void UMyUIManager::ClosePopUp(FString name)
{
	TSubclassOf<UUserWidget> widgetClass = *_widgets.Find(name);
	if (widgetClass == nullptr)
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

	if(target != nullptr)
		_widgetStack.Remove(target);
}

void UMyUIManager::ClosePopUp()
{
	if(_widgetStack.IsEmpty())
		return;

	_widgetStack.Last()->RemoveFromParent();
	_widgetStack.Pop();
	_zOrder--;
}

void UMyUIManager::CloseAllPopUp()
{
	for(auto& widget : _widgetStack)
		widget->RemoveFromParent();
	_widgetStack.Empty();
	_zOrder = 1;
}

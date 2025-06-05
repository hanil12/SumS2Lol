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

	auto playerController = GetWorld()->GetFirstPlayerController();
	if (playerController)
	{
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		FInputModeGameAndUI inputModeData;
		inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		playerController->SetInputMode(inputModeData);
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

	auto playerController = GetWorld()->GetFirstPlayerController();
	if (_widgetStack.IsEmpty() && playerController)
	{
		playerController->bShowMouseCursor = false;

		FInputModeGameOnly inputModeData;
		playerController->SetInputMode(inputModeData);
	}
}

void UUIManager::ClosePopUp()
{
	if(_widgetStack.IsEmpty() == true)
		return;

	_widgetStack.Last()->RemoveFromParent();
	_widgetStack.Pop();
	_zOrder--;

	auto playerController = GetWorld()->GetFirstPlayerController();
	if (_widgetStack.IsEmpty() && playerController)
	{
		playerController->bShowMouseCursor = false;

		FInputModeGameOnly inputModeData;
		playerController->SetInputMode(inputModeData);
	}
}

void UUIManager::CloseAll()
{
	for (auto& widget : _widgetStack)
	{
		widget->RemoveFromParent();
	}

	_widgetStack.Empty();
	_zOrder = 1;

	auto playerController = GetWorld()->GetFirstPlayerController();
	if (playerController)
	{
		playerController->bShowMouseCursor = false;

		FInputModeGameOnly inputModeData;
		playerController->SetInputMode(inputModeData);
	}
}

UUserWidget* UUIManager::GetOrShowSceneUI(TSubclassOf<UUserWidget> widgetClass)
{
	if (_sceneUI != nullptr && _sceneUI->GetClass() == widgetClass)
	{
		return _sceneUI;
	}

	if (_sceneUI != nullptr)
	{
		CloseSceneUI();
	}

	_sceneUI = CreateWidget(GetWorld(), widgetClass);
	_sceneUIClass = widgetClass;

	_sceneUI->AddToViewport();

	return _sceneUI;
}

void UUIManager::CloseSceneUI()
{
	_sceneUIClass = nullptr;

	_sceneUI->RemoveFromParent();
	_sceneUI = nullptr;

	return;
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

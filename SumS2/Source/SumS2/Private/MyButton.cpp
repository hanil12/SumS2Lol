// Fill out your copyright notice in the Description page of Project Settings.


#include "MyButton.h"

#include "MyInvenUI.h"

void UMyButton::SetCurIndex()
{
	if(widget == nullptr)
		return;
	widget->_curIndex = _curIndex;
	UE_LOG(LogTemp, Error,TEXT("Widget CurIndex : %d"), widget->_curIndex);
}

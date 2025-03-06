// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "MyPlayerController.h"
#include "MyStatComponent.h"
#include "MyAnimInstance.h"
#include "MyItem.h"

#include "Blueprint/UserWidget.h"
#include "MyInvenUI.h"
#include "Components/Button.h"
#include "MyInvenComponent.h"

AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// 상속관계 설정
	_springArm->SetupAttachment(GetCapsuleComponent());
	_camera->SetupAttachment(_springArm);

	_springArm->TargetArmLength = 500.0f;
	_springArm->SetRelativeRotation(FRotator(-35.0f, 0.0f, 0.0f));

	// Inventory
	static ConstructorHelpers::FClassFinder<UMyInvenUI> invenClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrints/BP_MyInven.BP_MyInven_C'"));
	if (invenClass.Succeeded())
	{
		_invenWidget = CreateWidget<UUserWidget>(GetWorld(),invenClass.Class);
	}

	_invenComponent = CreateDefaultSubobject<UMyInvenComponent>(TEXT("InvenComponent"));
}

void AMyPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto invenUI = Cast<UMyInvenUI>(_invenWidget);
	if (invenUI)
	{
		_invenComponent->itemAddEvent.AddUObject(invenUI, &UMyInvenUI::SetItem_Index);
		invenUI->Drop->OnClicked.AddDynamic(this, &AMyPlayer::Drop);
	}
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputCompnent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhancedInputCompnent)
	{
		enhancedInputCompnent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &AMyPlayer::Move);
		enhancedInputCompnent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &AMyPlayer::Look);
		enhancedInputCompnent->BindAction(_jumpAction, ETriggerEvent::Triggered, this, &AMyPlayer::JumpA);
		enhancedInputCompnent->BindAction(_attackAction, ETriggerEvent::Triggered, this, &AMyPlayer::Attack);
		enhancedInputCompnent->BindAction(_invenAction, ETriggerEvent::Started, this, &AMyPlayer::InvenOpen);
	}
}

void AMyPlayer::Move(const FInputActionValue& value)
{
	if (_isAttack) return;

	FVector2D moveVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (moveVector.Length() > 0.01f)
		{
			FVector forWard = GetActorForwardVector();
			FVector right = GetActorRightVector();

			_vertical = moveVector.Y;
			_horizontal = moveVector.X;

			AddMovementInput(forWard, moveVector.Y * _statComponent->GetSpeed());
			AddMovementInput(right, moveVector.X * _statComponent->GetSpeed());
		}
	}
}

void AMyPlayer::Look(const FInputActionValue& value)
{
	FVector2D lookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(lookAxisVector.X);
		AddControllerPitchInput(-lookAxisVector.Y);
	}
}

void AMyPlayer::JumpA(const FInputActionValue& value)
{
	if (_isAttack) return;

	bool isPress = value.Get<bool>();

	if (isPress)
	{
		ACharacter::Jump();
	}
}

void AMyPlayer::Attack(const FInputActionValue& value)
{
	if (_isAttack) return;

	bool isPress = value.Get<bool>();

	if (isPress)
	{
		_isAttack = true;

		_curAttackSection = (_curAttackSection) % 3 + 1;
		_animInstance->PlayAnimMontage();

		_animInstance->JumpToSection(_curAttackSection);
	}
}

void AMyPlayer::InvenOpen(const FInputActionValue& value)
{
	bool isPress = value.Get<bool>();

	if (isPress)
	{
		auto controller = Cast<AMyPlayerController>(GetController());
		if (_isInvenOpen)
		{
			if(controller)
				controller->HideUI();
			_invenWidget->RemoveFromViewport();
		}
		else
		{
			if(controller)
				controller->ShowUI();
			_invenWidget->AddToViewport();
		}
		_isInvenOpen = !_isInvenOpen;
	}
}

void AMyPlayer::AddItem(AMyItem* item)
{
	// TODO
	if (item && _invenComponent)
	{
		auto info = item->GetInfo();
		_invenComponent->AddItem(info.itemId, info.type);
	}
}

void AMyPlayer::Drop()
{
	UE_LOG(LogTemp, Error, TEXT("Drop"));
}

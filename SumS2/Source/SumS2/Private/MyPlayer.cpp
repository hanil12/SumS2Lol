// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Math/UnrealMathUtility.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Blueprint/UserWidget.h"
#include "MyInvenUI.h"
#include "Components/Button.h"
#include "MyInvenComponent.h"

#include "UIManager.h"
#include "MyCharacter.h"

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

	_invenComponent = CreateDefaultSubobject<UMyInvenComponent>(TEXT("InvenComponent"));

	bUseControllerRotationYaw = false;
}

void AMyPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	if(_sceneUIClass)
		UI->GetOrShowSceneUI(_sceneUIClass);
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
	FVector2D moveVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (moveVector.Length() > 0.01f)
		{
			FVector forWard = GetControlRotation().Vector();
			FVector right = forWard.RotateAngleAxis(90, FVector(0.0f,0.0f,1.0f));

			_vertical = moveVector.Y;
			_horizontal = moveVector.X;

			AddMovementInput(forWard, moveVector.Y * _statComponent->GetSpeed());
			AddMovementInput(right, moveVector.X * _statComponent->GetSpeed());

			GetCharacterMovement()->bUseControllerDesiredRotation = true;
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

		float degree = FMath::FindDeltaAngleDegrees(GetActorRotation().Yaw, GetControlRotation().Yaw);

		// 카메라 오른쪽을 넘어감, 나는 정면
		if (degree > 90.0f)
		{
			_isTurnRight = true;
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
		}
		// 카메라 왼쪽을 넘어감, 나는 정면
		else if (degree < -90.0f)
		{
			_isTurnLeft = true;
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
		}
		// 움직이거나, 공격
		else if (GetCharacterMovement()->Velocity.Size() > 0.1f || _isAttack)
		{
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
		}
		// 카메라, 정면 각도 차이의 절대값이 90도 미만
		else if(FMath::Abs(degree) < 0.1f)
		{
			_isTurnLeft = false;
			_isTurnRight = false;
			GetCharacterMovement()->bUseControllerDesiredRotation = false;
		}
	}
}

void AMyPlayer::JumpA(const FInputActionValue& value)
{
	bool isPress = value.Get<bool>();

	if (isPress)
	{
		GetGameInstance()->GetSubsystem<UUIManager>()->CloseAll();

		ACharacter::Jump();
	}
}

void AMyPlayer::Attack(const FInputActionValue& value)
{
	if (_isAttack) return;

	bool isPress = value.Get<bool>();

	if (isPress)
	{
		GetGameInstance()->GetSubsystem<UUIManager>()->GetOrShowPopUp("HpBar");

		_isAttack = true;

		_curAttackSection = (_curAttackSection) % 3 + 1;
		_animInstance->PlayAnimMontage();

		_animInstance->JumpToSection(_curAttackSection);
		GetCharacterMovement()->bUseControllerDesiredRotation = true;

		// 투사체
		if (_curAttackSection == 3)
		{
			FVector startPos = GetMesh()->GetSocketLocation(TEXT("s_throw"));
			FVector direction = _camera->GetForwardVector();

			auto projectile = GetWorld()->SpawnActor<AMyProjectile>(_projectileClass, startPos, FRotator::ZeroRotator);
			projectile->SetOwner(this);
			projectile->FireDirection(direction);
		}
	}
}

void AMyPlayer::InvenOpen(const FInputActionValue& value)
{
	bool isPress = value.Get<bool>();

	if (isPress)
	{
		// 인벤토리 UI를 연다.
		// 1. 어떤 키를 입력해서 UI를 열었을 때 누가 열었는지 Debug하기가 쉽지 않다.
		// 2. 어떤 키를 눌러서 꺼야하거나, 전체가 한번에 꺼져야한다면, 일일 다 부탁해야한다.
		// => UIManager를 만들어서 한번에 관리하자.

		if (GetGameInstance()->GetSubsystem<UUIManager>()->IsOpen("Inven"))
			GetGameInstance()->GetSubsystem<UUIManager>()->ClosePopUp("Inven");
		else
		{
			Cast<UMyInvenUI>(GetGameInstance()->GetSubsystem<UUIManager>()->GetOrShowPopUp("Inven"))->SyncInvenComp(_invenComponent);
		}
	}
}

void AMyPlayer::Attack_Hit()
{
	if (IsDead()) return;

	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRadius = 100.0f;

	FVector forward = _camera->GetForwardVector();
	FQuat quat = FQuat::FindBetweenVectors(FVector(0, 0, 1), forward);

	FVector center = GetActorLocation() + forward * _attackRange * 0.5f;
	FVector start = GetActorLocation() + forward * _attackRange * 0.5f;
	FVector end = GetActorLocation() + forward * _attackRange * 0.5f;

	bool bResult = GetWorld()->SweepSingleByChannel
	(
		OUT hitResult,
		start,
		end,
		quat,
		ECC_GameTraceChannel2,
		FCollisionShape::MakeCapsule(attackRadius, _attackRange * 0.5f),
		params
	);

	FColor drawColor = FColor::Green;

	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;
		AMyCharacter* victim = Cast<AMyCharacter>(hitResult.GetActor());
		if (victim)
		{
			FDamageEvent damageEvent = FDamageEvent();

			FVector hitPoint = hitResult.ImpactPoint;
			EFFECT_M->PlayEffect("MeleeAttack", hitPoint);
			victim->TakeDamage(_statComponent->GetAtk(), damageEvent, GetController(), this);
		}
	}

	DrawDebugCapsule(GetWorld(), center,
		_attackRange * 0.5f, attackRadius, quat, drawColor, false, 1.0f);
}

void AMyPlayer::AddItem(AMyItem* item)
{
	// TODO
	if (item && _invenComponent)
	{
		_invenComponent->AddItem(item);
	}
}

void AMyPlayer::Drop()
{
	UE_LOG(LogTemp, Error, TEXT("Drop"));

	int32 curDropIndex = -1;
	// invenUI에서 현재 선택한 curIndex
	auto invenUI = Cast<UMyInvenUI>(GetGameInstance()->GetSubsystem<UUIManager>()->GetOrShowPopUp("Inven"));
	if(invenUI)
		curDropIndex = invenUI->_curIndex;

	auto item = _invenComponent->DropItem(curDropIndex);
	if(item == nullptr)
		return;

	invenUI->SetItem_Index(curDropIndex, FMyItemInfo());

	FVector playerLocation = GetActorLocation();

	float dropRadius = 200.0f;
	FVector randomOffset = FMath::VRand() * FMath::FRandRange(100.0f, dropRadius);
	FVector dropLocation = playerLocation + randomOffset;
	dropLocation.Z = 40.0f;

	item->SetActorLocation(dropLocation);
	item->SetActorHiddenInGame(false);
	item->SetActorEnableCollision(true);
}

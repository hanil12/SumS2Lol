// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"

#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyHpBar.h"
#include "MyPlayerController.h"
#include "MyStatComponent.h"

#include "Animation/AnimInstance.h"
#include "MyAnimInstance.h"

AMyEnemy::AMyEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	_hpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	_hpBarWidget->SetupAttachment(GetMesh());
	_hpBarWidget->SetWidgetSpace(EWidgetSpace::World);

	static ConstructorHelpers::FClassFinder<UMyHpBar> hpBarClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrints/BP_MyHpbar.BP_MyHpbar_C'"));
	if (hpBarClass.Succeeded())
	{
		_hpBarWidget->SetWidgetClass(hpBarClass.Class);
	}
}

void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();

	// HpBar...ProgressBar...Percent변경될 때 호출되는 함수
	auto hpBar = Cast<UMyHpBar>(_hpBarWidget->GetWidget());
	if (hpBar)
	{
		_statComponent->_hpChanged.AddUObject(hpBar, &UMyHpBar::SetHpBarValue);
	}
}

void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto playerCameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;

	if (playerCameraManager)
	{
		FVector hpBarLocation = _hpBarWidget->GetComponentLocation();
		FVector cameraLocation = playerCameraManager->GetCameraLocation();
		FRotator rot = UKismetMathLibrary::FindLookAtRotation(hpBarLocation, cameraLocation);
		_hpBarWidget->SetWorldRotation(rot);
	}
}

void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyEnemy::Attack_AI()
{
	if (_isAttack) return;

	_isAttack = true;

	_curAttackSection = (_curAttackSection) % 3 + 1;
	_animInstance->PlayAnimMontage();

	_animInstance->JumpToSection(_curAttackSection);
}

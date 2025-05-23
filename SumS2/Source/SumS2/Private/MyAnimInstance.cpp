// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

#include "MyCharacter.h"
#include "MyPlayer.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Math/UnrealMathUtility.h"

UMyAnimInstance::UMyAnimInstance()
{
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	auto pawn = TryGetPawnOwner();
	AMyCharacter* character = Cast<AMyCharacter>(pawn); // dynamicCast
	if (character != nullptr)
	{
		_speed = character->GetVelocity().Size();
		_isFalling = character->GetMovementComponent()->IsFalling();
		_vertical = character->My_Vertical();
		_horizontal = character->My_Horizontal();
		_isDead = character->IsDead();
		_isAttacking = character->IsAttacking();

		FRotator controllRotation = character->GetControlRotation();
		FRotator actorRotation = character->GetActorRotation();
		_yaw = FMath::FindDeltaAngleDegrees(actorRotation.Yaw, controllRotation.Yaw);
		_pitch = FMath::FindDeltaAngleDegrees(actorRotation.Pitch, controllRotation.Pitch);
		auto player = Cast<AMyPlayer>(character);
		if(player)
		{
			_isTurnLeft = player->_isTurnLeft;
			_isTurnRight = player->_isTurnRight;
		}
	}
}

void UMyAnimInstance::PlayAnimMontage()
{
	if(_animMontage == nullptr)
		return;

	if (!Montage_IsPlaying(_animMontage))
	{
		// Attack Delegate 실행
		//_attackStart.Execute();
		//_attackStart2.Execute(1,2);
		//_attackStart3.Broadcast(); // 멀티캐스트

		Montage_Play(_animMontage);
	}
}

void UMyAnimInstance::AnimNotify_Attack_Hit()
{
	// 나를 갖고 있는 캐릭터의 AttackHit
	if(_hitEvent.IsBound())
		_hitEvent.Broadcast();
}

void UMyAnimInstance::AnimNotify_Dead()
{
	// 죽었을 때 나오는 이벤트들
	if(_deadEvent.IsBound())
		_deadEvent.Broadcast();
}

void UMyAnimInstance::JumpToSection(int32 sectionIndex)
{
	// Section1,Section2, Section3
	FName sectionName = FName(*FString::Printf(TEXT("Section%d"), sectionIndex));
	Montage_JumpToSection(sectionName, _animMontage);
}

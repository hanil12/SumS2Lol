// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "MyPlayerController.h"
#include "MyStatComponent.h"
#include "MyAnimInstance.h"
#include "MyItem.h"

#include "MyProjectile.h"
#include "MyGameInstance.h"
#include "Engine/DamageEvents.h"

#include "MyCharacter.generated.h"

UCLASS()
class SUMS2_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*UFUNCTION()
	void OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult);*/

	UFUNCTION()
	void TestDelegate();

	UFUNCTION()
	int32 TestDelegate2(int32 a, int32 b);

	UFUNCTION()
	void AttackEnd(class UAnimMontage* Montage, bool bInterrupted);

	float My_Vertical() { return _vertical; }
	float My_Horizontal() { return _horizontal; }
	float AttackRange() { return _attackRange; }

	virtual void Attack_Hit();
	void DeadEvent();

	void AddHp(float amount);

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	bool IsDead();
	bool IsAttacking() { return _isAttack; }

protected:
	UPROPERTY()
	class UMyAnimInstance* _animInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	class UMyStatComponent* _statComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	bool _isAttack;

	int32 _curAttackSection = 1;

	float _vertical = 0.0f;
	float _horizontal = 0.0f;

	UPROPERTY(EditAnywhere)
	float _attackRange = 500.0f;
};

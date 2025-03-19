// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectile.h"

#include "Components/MeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMyProjectile::AMyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	_collider = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	_movementComp = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");

	RootComponent = _collider;
	_mesh->SetupAttachment(_collider);
}

// Called when the game starts or when spawned
void AMyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator curRot = GetActorRotation();

	curRot.Yaw += DeltaTime * 200.0f;
	curRot.Pitch += DeltaTime * 200.0f;

	SetActorRotation(curRot);
}

void AMyProjectile::FireDirection(const FVector& direction)
{
	_movementComp->Velocity = direction * _movementComp->InitialSpeed;
}


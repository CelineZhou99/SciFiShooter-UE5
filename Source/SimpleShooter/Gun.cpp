// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	// spawn particle effect for muzzle flash
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, "MuzzleFlashSocket");

	APawn *OwnerPawn = Cast<APawn>(GetOwner());

	if (!OwnerPawn)
	{
		return;
	}
	AController *OwnerController = OwnerPawn->GetController();
	if (OwnerController)
	{
		FVector Location = FVector::ZeroVector;
		FRotator Rotation = FRotator::ZeroRotator;
		OwnerController->GetPlayerViewPoint(Location, Rotation);

		// start point + vector that points in the direction of the rotation * amount of distance
		FVector End = Location + Rotation.Vector() * MaxRange;

		FHitResult HitResult;

		// ignore some actors for the collision by ray tracing
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());

		// only draw debug point if hit
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params))
		{
			// the negative of where it came from
			FVector ShotDirection = -Rotation.Vector();
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletHit, HitResult.ImpactPoint, ShotDirection.Rotation());

			// cause damage
			AActor *VictimActor = HitResult.GetActor();
			if (VictimActor)
			{
				// damage event for bullet
				FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
				VictimActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			}
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

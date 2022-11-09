// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGun();

	// trigger the gun
	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	USceneComponent *Root;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USkeletalMeshComponent *Mesh;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem *MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem *BulletHit;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = 10;
};

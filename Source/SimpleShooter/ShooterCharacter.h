// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	void Shoot();

private:
	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	// for controller looking around
	void LookUpRate(float AxisValue);

	void LookRightRate(float AxisValue);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationRate = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class AGun> GunClass;

	UPROPERTY()
	class AGun *Gun;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	float Health;
};

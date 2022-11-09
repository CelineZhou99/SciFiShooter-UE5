// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    // run ai behavior tree
    if (AIBehavior)
    {
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector("StartLocation", GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Take over by services in behaviortree
    // APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    // // if lineofsight then move and set focus
    // // else clear focus and stop movement
    // if (LineOfSightTo(PlayerPawn))
    // {
    //     // set playerlocation
    //     // set lastknown
    //     GetBlackboardComponent()->SetValueAsVector("PlayerLocation", PlayerPawn->GetActorLocation());
    //     GetBlackboardComponent()->SetValueAsVector("LastKnownPlayerLocation", PlayerPawn->GetActorLocation());
    // }
    // else
    // {
    //     // clear playerlocation
    //     GetBlackboardComponent()->ClearValue("PlayerLocation");
    // }
}

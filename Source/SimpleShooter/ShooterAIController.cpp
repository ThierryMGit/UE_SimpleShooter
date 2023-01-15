// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

AShooterAIController::AShooterAIController(){}

bool AShooterAIController::isDead() const
{
    AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(GetPawn());

    if (!ShooterCharacter) return false;

    return ShooterCharacter->isDead();
}

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehavior) {
        RunBehaviorTree(AIBehavior);

        APawn* AIPawn = GetPawn();
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), AIPawn->GetActorLocation());

        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
    }
}


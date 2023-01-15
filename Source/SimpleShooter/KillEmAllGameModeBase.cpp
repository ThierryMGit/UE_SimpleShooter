// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillEmAllGameModeBase::PawnKilled(APawn* Pawn)
{
    Super::PawnKilled(Pawn);

    APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
    if(PlayerController) {
        EndGame(false);
    } else {
        for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld())) {
            if (!Controller->isDead()) {
                return;
            }
        }
        EndGame(true);
    }
}

void AKillEmAllGameModeBase::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld())) {
        if(Controller->IsPlayerController()) {
            Controller->GameHasEnded(Controller->GetPawn(), bIsPlayerWinner);
        } else {
            Controller->GameHasEnded(Controller->GetPawn(), !bIsPlayerWinner);
        }
    }
}

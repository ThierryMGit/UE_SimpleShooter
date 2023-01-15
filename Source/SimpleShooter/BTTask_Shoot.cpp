// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "ShooterAIController.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AShooterAIController* AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());

    if (!AIController) return EBTNodeResult::Failed;

    AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(AIController->GetPawn());

    if (!ShooterCharacter) return EBTNodeResult::Failed;

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn) return EBTNodeResult::Failed;

    AShooterCharacter* PlayerCharacter = Cast<AShooterCharacter>(PlayerPawn);

    ShooterCharacter->Shoot();

    if(PlayerCharacter->isDead()) {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("isPlayerDead"), true);
    }

    return EBTNodeResult::Succeeded;
}

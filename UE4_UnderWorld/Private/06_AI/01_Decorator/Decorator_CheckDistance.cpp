// Fill out your copyright notice in the Description page of Project Settings.


#include "06_AI/01_Decorator/Decorator_CheckDistance.h"

#include "AIController.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UDecorator_CheckDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	bool result = false;

	if (GetSelectedBlackboardKey() == "Target")
	{
		auto obj = OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
		if (obj != nullptr)
		{
			AActor* target = Cast<AActor>(obj);
			if (target != nullptr)
			{
				// Ÿ�ٰ��� �Ÿ��� ���ϰ� ���Ÿ� �̳��� true
				float distancefromTarget = OwnerComp.GetAIOwner()->GetPawn()->GetDistanceTo(target);
				if (distancefromTarget <= distance)
				{
					result = true;
				}
			}
		}
	}
	else if (GetSelectedBlackboardKey() == "PatrolLocation")
	{
		//// ������ ��ġ�� ���� �� ��ġ�� �Ÿ��� ���ϰ� ���Ÿ� �̳��� true
		//auto patrolVector = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
		//FVector spawnVector = OwnerComp.GetAIOwner()->GetPawn<AMonsterCharacter>()->GetSpawnLocation();
		//float distancefromTarget = FVector::Distance(spawnVector, patrolVector);
		//if (distancefromTarget <= distance)
		//{
		//	return true;
		//}
	}
	if (bInversed)
		result = !result;
	return result;
}

FString UDecorator_CheckDistance::GetStaticDescription() const
{
	if (bInversed)
	{
		return "Check distance to target > " + FString::FormatAsNumber(distance);
	}
	else
	{
		return "Check distance to target <= " + FString::FormatAsNumber(distance);
	}
}

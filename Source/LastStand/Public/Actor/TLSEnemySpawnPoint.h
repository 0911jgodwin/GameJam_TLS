// Copyright JGodwin

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "TLSEnemySpawnPoint.generated.h"

class ATLSEnemy;
/**
 * 
 */
UCLASS()
class LASTSTAND_API ATLSEnemySpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Type")
	TSubclassOf<ATLSEnemy> EnemyType;
};

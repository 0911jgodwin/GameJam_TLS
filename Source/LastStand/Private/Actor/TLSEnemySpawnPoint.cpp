// Copyright JGodwin


#include "Actor/TLSEnemySpawnPoint.h"

#include "Character/TLSEnemy.h"

void ATLSEnemySpawnPoint::SpawnEnemy()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ATLSEnemy* Enemy = GetWorld()->SpawnActorDeferred<ATLSEnemy>(EnemyType, GetActorTransform());
	Enemy->FinishSpawning(GetActorTransform());
	Enemy->SpawnDefaultController();
}

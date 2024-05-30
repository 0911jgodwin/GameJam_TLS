// Copyright JGodwin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TLSEnemySpawnVolume.generated.h"

class ATLSEnemySpawnPoint;
class UBoxComponent;
UCLASS()
class LASTSTAND_API ATLSEnemySpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ATLSEnemySpawnVolume();

	UPROPERTY(BlueprintReadOnly)
	bool bReached = false;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	TArray<ATLSEnemySpawnPoint*> SpawnPoints;

private:	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> Box;

};

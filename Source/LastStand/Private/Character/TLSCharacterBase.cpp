// Copyright JGodwin


#include "Character/TLSCharacterBase.h"


ATLSCharacterBase::ATLSCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATLSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
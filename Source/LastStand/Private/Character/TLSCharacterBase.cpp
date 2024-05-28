// Copyright JGodwin


#include "Character/TLSCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "LastStand/LastStand.h"
#include "AbilitySystem/TLSAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"


ATLSCharacterBase::ATLSCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* ATLSCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATLSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATLSCharacterBase::InitAbilityActorInfo()
{
}

void ATLSCharacterBase::AddCharacterAbilities()
{
	UTLSAbilitySystemComponent* TLSASC = CastChecked<UTLSAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	TLSASC->AddCharacterAbilities(StartupAbilities);
}
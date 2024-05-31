// Copyright JGodwin


#include "Character/TLSCharacterBase.h"
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
}

UAbilitySystemComponent* ATLSCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATLSCharacterBase::Die()
{
	MulticastHandleDeath();
}

void ATLSCharacterBase::MulticastHandleDeath_Implementation()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
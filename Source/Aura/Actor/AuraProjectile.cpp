// Copyright Terren 


#include "AuraProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Aura/Aura.h"
#include "Components/AudioComponent.h"

// Sets default values
AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);
	Sphere->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.0f;
	ProjectileMovement->MaxSpeed = 550.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
}

void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);
	LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, RootComponent);
}

void AAuraProjectile::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		if (LoopingSoundComponent) LoopingSoundComponent->Stop();
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	}
	Super::Destroyed();
}

void AAuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (LoopingSoundComponent) LoopingSoundComponent->Stop();
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	
	if (HasAuthority())
	{
		Destroy();
	}
	else
	{
		bHit = true;
	}
}



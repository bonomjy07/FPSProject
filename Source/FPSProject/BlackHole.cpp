// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	InnerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerSphereComp->SetSphereRadius(100.f);
	InnerSphereComp->SetupAttachment(MeshComp);

	OuterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComp"));
	OuterSphereComp->SetSphereRadius(500.f);
	OuterSphereComp->SetupAttachment(MeshComp);

	Strength = -2000.f;
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
	//ActivateBlackHole();
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingComps;

	// Suck it up
	if (OuterSphereComp)
	{
		OuterSphereComp->GetOverlappingComponents(OverlappingComps);
		for (int32 i = 0; i < OverlappingComps.Num(); ++i)
		{
			UPrimitiveComponent* Comp = OverlappingComps[i];
			if (Comp && !Comp->IsPendingKill() && Comp->IsSimulatingPhysics())
			{
				float Radius = OuterSphereComp->GetScaledSphereRadius();
				Comp->AddRadialForce(GetActorLocation(), Radius, Strength, ERadialImpulseFalloff::RIF_Linear, true);
			}
		}
	}

	// Destroy
	if (InnerSphereComp)
	{
		InnerSphereComp->GetOverlappingComponents(OverlappingComps);
		for (int32 i = 0; i < OverlappingComps.Num(); ++i)
		{
			UPrimitiveComponent* Comp = OverlappingComps[i];
			if (Comp && !Comp->IsPendingKill() && Comp->IsSimulatingPhysics())
			{
				AActor* Actor = Comp->GetAttachmentRootActor();
				if (Actor && !Actor->IsPendingKill())
				{
					Actor->Destroy();
				}
			}
		}
	}
}

void ABlackHole::ActivateBlackHole()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (int32 iComp = 0; iComp < OverlappingActors.Num(); ++iComp)
	{

	}
}


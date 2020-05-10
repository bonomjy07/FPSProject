// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSObjectiveActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSProjectCharacter.h"

// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereComponent->SetupAttachment(MeshComponent);

	bReplicates = true;
	bReplicateMovement = true;
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();

	PlayEffect();
}

void AFPSObjectiveActor::PlayEffect()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFx, GetActorLocation());
}

// Called every frame
void AFPSObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Role == ROLE_Authority)
	{
		FVector NewLocation = GetActorLocation();
		FRotator NewRotation = GetActorRotation();
		float RunningTime = GetGameTimeSinceCreation();
		NewLocation.Z += 100.f * (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
		NewRotation.Yaw += 40.f * DeltaTime;

		SetActorLocationAndRotation(NewLocation, NewRotation);
	}
}

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffect();

	if (Role == ROLE_Authority)
	{
		AFPSProjectCharacter* MyCharacter = Cast<AFPSProjectCharacter>(OtherActor);
		if (MyCharacter)
		{
			MyCharacter->bIsCarryObjective = true;

			Destroy();
		}
	}
}


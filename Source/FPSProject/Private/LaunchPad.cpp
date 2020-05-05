// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(200.f));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::HandleOverlap);
	RootComponent = BoxComp;

	ArrowMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMeshComp"));
	ArrowMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ArrowMeshComp->SetupAttachment(RootComponent);

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	BaseMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BaseMeshComp->SetupAttachment(RootComponent);

	LaunchStrength = 1000.f;
	LaunchPitchOffset = 35.f;
}

void ALaunchPad::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Calculate Launch velocity
	FRotator LaunchRotation = GetActorRotation();
	LaunchRotation.Pitch += LaunchPitchOffset;
	FVector LaunchDirection = LaunchRotation.Vector();
	FVector LaunchVelocity = LaunchDirection * LaunchStrength;

	// Launch the character
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (Character)
	{
		Character->LaunchCharacter(LaunchVelocity, true, true);

		// Spawn fx
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchPadEffect, GetActorLocation());
		UGameplayStatics::PlaySound2D(this, LaunchPadSound);
	}
	// Launch the actor who has component simulating physics
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVelocity * OtherComp->GetMass());

		// Spawn fx
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchPadEffect, GetActorLocation());
		UGameplayStatics::PlaySound2D(this, LaunchPadSound);
	}
}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


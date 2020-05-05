// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

UCLASS()
class FPSPROJECT_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class UParticleSystem* PickupFx;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayEffect();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Use this instead of OnCoponentOverlap()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};

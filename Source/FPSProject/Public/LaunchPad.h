// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

UCLASS()
class FPSPROJECT_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	// Root Component
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* ArrowMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* BaseMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class UParticleSystem* LaunchPadEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class USoundBase* LaunchPadSound;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchStrength;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchPitchOffset;

	// Launch the overlapped actor
	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

UCLASS()
class FPSPROJECT_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHole();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Coponents")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Coponents")
	class USphereComponent* InnerSphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Coponents")
	class USphereComponent* OuterSphereComp;

	UPROPERTY(EditAnywhere, Category = "Power")
	float Strength;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ActivateBlackHole();
};

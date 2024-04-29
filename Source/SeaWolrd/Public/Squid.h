// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Squid.generated.h"

UCLASS()
class SEAWOLRD_API ASquid : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASquid();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 300;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "TinkyWinky.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class SEAWOLRD_API ATinkyWinky : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATinkyWinky();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* FirePosition;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> Magazine;

public: 
	UPROPERTY(EditAnywhere, Category = "Camera")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, Category = "Camera")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* PlayerMappingContext;

	/*UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<class ABullet> Magazine;*/

public:
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveIA;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookUpIA;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TurnIA;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpIA;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireIA;

	void Move(const FInputActionValue& Value);

	void LookUp(const FInputActionValue& Value);

	void Turn(const FInputActionValue& Value);

	void InputJump(const FInputActionValue& Value);

	void InputFire(const FInputActionValue& Value);

public:
		UPROPERTY(VisibleAnywhere, Category = "Move")
	float MoveSpeed;

private:
	FVector MoveDirection;


};

// Fill out your copyright notice in the Description page of Project Settings.


#include "TinkyWinky.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Bullet.h"


// Sets default values
ATinkyWinky::ATinkyWinky()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> InitMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/BP/TinkyWinky/Main_teletubbies_red/source/Teletubbies_-_red/Teletubbies.Teletubbies'"));

	if (InitMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(InitMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));
	}

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0, 0, 50), FRotator(-20, 0, 0));
	SpringArmComp->TargetArmLength = 530;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;
}

// Called when the game starts or when spawned
void ATinkyWinky::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

// Called every frame
void ATinkyWinky::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveDirection = FTransform(GetControlRotation()).TransformVector(MoveDirection);

	/*FVector P0 = GetActorLocation();
	FVector vt = MoveDirection * MoveSpeed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P);*/
	AddMovementInput(MoveDirection);

	MoveDirection = FVector::ZeroVector;
}

// Called to bind functionality to input
void ATinkyWinky::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &ATinkyWinky::Move);
		EnhancedInputComponent->BindAction(LookUpIA, ETriggerEvent::Triggered, this, &ATinkyWinky::LookUp);
		EnhancedInputComponent->BindAction(TurnIA, ETriggerEvent::Triggered, this, &ATinkyWinky::Turn);
		EnhancedInputComponent->BindAction(JumpIA, ETriggerEvent::Triggered, this, &ATinkyWinky::InputJump);
		EnhancedInputComponent->BindAction(FireIA, ETriggerEvent::Triggered, this, &ATinkyWinky::InputFire);

	}
}

void ATinkyWinky::Move(const FInputActionValue& Value)
{
	const FVector CurrentValue = Value.Get<FVector>();

	if (Controller)
	{
		MoveDirection.Y = CurrentValue.X;
		MoveDirection.X = CurrentValue.Y;

	}
}

void ATinkyWinky::LookUp(const FInputActionValue& Value)
{
	const float _CurrentValue = Value.Get<float>();
	AddControllerPitchInput(_CurrentValue);
}

void ATinkyWinky::Turn(const FInputActionValue& Value)
{
	const float _CurrentValue = Value.Get<float>();
	AddControllerYawInput(_CurrentValue);

}

void ATinkyWinky::InputJump(const FInputActionValue& Value)
{
	Jump();
}

void ATinkyWinky::InputFire(const FInputActionValue& Value)
{
	/*FTransform firePosion = WeaponMeshComp->GetSocketTransform(TEXT("FirePosition"));
	Getworld()->SpawnActor<ABullet>(Magazine, fireposition);*/
}


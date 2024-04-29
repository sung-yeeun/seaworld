// Fill out your copyright notice in the Description page of Project Settings.


#include "Fish.h"
#include "Components/BoxComponent.h"

// Sets default values
AFish::AFish()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBoxComponent"));
	SetRootComponent(BoxComp);

	const FVector BoxSize = FVector(32.0f, 45.0f, 20.0f);
	BoxComp->SetBoxExtent(BoxSize);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));
	MeshComp->SetupAttachment(BoxComp);

	MeshComp->SetRelativeLocation(FVector(0, 0, -50));


}

// Called when the game starts or when spawned
void AFish::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFish::Move()
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * MoveSpeed * GetWorld()->GetDeltaSeconds());

}

// Called every frame
void AFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}

// Called to bind functionality to input
void AFish::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


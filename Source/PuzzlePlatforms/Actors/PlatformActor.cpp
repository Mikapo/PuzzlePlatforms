// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformActor.h"
#include "Components/SphereComponent.h"





// Sets default values
APlatformActor::APlatformActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	TargetLocationComponent = CreateDefaultSubobject<USphereComponent>("TargetDirection");
	TargetLocationComponent->SetupAttachment(Mesh);
	

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	
	
}

// Called when the game starts or when spawned
void APlatformActor::BeginPlay()
{

	UGameInstance* GameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Game Instance: %s"), *GameInstance->GetName())
	}


	Super::BeginPlay();

	if (HasAuthority())
	{
		InitialLocation = GetActorLocation();
		TargetLocation = TargetLocationComponent->GetComponentLocation();
	}
	
}

// Called every frame
void APlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (HasAuthority() && bMoving) Move();
}

void APlatformActor::Trigger(const bool& Value)
{
	if (Value) NumberOfActivePressurePlates++;
	else NumberOfActivePressurePlates--;

	if (NumberOfActivePressurePlates < 0)NumberOfActivePressurePlates = 0;

	if (NumberOfActivePressurePlates > 0) bMoving = true;
	else bMoving = false;
}

void APlatformActor::Move()
{
	FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), TargetLocation, GetWorld()->GetDeltaSeconds(), Speed);
	SetActorLocation(NewLocation);
	
	if (FMath::IsNearlyZero((GetActorLocation() - TargetLocation).Size()))
	{
		if (bMovingBack) TargetLocation = TargetLocationComponent->GetComponentLocation();
		else TargetLocation = InitialLocation;

		bMovingBack = !bMovingBack;
	}
}


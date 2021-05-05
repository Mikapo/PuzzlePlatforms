// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlateActor.h"
#include "Components/BoxComponent.h"
#include "PuzzlePlatforms/Characters/BaseCharacter.h"
#include "PuzzlePlatforms/Actors/PlatformActor.h"
#include "TimerManager.h"

// Sets default values
APressurePlateActor::APressurePlateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->SetupAttachment(BaseMesh);

	PressurePlateArea = CreateDefaultSubobject<UBoxComponent>(TEXT("PressurePlateArea"));
	PressurePlateArea->SetupAttachment(BaseMesh);

	PressurePlateArea->OnComponentBeginOverlap.AddDynamic(this, &APressurePlateActor::OnOverlapBegin);
	PressurePlateArea->OnComponentEndOverlap.AddDynamic(this, &APressurePlateActor::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APressurePlateActor::BeginPlay()
{
	Super::BeginPlay();

	for (APlatformActor* Platform : Platforms)
	{
		Platform->Trigger(false);
	}
	
}

void APressurePlateActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{
		OverlappingCharacters.Add(Player);
		SetPressed(true);
	}
}

void APressurePlateActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor)) OverlappingCharacters.Remove(Player);
	if (OverlappingCharacters.Num() != 0) return;
	
	SetPressed(false);

}

void APressurePlateActor::SetPressed(const bool& Pressed)
{
	for (APlatformActor* Platform : Platforms)
	{
		Platform->Trigger(Pressed);
	}

	if (Pressed) GetWorld()->GetTimerManager().SetTimer(ButtonAnimationHandle, this, &APressurePlateActor::PressInAnimation, 0.01f, true);
	else GetWorld()->GetTimerManager().SetTimer(ButtonAnimationHandle, this, &APressurePlateActor::PressOutAnimation, 0.01f, true);

}

void APressurePlateActor::PressInAnimation()
{
	FVector ButtonPosition = FMath::VInterpConstantTo(ButtonMesh->GetRelativeLocation(), PressedRelativeButtonPosition, GetWorld()->GetDeltaSeconds(), ButtonSpeed);
	ButtonMesh->SetRelativeLocation(ButtonPosition);

	float Distance = (ButtonMesh->GetRelativeLocation() - PressedRelativeButtonPosition).Size();

	if (FMath::IsNearlyZero(Distance))
	{
		GetWorld()->GetTimerManager().ClearTimer(ButtonAnimationHandle);
	}
}

void APressurePlateActor::PressOutAnimation()
{
	FVector ButtonPosition = FMath::VInterpConstantTo(ButtonMesh->GetRelativeLocation(), InitialRelativeButtonPosition, GetWorld()->GetDeltaSeconds(), ButtonSpeed);
	ButtonMesh->SetRelativeLocation(ButtonPosition);

	float Distance = (ButtonMesh->GetRelativeLocation() - InitialRelativeButtonPosition).Size();

	if (FMath::IsNearlyZero(Distance))
	{
		GetWorld()->GetTimerManager().ClearTimer(ButtonAnimationHandle);
	}
}

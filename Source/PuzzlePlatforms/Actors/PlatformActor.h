// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformActor.generated.h"

class USphereComponent;
class APressurePlateActor;

UCLASS()
class PUZZLEPLATFORMS_API APlatformActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Trigger(const bool& Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void Move();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (ToolTip = "Used for setting platfrom end location"))
	USphereComponent* TargetLocationComponent;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float Speed = 200;

	FVector InitialLocation;
	FVector TargetLocation;
	bool bMovingBack = false;
	bool bMoving = true;
	int32 NumberOfActivePressurePlates = 0;
	
};

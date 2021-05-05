// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlateActor.generated.h"

class UBoxComponent;
class APlatformActor;
class ABaseCharacter;
UCLASS()
class PUZZLEPLATFORMS_API APressurePlateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlateActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	/*FUNCTIONS*/

	UFUNCTION() 
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() 
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetPressed(const bool& Pressed);
	void PressInAnimation();
	void PressOutAnimation();

	/*COMPONENTS*/

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ButtonMesh;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* PressurePlateArea;

	/*VARIABLES*/

	//All Platforms that this PressurePlate controls
	UPROPERTY(EditAnywhere, Category = "Platforms")
	TArray<APlatformActor*> Platforms;
	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector InitialRelativeButtonPosition;
	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector PressedRelativeButtonPosition;
	UPROPERTY(EditAnywhere, Category = "Settings")
	float ButtonSpeed = 10;

	TArray<ABaseCharacter*> OverlappingCharacters;
	FTimerHandle ButtonAnimationHandle;




};

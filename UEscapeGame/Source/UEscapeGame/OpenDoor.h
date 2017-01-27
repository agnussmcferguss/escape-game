// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UESCAPEGAME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	void OpenDoor();

	void CloseDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.0;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(VisibleAnywhere)
	AActor* ActorThatOpens = nullptr;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.0f;

	UPROPERTY(EditAnywhere)
	float MassThreshold = 50.0;

	float LastDoorOpenTime = -1.0f;

	AActor* Owner = nullptr; // The owning actor

	float GetTotalMassOfActorsOnPlate();
};

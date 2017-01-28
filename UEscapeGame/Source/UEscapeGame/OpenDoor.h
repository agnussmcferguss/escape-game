// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UESCAPEGAME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category="OpenDoor")
	float GetTotalMassOfActorsOnPlate() const;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OpenDoor;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent CloseDoor;

private:

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float PressurePlateMassThreshold = 50.0;
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "UEscapeGame.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	/// Check that we have a valid pressure plate
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate trigger volume"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the trigger every frame
	if (GetTotalMassOfActorsOnPlate() > PressurePlateMassThreshold) {
		// Open the door
		OnOpenRequest.Broadcast();
	} else {
		OnCloseRequest.Broadcast();
	}
		
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0;

	/// Check to see if the pressure plate volume is valid
	if (PressurePlate != nullptr) {

		// Get a list of the physics actors on the plate
		TSet<AActor*> OverlappingActors;
		PressurePlate->GetOverlappingActors(OverlappingActors, nullptr);

		// For each actor, add its mass to the total mass
		for (const auto& IterActor : OverlappingActors) {
			TotalMass += IterActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	} 

	return TotalMass;
}
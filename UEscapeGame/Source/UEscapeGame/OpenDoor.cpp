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

	// Set the ActorThatOpens
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	Owner = GetOwner();
	
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the trigger every frame
	if (GetTotalMassOfActorsOnPlate() > MassThreshold) {
		// Open the door
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// check if it's time to close the door
	float currentTime = GetWorld()->GetTimeSeconds();
	if (currentTime > LastDoorOpenTime + DoorCloseDelay) {
		CloseDoor();
	}
		
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	// Initialise the Total Mass
	float TotalMass = 0.0;

	// Get a list of the physics actors on the plate
	if (PressurePlate) {
		TSet<AActor*> OverlappingActors;
		//TSubclassOf<> ClassFilter();
		PressurePlate->GetOverlappingActors(OverlappingActors, nullptr);

		// For each actor, add its mass to the total mass
		for (const auto& IterActor : OverlappingActors) {

			TotalMass += IterActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}

	return TotalMass;
}

void UOpenDoor::OpenDoor()
{
	FRotator currentRotation = Owner->GetActorRotation();
	Owner->SetActorRotation(FRotator(0.0, OpenAngle, 0.0));
}

void UOpenDoor::CloseDoor()
{
	FRotator currentRotation = Owner->GetActorRotation();
	Owner->SetActorRotation(FRotator(0.0, 0.0, 0.0));
}
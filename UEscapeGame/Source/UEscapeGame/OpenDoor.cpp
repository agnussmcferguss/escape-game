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
	// If the actor that opens the door is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
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
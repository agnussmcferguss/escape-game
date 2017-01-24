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


void UOpenDoor::OpenDoor()
{
	// Find the owning Actor
	AActor* Owner = GetOwner();

	FRotator currentRotation = Owner->GetActorRotation();
	FRotator deltaRotation = FRotator(0.0, 90.0, 0.0);

	Owner->SetActorRotation(currentRotation + deltaRotation);
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Set the ActorThatOpens
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the trigger every frame
	// If the actor that opens the door is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens) && !isOpen) {
		// Open the door
		OpenDoor();
		isOpen = true;
	}
		
}


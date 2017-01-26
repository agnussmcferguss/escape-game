// Fill out your copyright notice in the Description page of Project Settings.

#include "UEscapeGame.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	Controller = GetWorld()->GetFirstPlayerController();
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/// Get Player Viewport
	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	/// Log out to test
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation:, %s"), *ViewLocation.ToString(), *ViewRotation.ToString());

	/// Draw a red trace in the world
	FVector LineTraceEnd = ViewLocation + ViewRotation.Vector() * GrabDistance;
	DrawDebugLine(
		GetWorld(),
		ViewLocation,
		LineTraceEnd,
		FColor(255, 0, 0, 1),
		false,
		0,
		0,
		LineThickness
	);

}


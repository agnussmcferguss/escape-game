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
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	Controller = GetWorld()->GetFirstPlayerController();

	FindPhysicsHandleComponent();
	FindInputComponent();
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached
	if (PhysicsHandle->GrabbedComponent) {
		/// Get Player Viewport
		FVector ViewLocation;
		FRotator ViewRotation;
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

		/// Setup Query Parameters
		FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
		FVector LineTraceEnd = ViewLocation + ViewRotation.Vector() * Reach;

		// Move the object being held
		PhysicsHandle->SetTargetLocation(LineTraceEnd);

	}
		

}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() 
{
	/// Get Player Viewport
	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	/// Setup Query Parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FVector LineTraceEnd = ViewLocation + ViewRotation.Vector() * Reach;
	/// Do a line trace
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		ViewLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return Hit;
}


void UGrabber::Grab()
{
	//UE_LOG(LogTemp, Warning, TEXT("Grab Button Pressed"));

	// Line Trace and Try and reach any actors with physics body
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	AActor* HitActor = HitResult.GetActor();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	if (HitActor) {
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitActor->GetName());

		// TODO: If we hit anything, attach physics handle
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
		);
	}

}


void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"));

	// TODO: Release Physics handle
	PhysicsHandle->ReleaseComponent();
}


void UGrabber::FindInputComponent()
{
	// Find the Input Component (Only appears at runtime)
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!(InputComponent)) {
		UE_LOG(LogTemp, Error, TEXT("%s: Missing InputComponent"), *GetOwner()->GetName());
	} else {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::FindPhysicsHandleComponent()
{
	// Find the Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!(PhysicsHandle)) {
		UE_LOG(LogTemp, Error, TEXT("%s: Missing PhysicsHandle"), *GetOwner()->GetName());
	}
}
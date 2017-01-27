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
	BindInputComponent();
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached
	if (PhysicsHandle != nullptr && PhysicsHandle->GrabbedComponent != nullptr) {
		
		// Get the location we want to move the object to
		FVector LineTraceEnd = GetLineTraceEndPoint();

		// Move the object being held
		PhysicsHandle->SetTargetLocation(LineTraceEnd);

	} else if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s: missing PhysicsHandle"), *GetOwner()->GetName());
	}
		

}

void UGrabber::Grab()
{
	// Line Trace and Try and reach any actors with physics body
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	AActor* HitActor = HitResult.GetActor();

	// Attach Physics Handle
	if (HitActor != nullptr) {
			UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

			PhysicsHandle->GrabComponent(
				ComponentToGrab,
				NAME_None,  // No Bones to be grabbed
				ComponentToGrab->GetOwner()->GetActorLocation(),
				true
			);
	}
}


void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}



void UGrabber::BindInputComponent()
{
	// Find the Input Component (Only appears at runtime)
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	// If found, bind the grab action
	if (InputComponent != nullptr) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s: Missing InputComponent"), *GetOwner()->GetName());
	}
}


// Searches along the reach line to find the first available physics body
const FHitResult UGrabber::GetFirstPhysicsBodyInReach() 
{
	/// Setup Query Parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FVector ViewLocation = GetViewLocation();
	FVector LineTraceEnd = GetLineTraceEndPoint();

	/// Do a line trace
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		ViewLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return HitResult;
}



const FVector UGrabber::GetViewLocation() const
{
	FVector ViewLocation;
	FRotator ViewRotation;

	if (Controller != nullptr) {
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s: Missing PlayerController"), *GetOwner()->GetName());
	}
	
	return ViewLocation;
}



const FRotator UGrabber::GetViewRotation() const
{
	FVector ViewLocation;
	FRotator ViewRotation;

	if (Controller != nullptr) {
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s: Missing PlayerController"), *GetOwner()->GetName());
	}

	return ViewRotation;
}



const FVector UGrabber::GetLineTraceEndPoint() const
{
	/// Get Player Viewport
	FVector ViewLocation = GetViewLocation();
	FRotator ViewRotation = GetViewRotation();

	FVector LineTraceEnd = ViewLocation + ViewRotation.Vector() * Reach;
	return LineTraceEnd;
}



const FVector UGrabber::GetLineTraceEndPoint(const FVector & ViewLocation, const FRotator & ViewRotation) const
{
	FVector LineTraceEnd = ViewLocation + ViewRotation.Vector() * Reach;
	return LineTraceEnd;
}






void UGrabber::FindPhysicsHandleComponent()
{
	// Find the Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!(PhysicsHandle)) {
		UE_LOG(LogTemp, Error, TEXT("%s: Missing PhysicsHandle"), *GetOwner()->GetName());
	}
}
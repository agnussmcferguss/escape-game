// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UESCAPEGAME_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float Reach = 100.0;

	UPROPERTY(EditAnywhere)
	float LineThickness = 10.0;

	UPROPERTY(EditAnywhere)
	bool ShowDebugLine = false;

	APlayerController* Controller = nullptr;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	// Ray cast and grab physics object
	void Grab();

	// Release any grabbed physics object
	void Release();
	
	// Finds the attached InputComponent
	void BindInputComponent();

	// Finds the PhysicsHandle Component
	void FindPhysicsHandleComponent();

	// Finds the first PhysicsBody in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	const FVector GetViewLocation() const;

	const FRotator GetViewRotation() const;

	const FVector GetLineTraceEndPoint() const;

	const FVector GetLineTraceEndPoint(const FVector& ViewLocation, const FRotator& ViewRotation) const;
};

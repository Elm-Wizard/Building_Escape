// Copyright Nikola Aksentijevic 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Reach = 150.f;

	UPROPERTY()
	UPhysicsHandleComponent *PhysicsHandle = nullptr;
	UPROPERTY()
	UInputComponent *InputComponent = nullptr;

	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetupInputComponent();
	// Vraca prvog Actora u dometu
	FHitResult GetFirstPhysicsBodyInReach() const;
	// Vraca LineTraceEnd
	FVector GetPlayersReach() const;
	FVector GetPlayerWorldPosition() const;
};

// Copyright Nikola Aksentijevic 2020

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle -= InitialYaw;

	// if (!PressurePlate)
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("%s ima kompomentu OpenDoor, a nema podesen PressurePlate"), *GetOwner()->GetName());
	// }

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)) // Lazy Evaluation prvi uslov
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * DoorOpenSpeed); //FInterpConstantTo, FInterpTo, Lerp // DeltaTime mnozi da bi bilo nezavisno od razlicitog frejmrejta
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	// float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	// FRotator OpenDoor(0.f, OpenAngle, 0.f); // umesto OpenAngle moze i 0.f umesto, posto ga overridujemo na sl liniji
	// OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, 2); //FInterpConstantTo, FInterpTo, Lerp
	// GetOwner()->SetActorRotation(OpenDoor);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed); //FInterpConstantTo, FInterpTo, Lerp // DeltaTime mnozi da bi bilo nezavisno od razlicitog frejmrejta
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
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
	
	Owner = GetOwner();

	FConstPawnIterator PawnIterator = GetWorld()->GetPawnIterator();
	APawn* pPawn = GEngine->GetFirstLocalPlayerController(GetWorld())->GetPawnOrSpectator();
	pPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FString sName = AActor::GetDebugName(pPawn);
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Pawn is  %s ."), *sName);

	if (PawnIterator)
	{
		ActorThatOpen = *PawnIterator;
		
	}
	if (PawnIterator)
	{
		FString PName = AActor::GetDebugName(*PawnIterator);
		UE_LOG(LogTemp, Warning, TEXT("Pawn is at %s ."), *PName);
		PawnIterator++;
	}
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (PressurePlate->IsOverlappingActor(ActorThatOpen) && !Isopen)
	{
		LastDoorOpenTimes = GetWorld()->GetTimeSeconds();
		OpenDoor();
		//SetDoorRotation(FRotator(.0f, OpenAngle, .0f));
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTimes >= DoorCloseDelay && Isopen)
	{
		CloseDoor();
		//SetDoorRotation(FRotator(.0f, 0.0f, .0f));
	}
}

void UOpenDoor::SetDoorRotation( FRotator NewRotation )
{
	if (Owner == nullptr ) return;
	Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::OpenDoor()
{
	Isopen = true;
	OnOpenRequest.Broadcast();
}
void UOpenDoor::CloseDoor()
{
	OnCloseRequest.Broadcast();
	Isopen = false;
}
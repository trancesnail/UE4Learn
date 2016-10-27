// Fill out your copyright notice in the Description page of Project Settings.

#include "Bored.h"
#include "BoredSpectatorPawn.h"
#include "BoredCameraComponent.h"
#include "BoredSpectatorPawnMovement.h"


ABoredSpectatorPawn::ABoredSpectatorPawn(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	GetCollisionComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	bAddDefaultMovementBindings = false;
	BoredCameraComponent = CreateDefaultSubobject<UBoredCameraComponent>(TEXT("BoredCameraComponent"));
}

void ABoredSpectatorPawn::MoveForward(float Val)
{
	BoredCameraComponent->MoveForward(Val);
}

/** event call on strafe right input */
void ABoredSpectatorPawn::MoveRight(float Val)
{
	BoredCameraComponent->MoveRight(Val);
}

/** Add custom key bindings */
void ABoredSpectatorPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

	//InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ABoredSpectatorPawn::OnMouseScrollUp);
	//InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ABoredSpectatorPawn::OnMouseScrollDown);

	InputComponent->BindAxis("MoveForward", this, &ABoredSpectatorPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABoredSpectatorPawn::MoveRight);
}

UBoredCameraComponent* ABoredSpectatorPawn::GetBoredCameraComponent()
{
	check(BoredCameraComponent != NULL);
	return BoredCameraComponent;
}
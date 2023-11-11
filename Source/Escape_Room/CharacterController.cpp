// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterController.h"

// Sets default values
ACharacterController::ACharacterController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->AirControl = 0.2f;

	SetCameraBoom();
	SetFollowCamera();
}

void ACharacterController::SetCameraBoom()
{
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 300.f;
	cameraBoom->bUsePawnControlRotation = true;
}

void ACharacterController::SetFollowCamera()
{
	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
	followCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterController::MoveForward(float value)
{
	FRotator rotation = Controller->GetControlRotation();
	FRotator yawRotation(0.f, rotation.Yaw, 0.f);
	FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(direction, value);
}

void ACharacterController::MoveRight(float value)
{
	FRotator rotation = Controller->GetControlRotation();
	FRotator yawRotation(0.f, rotation.Yaw, 0.f);

	FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(direction, value);
}

void ACharacterController::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ACharacterController::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}


// Called every frame
void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterController::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterController::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterController::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacterController::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacterController::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterController::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacterController::StopJumping);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACharacterController::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACharacterController::StopSprint);
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "FightingGame_2DCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AFightingGame_2DCharacter::AFightingGame_2DCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
    
    // Default values for health and stamina
    currentHealth = maxHealth = 100.0f;
    currentStamina = maxStamina = 100.0f;
    
    wasLightAttackUsed = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFightingGame_2DCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFightingGame_2DCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AFightingGame_2DCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AFightingGame_2DCharacter::TouchStopped);
    
    PlayerInputComponent->BindAction("AttackLight", IE_Pressed, this, &AFightingGame_2DCharacter::StartAttackLight);
    PlayerInputComponent->BindAction("AttackMedium", IE_Pressed, this, &AFightingGame_2DCharacter::StartAttackMedium);
    PlayerInputComponent->BindAction("AttackHeavy", IE_Pressed, this, &AFightingGame_2DCharacter::StartAttackHeavy);
}

void AFightingGame_2DCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AFightingGame_2DCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AFightingGame_2DCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AFightingGame_2DCharacter::StartAttackLight()
{
    UE_LOG(LogTemp, Warning, TEXT("Starting light attack"));
    wasLightAttackUsed = true;
}

void AFightingGame_2DCharacter::StartAttackMedium()
{
    UE_LOG(LogTemp, Warning, TEXT("Starting medium attack"));
}

void AFightingGame_2DCharacter::StartAttackHeavy()
{
    UE_LOG(LogTemp, Warning, TEXT("Starting heavy attack"));
    
    // Damage test
    DamageFighter(5.0f);
}

void AFightingGame_2DCharacter::DamageFighter(float damageValue)
{
    UE_LOG(LogTemp, Warning, TEXT("Dealing   %f damage"), damageValue);
    
    currentHealth -= damageValue;
    
    if(currentHealth <= 0.0f)
    {
        currentHealth = 0.0f;
    }
}

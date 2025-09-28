#include "Characters/CustomCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

class UEnhancedInputLocalPlayerSubsystem;

ACustomCharacter::ACustomCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACustomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACustomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACustomCharacter::Move);
		enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACustomCharacter::Look);
	}
}

void ACustomCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			subSystem->AddMappingContext(InputMappingContext, 0); 
		}
	}
	
}

void ACustomCharacter::Move(const FInputActionValue& value)
{
	const FVector2d movementVector = value.Get<FVector2d>();
	if (Controller)
	{
		FVector right = GetActorRightVector();
		AddMovementInput(right, movementVector.X);
		FVector forward = GetActorForwardVector();
		AddMovementInput(forward, movementVector.Y);
	}
}

void ACustomCharacter::Look(const FInputActionValue& value)
{
	const FVector2d lookAxisValue = value.Get<FVector2d>();
	if (Controller)
	{
		AddControllerYawInput(lookAxisValue.X);
		AddControllerPitchInput(lookAxisValue.Y);
	}
}


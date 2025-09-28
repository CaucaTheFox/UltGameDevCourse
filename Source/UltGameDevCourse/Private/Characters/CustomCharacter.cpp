#include "Characters/CustomCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

class UEnhancedInputLocalPlayerSubsystem;

ACustomCharacter::ACustomCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(GetRootComponent());

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(cameraBoom);
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


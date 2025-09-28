#include "Characters/CustomCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

class UEnhancedInputLocalPlayerSubsystem;

ACustomCharacter::ACustomCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	UCharacterMovementComponent* movementComponent = GetCharacterMovement();
	movementComponent->bOrientRotationToMovement = true;
	movementComponent->RotationRate = FRotator(0.f, 360.f, 0.f);

	USkeletalMeshComponent* meshComponent = GetMesh();
	hairMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairMesh"));
	hairMesh->SetupAttachment(meshComponent);
	faceMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FaceMesh"));
	faceMesh->SetupAttachment(meshComponent);
	upperBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UpperBodyMesh"));
	upperBodyMesh->SetupAttachment(meshComponent);
	lowerBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LowerBodyMesh"));
	lowerBodyMesh->SetupAttachment(meshComponent);
	shoesMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShoesMesh"));
	shoesMesh->SetupAttachment(meshComponent);
	
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
		const FRotator controlRotation = GetControlRotation();
		const FRotator yawRotation(0.f, controlRotation.Yaw, 0.f);
		const FVector3d controllerRight = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y); 
		AddMovementInput(controllerRight, movementVector.X);
		const FVector3d controllerForward = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(controllerForward, movementVector.Y);
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


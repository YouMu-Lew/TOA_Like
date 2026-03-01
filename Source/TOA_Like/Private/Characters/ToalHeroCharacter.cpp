#include "Characters/ToalHeroCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/ToalDataAsset_InputConfig.h"
#include "Components/ToalInputComponent.h"
#include "ToalGameplayTags.h"
#include "Engine/LocalPlayer.h"

namespace ToalHero {
    static const float LookYawRate   = 300.0f;
    static const float LookPitchRate = 165.0f;
}; // namespace ToalHero

AToalHeroCharacter::AToalHeroCharacter()
{
    // 设置角色胶囊体碰撞组件的尺寸大小
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

    // 禁用控制器对角色旋转的控制，让角色能够独立于控制器进行旋转
    bUseControllerRotationRoll  = false; // Roll 滚转（绕X轴旋转）
    bUseControllerRotationPitch = false; // Pitch 俯仰（绕Y轴旋转）
    bUseControllerRotationYaw   = false; // Yaw 偏航（绕Z轴旋转）

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(GetRootComponent());
    CameraBoom->TargetArmLength         = 300.f;
    CameraBoom->SocketOffset            = FVector(0.f, 55.f, 65.f);
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    UCharacterMovementComponent* MoveComp = GetCharacterMovement();
    MoveComp->bOrientRotationToMovement   = true;                      // 角色朝向移动方向旋转
    MoveComp->RotationRate                = FRotator(0.f, 500.f, 0.f); // 旋转速率
    MoveComp->MaxWalkSpeed                = 400.f;                     // 设置角色的最大行走速度
    MoveComp->BrakingDecelerationWalking  = 2000.f;                    // 设置角色的行走制动减速度
}

void AToalHeroCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AToalHeroCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
}

void AToalHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config."));

    check(PlayerInputComponent);

    const APlayerController* PC = GetController<APlayerController>();
    check(PC);

    const ULocalPlayer* LP = PC->GetLocalPlayer();
    check(LP);

    UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    check(Subsystem);

    Subsystem->AddMappingContext(InputConfigDataAsset.Get()->DefaultMappingContext, 0);

    UToalInputComponent* ToalIC = Cast<UToalInputComponent>(PlayerInputComponent);
    checkf(ToalIC, TEXT("Cannot cast `PlayerInputComponent` to `UToalInputComponent`."));

    ToalIC->BindNativeAction(InputConfigDataAsset, ToalGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
    ToalIC->BindNativeAction(InputConfigDataAsset, ToalGameplayTags::InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Input_LookMouse);
    ToalIC->BindNativeAction(InputConfigDataAsset, ToalGameplayTags::InputTag_Look_Stick, ETriggerEvent::Triggered, this, &ThisClass::Input_LookStick);
}

void AToalHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
    if (Controller)
    {
        const FVector2D Value = InputActionValue.Get<FVector2D>();
        const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

        if (Value.X != 0.0f)
        {
            const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
            AddMovementInput(MovementDirection, Value.X);
        }

        if (Value.Y != 0.0f)
        {
            const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
            AddMovementInput(MovementDirection, Value.Y);
        }
    }
}

void AToalHeroCharacter::Input_LookMouse(const FInputActionValue& InputActionValue)
{
    const FVector2D Value = InputActionValue.Get<FVector2D>();

    if (Value.X != 0.0f)
    {
        AddControllerYawInput(Value.X);
    }

    if (Value.Y != 0.0f)
    {
        AddControllerPitchInput(Value.Y);
    }
}

void AToalHeroCharacter::Input_LookStick(const FInputActionValue& InputActionValue)
{
    const FVector2D Value = InputActionValue.Get<FVector2D>();

    const UWorld* World = GetWorld();
    check(World);

    if (Value.X != 0.0f)
    {
        AddControllerYawInput(Value.X * ToalHero::LookYawRate * World->GetDeltaSeconds());
    }

    if (Value.Y != 0.0f)
    {
        AddControllerPitchInput(Value.Y * ToalHero::LookPitchRate * World->GetDeltaSeconds());
    }
}

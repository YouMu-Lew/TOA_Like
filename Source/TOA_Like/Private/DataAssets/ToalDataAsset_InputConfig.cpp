#include "DataAssets/ToalDataAsset_InputConfig.h"

const UInputAction* UToalDataAsset_InputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag,
                                                                            bool bLogNotFound) const
{
    for (const FToalInputAction& Action : NativeInputActions)
    {
        if (Action.InputAction && (Action.InputTag == InputTag))
        {
            return Action.InputAction;
        }
    }

    if (bLogNotFound)
    {
        UE_LOG(LogTemp, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."),
               *InputTag.ToString(), *GetNameSafe(this));
    }

    return nullptr;
}

const UInputAction* UToalDataAsset_InputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
                                                                             bool bLogNotFound) const
{
    return nullptr;
}

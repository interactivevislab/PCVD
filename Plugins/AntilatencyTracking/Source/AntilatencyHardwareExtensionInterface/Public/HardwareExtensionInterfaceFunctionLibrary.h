// Copyright 2020, ALT LLC. All Rights Reserved.
// This file is part of Antilatency SDK.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://www.antilatency.com/eula
// You may not use this file except in compliance with the License.
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/** @addtogroup hardwareExtensionInterfaceModule
 *  @{
 */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "HardwareExtensionInterfaceLibrary.h"
#include "HardwareExtensionInterfaceCotask.h"

#include "HardwareExtensionInterfaceFunctionLibrary.generated.h"

/** An additional enum that is used by the blueprint methods to allow user to check if called method has been executed successfully or not. */
UENUM(BlueprintType)
enum class EHardwareExtensionInterfaceExceptionResult : uint8 {
    /** The method executed successfully. */
    Success = 1 UMETA(DisplayName = "Success"),
    /** The method execution failed with some exception. */
    Fail = 0 UMETA(DisplayName = "Fail"),
};

/**
 * Provides Hardware Extension Interface module's methods wrappers for the UE blueprint system.
 */
UCLASS()
class ANTILATENCYHARDWAREEXTENSIONINTERFACE_API UHardwareExtensionInterfaceFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    /**
     * Get the Hardware Extension Interface library object.
     * @param result The Hardware Extension Interface library object.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void GetHardwareExtensionInterfaceLibrary(UHardwareExtensionInterfaceLibrary*& result, EHardwareExtensionInterfaceExceptionResult &exception);

    /**
     * Create the Hardware Extension Interface task on the node.
     * @param library A pointer to the UHardwareExtensionInterfaceLibrary object.
     * @param network A pointer to the UDeviceNetwork object.
     * @param node A node to start the radio metrics task on.
     * @param result A result pointer to the Hardware Extension Interface cotask object.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
    static void StartHardwareExtensionInterfaceTask(const UHardwareExtensionInterfaceLibrary* library, const UDeviceNetwork *network, const FAdnNode &node, UHardwareExtensionInterfaceCotask *&result, EHardwareExtensionInterfaceExceptionResult &exception);

    /**
     * Is a node supports the Hardware Extension Interface task or not.
     * @param library A pointer to the UHardwareExtensionInterfaceLibrary object.
     * @param network A pointer to the UDeviceNetwork object.
     * @param node A node to check the Hardware Extension Interface task support.
     * @param result Is node supports Hardware Extension Interface task or not.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void IsSupported(const UHardwareExtensionInterfaceLibrary* library, const UDeviceNetwork *network, const FAdnNode &node, bool &result, EHardwareExtensionInterfaceExceptionResult &exception);

    /**
     * Get all currently connected nodes that supports Hardware Extension Interface task.
     * @param library A pointer to the UHardwareExtensionInterfaceLibrary object.
     * @param network A pointer to the UDeviceNetwork object.
     * @param result An result array of nodes that support the Hardware Extension Interface task.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void FindSupportedNodes(const UHardwareExtensionInterfaceLibrary* library, const UDeviceNetwork *network, TArray<FAdnNode> &result, EHardwareExtensionInterfaceExceptionResult &exception);

    /**
     * Check if UHardwareExtensionInterfaceLibrary has been initialized properly (the UHardwareExtensionInterfaceLibrary is not nullptr and the native Antilatency::HardwareExtensionInterface::ILibrary is not nullptr).
     * @param library A pointer to the UHardwareExtensionInterfaceLibrary object.
     * @return True if object is initialized properly, otherwise false.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|Hardware Extension Interface|Library")
    static bool IsLibraryValid(const UHardwareExtensionInterfaceLibrary* library);

    /**
     * Check if Hardware Extension Interface task is finished.
     * @param cotask A pointer to the UHardwareExtensionInterfaceCotask object.
     * @param result True if task finished, otherwise false.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
    static void IsTaskFinished(const UHardwareExtensionInterfaceCotask* cotask, bool& result, EHardwareExtensionInterfaceExceptionResult& exception);

    /**
     * Stop Hardware Extension Interface task. Remember to free the target UHardwareExtensionInterfaceCotask object after calling this method because it will be not useful at all after that moment.
     * The node which is used by that task will become free (FNodeStatus::Idle) after calling this method, so you can run another task on it.
     * IMPORTANT: there is no guarantee that this node changes status immediately after calling this method, this may take some time.
     * @param cotask A pointer to the UHardwareExtensionInterfaceCotask object.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Cotask")
    static void Stop(UPARAM(ref) UHardwareExtensionInterfaceCotask* cotask);

    /**
     * Check if the cotask wrapper initialized properly.
     * @param cotask A pointer to the UHardwareExtensionInterfaceCotask object.
     * @return True if the cotask wrapper initialized properly, otherwise false.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|Hardware Extension Interface|Cotask")
    static bool IsHardwareExtensionInterfaceTaskValid(const UHardwareExtensionInterfaceCotask* cotask);



	UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
	static void CreateInputPin(const UHardwareExtensionInterfaceCotask* cotask, const EPins& pin, UInputPin*& result, EHardwareExtensionInterfaceExceptionResult& exception);

	UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
	static void CreateOutputPin(const UHardwareExtensionInterfaceCotask* cotask, const EPins& pin, const EPinState& initialState, UOutputPin*& result, EHardwareExtensionInterfaceExceptionResult& exception);

	UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
	static void CreateAnalogPin(const UHardwareExtensionInterfaceCotask* cotask, const EPins& pin, const uint8 refreshIntervalMs, UAnalogPin*& result, EHardwareExtensionInterfaceExceptionResult& exception);

	UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
	static void CreatePulseCounterPin(const UHardwareExtensionInterfaceCotask* cotask, const EPins& pin, const uint8 refreshIntervalMs, UPulseCounterPin*& result, EHardwareExtensionInterfaceExceptionResult& exception);

	UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
	static void Run(const UHardwareExtensionInterfaceCotask* cotask, EHardwareExtensionInterfaceExceptionResult& exception);

	
	
	UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Input Pin", Meta = (ExpandEnumAsExecs = "exception"))
	static void GetInputPinState(const UInputPin* pin, EPinState& result, EHardwareExtensionInterfaceExceptionResult& exception);

	UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Input Pin")
	static bool IsInputPinValid(const UInputPin* pin);



	UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Output Pin", Meta = (ExpandEnumAsExecs = "exception"))
	static void GetOutputPinState(const UOutputPin* pin, EPinState& result, EHardwareExtensionInterfaceExceptionResult& exception);

	UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Output Pin", Meta = (ExpandEnumAsExecs = "exception"))
	static void SetOutputPinState(const UOutputPin* pin, const EPinState& state, EHardwareExtensionInterfaceExceptionResult& exception);

	UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Output Pin")
	static bool IsOutputPinValid(const UOutputPin* pin);



	UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Analog Pin", Meta = (ExpandEnumAsExecs = "exception"))
	static void GetAnalogPinValue(const UAnalogPin* pin, float& result, EHardwareExtensionInterfaceExceptionResult& exception);

	UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Analog Pin")
	static bool IsAnalogPinValid(const UAnalogPin* pin);



	UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Pulse Counter Pin", Meta = (ExpandEnumAsExecs = "exception"))
	static void GetPulseCounterPinValue(const UPulseCounterPin* pin, uint8& result, EHardwareExtensionInterfaceExceptionResult& exception);

	UFUNCTION(BlueprintCallable, Category = "Antilatency|Hardware Extension Interface|Pulse Counter Pin")
	static bool IsPulseCounterPinValid(const UPulseCounterPin* pin);
};

/** @} */
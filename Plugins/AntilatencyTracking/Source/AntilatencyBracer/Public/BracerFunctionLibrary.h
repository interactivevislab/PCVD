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

/** @addtogroup bracerModule
 *  @{
 */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "BracerLibrary.h"
#include "BracerCotask.h"
#include "BracerTypes.h"

#include "BracerFunctionLibrary.generated.h"

/** An additional enum that is used by the blueprint methods to allow user to check if called method has been executed successfully or not. */
UENUM(BlueprintType)
enum class EBracerExceptionResult : uint8 {
    /** The method executed successfully. */
    Success = 1 UMETA(DisplayName = "Success"),
    /** The method execution failed with some exception. */
    Fail = 0 UMETA(DisplayName = "Fail"),
};

/**
 * Provides Bracer module's methods wrappers for the UE blueprint system.
 */
UCLASS()
class ANTILATENCYBRACER_API UBracerFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    /**
     * Get the native bracer library object.
     * @param result The native bracer library object.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Bracer|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void GetBracerLibrary(UBracerLibrary *&result, EBracerExceptionResult &exception);

    /**
     * Create the bracer task on the node.
     * @param bracerLibrary A pointer to the UBracerLibrary object.
     * @param network A pointer to the UDeviceNetwork object.
     * @param node A node to start the bracer task on.
     * @param result A result pointer to the bracer cotask.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Bracer|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
    static void StartBracerTask(const UBracerLibrary *bracerLibrary, const UDeviceNetwork *network, const FAdnNode &node, UBracerCotask *&result, EBracerExceptionResult &exception);

    /**
     * Is a node supports the bracer task or not.
     * @param bracerLibrary A pointer to the UBracerLibrary object.
     * @param network A pointer to the UDeviceNetwork object.
     * @param node A node to check the bracer task support.
     * @param result Is node supports bracer task or not.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Bracer|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void IsSupported(const UBracerLibrary *bracerLibrary, const UDeviceNetwork *network, const FAdnNode &node, bool &result, EBracerExceptionResult &exception);

    /**
     * Get all currently connected nodes that supports bracer task.
     * @param bracerLibrary A pointer to the UBracerLibrary object.
     * @param network A pointer to the UDeviceNetwork object.
     * @param result An result array of nodes that support the bracer task.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Bracer|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void FindSupportedNodes(const UBracerLibrary *bracerLibrary, const UDeviceNetwork *network, TArray<FAdnNode> &result, EBracerExceptionResult &exception);

    /**
     * Check if UBracerLibrary has been initialized properly (the UBracerLibrary is not nullptr and the native Antilatency::Bracer::ILibrary is not nullptr).
     * @param bracerLibrary A pointer to the UBracerLibrary object.
     * @return True if object is initialized properly, otherwise false.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|Bracer|Library")
    static bool IsLibraryValid(const UBracerLibrary *bracerLibrary);


	/**
	 * Get battery level.
	 * @param bracerCotask A pointer to the UBracerCotask object.
	 * @param result The current battery level.
	 * @param exception Method execution result.
	 */
	static void GetBatteryLevel(const UBracerCotask* bracerCotask, float& result, EBracerExceptionResult& exception);

	/**
	 * Get touch channels count.
	 * @param bracerCotask A pointer to the UBracerCotask object.
	 * @param result Braceer's touch channels count.
	 * @param exception Method execution result.
	 */
	static void GetTouchChannelsCount(const UBracerCotask* bracerCotask, int32& result, EBracerExceptionResult& exception);

	/**
	 * Get the raw touchpad trigger value.
	 * @param bracerCotask A pointer to the UBracerCotask object.
	 * @param channel Bracer channel.
	 * @param result The current touchpad value.
	 * @param exception Method execution result.
	 */
	UFUNCTION(BlueprintCallable, Category = "Antilatency|Bracer|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
	static void GetTouchNativeValue(const UBracerCotask* bracerCotask, const int32 channel, int32& result, EBracerExceptionResult& exception);


    /**
     * Get the current touchpad value.
     * @param bracerCotask A pointer to the UBracerCotask object.
	 * @param channel Bracer channel.
     * @param result The current touchpad value.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Bracer|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
    static void GetTouch(const UBracerCotask* bracerCotask, const int32 channel, float& result, EBracerExceptionResult& exception);

    /**
     * Execute vibration on the device.
     * @param bracerCotask A pointer to the UBracerCotask object.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Bracer|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
    static void ExecuteVibrationSequence(const UBracerCotask* bracerCotask, const TArray<FVibration>& vibrationSequence, EBracerExceptionResult& exception);

    /**
     * Check if bracer task is finished.
     * @param bracerCotask A pointer to the UBracerCotask object.
     * @param result True if task finished, otherwise false.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Bracer|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
    static void IsTaskFinished(const UBracerCotask* bracerCotask, bool& result, EBracerExceptionResult& exception);

    /**
     * Stop bracer task. Remember to free the target UBracerCotask object after calling this method because it will be not useful at all after that moment.
     * The node which is used by that task will become free (FNodeStatus::Idle) after calling this method, so you can run another task on it.
     * IMPORTANT: there is no guarantee that this node changes status immediately after calling this method, this may take some time.
     * @param bracerCotask A pointer to the bracer cotask object.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Bracer|Cotask")
    static void Stop(UPARAM(ref) UBracerCotask* bracerCotask);

    /**
     * Check if the cotask wrapper initialized properly.
     * @param bracerCotask A pointer to the UBracerCotask object.
     * @return True if the cotask wrapper initialized properly, otherwise false.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|Bracer|Cotask")
    static bool IsBracerTaskValid(const UBracerCotask* bracerCotask);
};

/** @} */
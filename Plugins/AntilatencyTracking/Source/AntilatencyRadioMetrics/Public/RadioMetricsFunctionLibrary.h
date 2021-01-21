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

/** @addtogroup radioMetricsModule
 *  @{
 */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "RadioMetricsLibrary.h"
#include "RadioMetricsCotask.h"

#include "RadioMetricsFunctionLibrary.generated.h"

/** An additional enum that is used by the blueprint methods to allow user to check if called method has been executed successfully or not. */
UENUM(BlueprintType)
enum class ERadioMetricsExceptionResult : uint8 {
    /** The method executed successfully. */
    Success = 1 UMETA(DisplayName = "Success"),
    /** The method execution failed with some exception. */
    Fail = 0 UMETA(DisplayName = "Fail"),
};

/**
 * Provides Radio Metrics module's methods wrappers for the UE blueprint system.
 */
UCLASS()
class ANTILATENCYRADIOMETRICS_API URadioMetricsFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    /**
     * Get the native radio metrics library object.
     * @param result The native radio metrics library object.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Radio Metrics|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void GetRadioMetricsLibrary(URadioMetricsLibrary *&result, ERadioMetricsExceptionResult &exception);

    /**
     * Create the radio metrics task on the node.
     * @param radioMetricsLibrary A pointer to the URadioMetricsLibrary object.
     * @param network A pointer to the UDeviceNetwork object.
     * @param node A node to start the radio metrics task on.
     * @param result A result pointer to the radio metrics cotask.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Radio Metrics|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
    static void StartRadioMetricsTask(const URadioMetricsLibrary *radioMetricsLibrary, const UDeviceNetwork *network, const FAdnNode &node, URadioMetricsCotask *&result, ERadioMetricsExceptionResult &exception);

    /**
     * Is a node supports the radio metrics task or not.
     * @param radioMetricsLibrary A pointer to the URadioMetricsLibrary object.
     * @param network A pointer to the UDeviceNetwork object.
     * @param node A node to check the radio metrics task support.
     * @param result Is node supports radio metrics task or not.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Radio Metrics|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void IsSupported(const URadioMetricsLibrary *radioMetricsLibrary, const UDeviceNetwork *network, const FAdnNode &node, bool &result, ERadioMetricsExceptionResult &exception);

    /**
     * Get all currently connected nodes that supports radio metrics task.
     * @param radioMetricsLibrary A pointer to the URadioMetricsLibrary object.
     * @param network A pointer to the UDeviceNetwork object.
     * @param result An result array of nodes that support the radio metrics task.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Radio Metrics|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void FindSupportedNodes(const URadioMetricsLibrary *radioMetricsLibrary, const UDeviceNetwork *network, TArray<FAdnNode> &result, ERadioMetricsExceptionResult &exception);

    /**
     * Check if URadioMetricsLibrary has been initialized properly (the URadioMetricsLibrary is not nullptr and the native Antilatency::RadioMetrics::ILibrary is not nullptr).
     * @param radioMetricsLibrary A pointer to the URadioMetricsLibrary object.
     * @return True if object is initialized properly, otherwise false.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|Radio Metrics|Library")
    static bool IsLibraryValid(const URadioMetricsLibrary *radioMetricsLibrary);

    /**
     * Check if radio metrics task is finished.
     * @param radioMetricsCotask A pointer to the URadioMetricsCotask object.
     * @param result True if task finished, otherwise false.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Radio Metrics|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
    static void IsTaskFinished(const URadioMetricsCotask* radioMetricsCotask, bool& result, ERadioMetricsExceptionResult& exception);

    /**
     * Stop radio metrics task. Remember to free the target URadioMetricsCotask object after calling this method because it will be not useful at all after that moment.
     * The node which is used by that task will become free (FNodeStatus::Idle) after calling this method, so you can run another task on it.
     * IMPORTANT: there is no guarantee that this node changes status immediately after calling this method, this may take some time.
     * @param radioMetricsCotask A pointer to the URadioMetricsCotask object.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Radio Metrics|Cotask")
    static void Stop(UPARAM(ref) URadioMetricsCotask* radioMetricsCotask);

    /**
     * Check if the cotask wrapper initialized properly.
     * @param radioMetricsCotask A pointer to the URadioMetricsCotask object.
     * @return True if the cotask wrapper initialized properly, otherwise false.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|Radio Metrics|Cotask")
    static bool IsRadioMetricsTaskValid(const URadioMetricsCotask* radioMetricsCotask);

	/**
	 * Get simplified metrics.
	 * @param radioMetricsCotask A pointer to the URadioMetricsCotask object.
	 * @param targetNode A slave radio node to get metrics.
	 * @param result Resulting simplified metrics.
	 * @param exception Method execution result.
	 */
	UFUNCTION(BlueprintCallable, Category = "Antilatency|Radio Metrics|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
	static void GetMetrics(const URadioMetricsCotask* radioMetricsCotask, const FAdnNode& targetNode, FRadioMetrics& result, ERadioMetricsExceptionResult& exception);

	/**
	 * Get extended metrics.
	 * @param radioMetricsCotask A pointer to the URadioMetricsCotask object.
	 * @param targetNode A slave radio node to get metrics.
	 * @param result Resulting simplified metrics.
	 * @param exception Method execution result.
	 */
	UFUNCTION(BlueprintCallable, Category = "Antilatency|Radio Metrics|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
	static void GetExtendedMetrics(const URadioMetricsCotask* radioMetricsCotask, const FAdnNode& targetNode, FExtendedMetrics& result, ERadioMetricsExceptionResult& exception);
};

/** @} */
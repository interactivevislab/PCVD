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

/** @addtogroup altTrackingModule
 *  @{
 */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "AltTrackingLibrary.h"
#include "AltTrackingCotask.h"
#include "AltEnvironment.h"

#include "AltTrackingFunctionLibrary.generated.h"

/** An additional enum that is used by the blueprint methods to allow user to check if called method has been executed successfully or not. */
UENUM(BlueprintType)
enum class EAltTrackingExceptionResult : uint8 {
    /** The method executed successfully. */
    Success = 1 UMETA(DisplayName = "Success"),
    /** The method execution failed with some exception. */
    Fail = 0 UMETA(DisplayName = "Fail"),
};

/**
 * Provides Alt Tracking module's methods wrappers for the UE blueprint system.
 */
UCLASS()
class ANTILATENCYALTTRACKING_API UAltTrackingFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:

    /**
     * Get the native tracking library object.
     * @param result The native tracking library object.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void GetTrackingLibrary(UAltTrackingLibrary*& result, EAltTrackingExceptionResult& exception);

    /** 
     * Create a placement pose from the code.
     * @param altTrackingLibrary A pointer to the UAltTrackingLibrary object.
     * @param code Placement serialized value.
     * @param result Result placement pose.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void CreatePlacement(const UAltTrackingLibrary* altTrackingLibrary, const FString& code, FAltPose& result, EAltTrackingExceptionResult& exception);

    /** 
     * Create the tracking task on the node.
     * @param altTrackingLibrary A pointer to the UAltTrackingLibrary object.
     * @param network A pointer to the UDeviceNetwork object.
     * @param node A node to start the tracking task on.
     * @param environment A pointer to AAltEnvironment object.
     * @param result A result pointer to the tracking cotask.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
    static void CreateTracking(const UAltTrackingLibrary* altTrackingLibrary, const UDeviceNetwork* network, const FAdnNode& node, const UAltEnvironment* environment, UAltTrackingCotask*& result, EAltTrackingExceptionResult& exception);

    /**
     * Creates placement code from FAltPose.
     * @param altTrackingLibrary A pointer to the UAltTrackingLibrary object.
     * @param placement A source placement pose.
     * @param result The result placement code (pose serialized value).
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void EncodePlacement(const UAltTrackingLibrary* altTrackingLibrary, const FAltPose& placement, FString& result, EAltTrackingExceptionResult& exception);

    /**
     * Is a node supports the tracking task or not.
     * @param altTrackingLibrary A pointer to the UAltTrackingLibrary object.
     * @param network A pointer to the UDeviceNetwork object.
     * @param node A node to check the tracking task support.
     * @param result Is node supports tracking task or not.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void IsSupported(const UAltTrackingLibrary* altTrackingLibrary, const UDeviceNetwork* network, const FAdnNode& node, bool& result, EAltTrackingExceptionResult& exception);

    /**
     * Get all currently connected nodes that supports tracking task.
     * @param altTrackingLibrary A pointer to the UAltTrackingLibrary object.
     * @param network A pointer to the UDeviceNetwork object.
     * @param result An result array of nodes that support the tracking task.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void FindSupportedNodes(const UAltTrackingLibrary* altTrackingLibrary, const UDeviceNetwork* network, TArray<FAdnNode>& result, EAltTrackingExceptionResult& exception);

    /**
     * Check if UAltTrackingLibrary has been initialized properly (the UAltTrackingLibrary is not nullptr and the native Antilatency::Alt::Tracking::ILibrary is not nullptr).
     * @param altTrackingLibrary A pointer to the UAltTrackingLibrary object.
     * @return True if object is initialized properly, otherwise false.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|Alt Tracking|Library")
    static bool IsLibraryValid(const UAltTrackingLibrary* altTrackingLibrary);



    /**
     * Get raw tracking state without extrapolation and placement applied.
     * @param trackingCotask A pointer to the UAltTrackingCotask object.
     * @param result Result raw tracking state.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
    static void GetState(const UAltTrackingCotask* trackingCotask, FTrackingState& result, EAltTrackingExceptionResult& exception);

    /**
     * Get tracking state with placement and extrapolation corrections applied.
     * @param trackingCotask A pointer to the UAltTrackingCotask object.
     * @param placement A placement pose that will be used for the tracking pose correction.
     * @param deltaTime An tracking extrapolation time.
     * @param result Result tracking state.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
    static void GetExtrapolatedState(const UAltTrackingCotask* trackingCotask, const FAltPose& placement, const float deltaTime, FTrackingState& result, EAltTrackingExceptionResult& exception);

    /**
     * Check if the task is finished on node.
     * @param trackingCotask A pointer to the UAltTrackingCotask object.
     * @param result True if task finished, otherwise false.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Cotask", Meta = (ExpandEnumAsExecs = "exception"))
    static void IsTaskFinished(const UAltTrackingCotask* trackingCotask, bool& result, EAltTrackingExceptionResult& exception);

    /**
     * Stop tracking task. Remember to free the target UAltTrackingCotask object after calling this method because it will be not useful at all after that moment.
     * The node which is used by that task will become free (FNodeStatus::Idle) after calling this method, so you can run another task on it.
     * IMPORTANT: there is no guarantee that this node changes status immediately after calling this method, this may take some time.
     * @param trackingCotask A pointer to the UAltTrackingCotask object.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Cotask")
    static void Stop(UPARAM(ref) UAltTrackingCotask* trackingCotask);

    /** 
     * Check if the cotask wrapper initialized properly.
     * @param trackingCotask A pointer to the UAltTrackingCotask object.
     * @return True if the cotask wrapper initialized properly, otherwise false.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|Alt Tracking|Cotask")
    static bool IsTrackingTaskValid(const UAltTrackingCotask* trackingCotask);




    /**
     * Initialize the native Antilatency::Alt::Tracking::IEnvironment object using a environment from the Antilatency Service that is marked as default.
     * @param result A pointer to the created UAltEnvironment instance.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Environment", Meta = (ExpandEnumAsExecs = "exception"))
    static void CreateEnvironment(UAltEnvironment*& result, EAltTrackingExceptionResult& exception);

    /**
     * Initialize the native Antilatency::Alt::Tracking::IEnvironment object using the environment code.
     * @param code The environment code (serialized value).
     * @param result A pointer to the created UAltEnvironment instance.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Environment", Meta = (ExpandEnumAsExecs = "exception"))
    static void CreateEnvironmentUsingCode(const FString& code, UAltEnvironment*& result, EAltTrackingExceptionResult& exception);

    /**
     * Initialize the native Antilatency::Alt::Tracking::IEnvironment object using a environment from the Antilatency Service with provided name.
     * @param name The name of the environment.
     * @param result A pointer to the created UAltEnvironment instance.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Environment", Meta = (ExpandEnumAsExecs = "exception"))
    static void CreateEnvironmentUsingName(const FString& name, UAltEnvironment*& result, EAltTrackingExceptionResult& exception);

    /** 
     * Get environment's markers coordinates.
     * @param environment A pointer to the environment object.
     * @param result The result array of FVector coordinates that represents environment IR markers positions.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Environment", Meta = (ExpandEnumAsExecs = "exception"))
    static void GetMarkers(const UAltEnvironment* environment, TArray<FVector>& result, EAltTrackingExceptionResult& exception);

    /**
     * Is current environment is mutable (IR markers pattern is not constantly defined).
     * @param environment A pointer to the environment object.
     * @param result True if environment is mutable, otherwise false.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Environment", Meta = (ExpandEnumAsExecs = "exception"))
    static void IsMutable(const UAltEnvironment* environment, bool& result, EAltTrackingExceptionResult& exception);

    /** 
     * Get mutable environment update id: every time when the tracking corrects markers positions, the environment update id will be incremented.
     * @param environment A pointer to the environment object.
     * @param result Current mutable environment update id.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Alt Tracking|Environment", Meta = (ExpandEnumAsExecs = "exception"))
    static void GetUpdateId(const UAltEnvironment* environment, int32& result, EAltTrackingExceptionResult& exception);

    /** 
     * Check if environment initialized properly.
     * @return true if environment initialized properly, otherwise false.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|Alt Tracking|Environment")
    static bool IsEnvironmentValid(const UAltEnvironment* environment);

};

/** @} */
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

/** @addtogroup altTrackingAlignmentModule
 *  @{
 */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "TrackingAlignmentLibrary.h"
#include "TrackingAlignment.h"
#include "TrackingAlignmentTypes.h"

#include "TrackingAlignmentFunctionLibrary.generated.h"

/** An additional enum that is used by the blueprint methods to allow user to check if called method has been executed successfully or not. */
UENUM(BlueprintType)
enum class ETrackingAlignmentExceptionResult : uint8 {
    /** The method executed successfully. */
    Success = 1 UMETA(DisplayName = "Success"),
    /** The method execution failed with some exception. */
    Fail = 0 UMETA(DisplayName = "Fail"),
};

/**
 * Provides Alt Tracking Alignment module's methods wrappers for the UE blueprint system.
 */
UCLASS()
class ANTILATENCYTRACKINGALIGNMENT_API UTrackingAlignmentFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:

    /**
     * Get the native tracking alignment library object.
     * @param result The native tracking alignment library object.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Tracking Alignment|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void GetTrackingAlignmentLibrary(UTrackingAlignmentLibrary*& result, ETrackingAlignmentExceptionResult& exception);

    /** 
     * Create the tracking alignment.
     * @param trackingAlignmentLibrary A pointer to the UTrackingAlignmentLibrary object.
     * @param result A result pointer to the tracking alignment.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Tracking Alignment|Alignment", Meta = (ExpandEnumAsExecs = "exception"))
    static void CreateTrackingAlignment(const UTrackingAlignmentLibrary* trackingAlignmentLibrary, const FQuat& initialARelativeToB, const float initialTimeBAheadOfA, UTrackingAlignment*& result, ETrackingAlignmentExceptionResult& exception);

    /**
     * Check if UTrackingAlignmentLibrary has been initialized properly (the UTrackingAlignmentLibrary is not nullptr and the native Antilatency::TrackingAlignment::ILibrary is not nullptr).
     * @param trackingAlignmentLibrary A pointer to the UTrackingAlignmentLibrary object.
     * @return True if object is initialized properly, otherwise false.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|Tracking Alignment|Library")
    static bool IsLibraryValid(const UTrackingAlignmentLibrary* trackingAlignmentLibrary);



    /**
     * @param a Alt rotation without extrapolation.
	 * @param b Third-party tracker's rotation as is.
	 * @param time Application's time since startup in seconds.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|Tracking Alignment", Meta = (ExpandEnumAsExecs = "exception"))
    static void Update(const UTrackingAlignment* trackingAlignment, const FQuat& a, const FQuat& b, const float time, FTrackingAlignmentState& result, ETrackingAlignmentExceptionResult& exception);


	/** 
     * Check if the Antilatency::Alt::TrackingAlignment::ITrackingAlignment wrapper initialized properly.
     * @param trackingCotask A pointer to the UAltTrackingCotask object.
     * @return True if the cotask wrapper initialized properly, otherwise false.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|Tracking Alignment")
    static bool IsTrackingAlignmentValid(const UTrackingAlignment* trackingAlignment);

};

/** @} */
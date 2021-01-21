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
#include "UObject/NoExportTypes.h"

#include "AltEnvironment.h"
#include "DeviceNetwork.h"
#include "DeviceNetworkTypes.h"
#include "AltTrackingCotask.h"
#include "AltTrackingTypes.h"

#include <Antilatency.Alt.Tracking.h>

#include "AltTrackingLibrary.generated.h"

/** 
 * Antilatency::Alt::Tracking::ILibrary wrapper for UE.
 * Do not instantiate this class directly by calling NewObject<UAltTrackingLibrary> method,
 * use UAltTrackingLibrary::GetLibrary instead.
 */
UCLASS(BlueprintType)
class ANTILATENCYALTTRACKING_API UAltTrackingLibrary : public UObject {
    GENERATED_BODY()

public:
    /** 
     * Get UAltTrackingLibrary instance.
     * @return The UAltTrackingLibrary wrapper object. If native Antilatency::Alt::Tracking::ILibrary creation fails, returns nullptr.
     */
    static UAltTrackingLibrary* GetLibrary();

    /** 
     * Create native Antilatency::Alt::Tracking::IEnvironment object.
     * @param code An environment serialized value.
     * @param result Result Antilatency::Alt::Tracking::IEnvironment object. If the code is incorrect, result will be equal nullptr.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode CreateNativeEnvironment(const FString& code, Antilatency::Alt::Tracking::IEnvironment& result) const;

    /** 
     * Create placement from serialized value.
     * @param code Placement serialized value.
     * @param result Result FAltPose structure. If the code is incorrect, identity pose will be returned.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode CreatePlacement(const FString& code, FAltPose& result) const;

    /** 
     * Run tracking task on node.
     * @param network A pointer to the UDeviceNetwork object.
     * @param node A node to start the tracking task on.
     * @param environment A pointer to the AAltEnvironment object.
     * @param result The wrapper of the host-part of the tracking task.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode CreateTracking(const UDeviceNetwork* network, const FAdnNode& node, const UAltEnvironment* environment, UAltTrackingCotask*& result) const;

    /** 
     * Creates a placement serialized value from the FAltPose. 
     * @param placement The placement to get serialized value from.
     * @param result Placement serialized value.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode EncodePlacement(const FAltPose& placement, FString& result) const;

    /** 
     * Check if the node supports the tracking task. 
     * @param network A pointer to the UDeviceNetwork object.
     * @param node A node to check the tracking task support.
     * @param result Is node supports tracking task or not.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode IsSupported(const UDeviceNetwork* network, const FAdnNode& node, bool& result) const;

    /** 
     * Get a list of the currently connected nodes that support the tracking task.
     * @param network A pointer to the UDeviceNetwork object.
     * @param result An result array of the nodes that support the tracking task.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode FindSupportedNodes(const UDeviceNetwork* network, TArray<FAdnNode>& result) const;

    /**
     * Check if UAltTrackingLibrary has been initialized properly (the UAltTrackingLibrary is not nullptr and the native Alt::Tracking::ILibrary is not nullptr).
     * @return True if object is initialized properly, otherwise false.
     */
    bool IsValid() const;

private:
    /** A pointer to the native tracking library object. */
    mutable Antilatency::Alt::Tracking::ILibrary _library;

    Antilatency::Alt::Tracking::ITrackingCotaskConstructor GetCotaskConstructor() const;

    void Init(Antilatency::Alt::Tracking::ILibrary& library);
};

/** @} */
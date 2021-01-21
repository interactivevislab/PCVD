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

#include <Antilatency.Alt.Tracking.h>

#include "AltTrackingTypes.h"

#include "AltTrackingCotask.generated.h"

/**
 * An UE wrapper for the host part of the alt tracking task (cotask). That task can be executed on the Alt tracker nodes to get tracking data.
 * Do not instantiate this class directly by calling the NewObject<UAltTrackingCotask> method,
 * use the UAltTrackingLibrary::CreateTracking or UAltTrackingCotask::CreateAltTrackingCotask instead.
 */
UCLASS(BlueprintType)
class ANTILATENCYALTTRACKING_API UAltTrackingCotask : public UObject {
    GENERATED_BODY()

public:

    /**
     * Create UAltTrackingCotask instance.
     * @param native The native Antilatency::Alt::Tracking::ICotask object.
     * @return The pointer to the created UAltTrackingCotask instance.
     */
    static UAltTrackingCotask* CreateAltTrackingCotask(const Antilatency::Alt::Tracking::ITrackingCotask& native);

    /**
     * Get raw tracking state without extrapolation and placement applied.
     * @param result Result raw tracking state.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode GetState(FTrackingState& result) const;

    /**
     * Get tracking state with placement and extrapolation corrections applied.
     * @param placement A placement pose that will be used for the tracking pose correction.
     * @param deltaTime An tracking extrapolation time.
     * @param result Result tracking state.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode GetExtrapolatedState(const FAltPose& placement, const float deltaTime, FTrackingState& result) const;

    /**
     * Check if the task is finished on node.
     * @param result True if task finished, otherwise false.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode IsTaskFinished(bool& result) const;

    /**
     * Stop tracking task. Remember to free the target UAltTrackingCotask object after calling this method because it will be not useful at all after that moment.
     * The node which is used by that task will become free (FNodeStatus::Idle) after calling this method, so you can run another task on it.
     * IMPORTANT: there is no guarantee that this node changes status immediately after calling this method, this may take some time.
     */
    void Stop();

    /**
     * Check if the cotask wrapper initialized properly.
     * @return True if the cotask wrapper initialized properly, otherwise false.
     */
    bool IsValid() const;

private:
    /** A pointer to the native tracking cotask object */
    mutable Antilatency::Alt::Tracking::ITrackingCotask _native;

    void Init(Antilatency::Alt::Tracking::ITrackingCotask native);
};

/** @} */
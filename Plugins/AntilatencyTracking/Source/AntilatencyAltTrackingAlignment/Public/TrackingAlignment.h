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

#include "TrackingAlignmentTypes.h"

#include <Antilatency.TrackingAlignment.h>

#include "TrackingAlignment.generated.h"

/**
 */
UCLASS(BlueprintType)
class ANTILATENCYTRACKINGALIGNMENT_API UTrackingAlignment : public UObject {
	GENERATED_BODY()

	virtual void BeginDestroy() override;

public:

    /**
     * Create UTrackingAlignment instance.
     * @param native The native Antilatency::Alt::TrackingAlignment::IAlignment object.
     * @return The pointer to the created UTrackingAlignment instance.
     */
    static UTrackingAlignment* CreateTrackingAlignment(const Antilatency::TrackingAlignment::ITrackingAlignment& native);

    /**
     * @param a Alt rotation without extrapolation.
	 * @param b Third-party tracker's rotation as is.
	 * @param time Application's time since startup in seconds.
	 * @param result Result Tracking Alignment state.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode Update(const FQuat& a, const FQuat& b, const float time, FTrackingAlignmentState& result) const;


    /**
     * Check if the cotask wrapper initialized properly.
     * @return True if the cotask wrapper initialized properly, otherwise false.
     */
    bool IsValid() const;

private:
    /** A pointer to the native tracking cotask object */
    mutable Antilatency::TrackingAlignment::ITrackingAlignment _native;

    void Init(Antilatency::TrackingAlignment::ITrackingAlignment native);
};

/** @} */
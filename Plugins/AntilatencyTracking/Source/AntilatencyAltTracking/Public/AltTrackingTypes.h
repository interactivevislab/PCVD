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

#include "AltTrackingLog.h"

#include <Antilatency.Alt.Tracking.h>
#include <Antilatency.Math.h>

#include "AltTrackingTypes.generated.h"

/** Describes the tracker position and rotation, also used as a placement representation. */
USTRUCT(BlueprintType, Category = "Antilatency|Alt Tracking|Alt Pose")
struct FAltPose {
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Antilatency|Alt Tracking|Alt Pose")
    FVector Position;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Antilatency|Alt Tracking|Alt Pose")
    FRotator Rotation;

    FAltPose() :
        Position(EForceInit::ForceInit),
        Rotation(EForceInit::ForceInit) {}

    FAltPose(const Antilatency::Math::floatP3Q native) {
        Position = FVector(native.position.z * 100.0f, native.position.x * 100.0f, native.position.y * 100.0f);
        Rotation = FRotator(FQuat(native.rotation.z, native.rotation.x, native.rotation.y, native.rotation.w));
    }

    FAltPose(const FVector& pos, const FQuat& rot) : Position(pos), Rotation(rot) {}

    Antilatency::Math::floatP3Q ToNative() const {
        Antilatency::Math::floatP3Q result;
        result.position = { Position.Y / 100.0f, Position.Z / 100.0f, Position.X / 100.0f };
        FQuat q(Rotation);
        result.rotation = { q.Y, q.Z, q.X, q.W };

		//ALTTRACKING_LOG(Log, TEXT("To native: {%f, %f, %f, %f}"), result.rotation.x, result.rotation.y, result.rotation.z, result.rotation.w);
        return result;
    }
};

/** Describes the current tracking stage. */
UENUM(BlueprintType, Category = "Antilatency|Alt Tracking|Tracking Stage")
enum class ETrackingStage : uint8 {
    /** Tracker collects the accelerometer data to find the upright orientation. No tracking data is valid in this stage. */
    InertialDataInitialization,
    /** Only the rotation part is valid in this stage. The rotation around the vertical axis may drifts. */
    Tracking3Dof,
    /** A full 6 DoF tracking, corrected by the optics. */
    Tracking6Dof,
    /** Inertial only 6 DoF tracking, without optical corrections. */
    TrackingBlind6Dof
};

/** Describes the current tracking stability. */
USTRUCT(BlueprintType, Category = "Antilatency|Alt Tracking|Tracking Stability")
struct FTrackingStability {
    GENERATED_BODY()

public:
    FTrackingStability() {
        Stage = ETrackingStage::InertialDataInitialization;
        Value = 0.0f;
    }

    FTrackingStability(const Antilatency::Alt::Tracking::Stability native) {
        Stage = static_cast<ETrackingStage>(native.stage);
        Value = native.value;
    }

    /** Current tracking stage. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Antilatency|Alt Tracking|Tracking Stability")
    ETrackingStage Stage;

    /**
     * Describes the current stability value.
     * If the tracking stage is InertialDataInitialization or Tracking3Dof, stability value will be always 0.
     * If the tracking stage is Tracking6Dof, this value represents how stable the solution is. Since this value depends on many factors, there is no units for it. This value may be used for debug purposes.
     * If the tracking stage is TrackingBlind6Dof, this value is a fraction of time left before switch to Tracking3Dof - it is useful to notify the user about the oncoming loss of tracking.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Antilatency|Alt Tracking|Tracking Stability")
    float Value;
};

/** Describes the current tracking state. */
USTRUCT(BlueprintType, Category = "Antilatency|Alt Tracking|Tracking State")
struct FTrackingState {
    GENERATED_BODY()

public:
    FTrackingState() {
        Pose = {};
        Velocity = {};
        LocalAngularVelocity = {};
        Stability = {};
    }

    FTrackingState(Antilatency::Alt::Tracking::State native) {
        Pose = FAltPose(native.pose);
        Velocity = {native.velocity.y, native.velocity.z, native.velocity.x};
        LocalAngularVelocity = { native.localAngularVelocity.y, native.localAngularVelocity.z, native.localAngularVelocity.x};
        Stability = FTrackingStability(native.stability);
    }

    /** Tracker position and rotation. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Antilatency|Alt Tracking|Tracking State")
    FAltPose Pose;

    /** Tracker velocity. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Antilatency|Alt Tracking|Tracking State")
    FVector Velocity;

    /** Tracker local angular velocity. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Antilatency|Alt Tracking|Tracking State")
    FVector LocalAngularVelocity;

    /** Current tracking stability. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Antilatency|Alt Tracking|Tracking State")
    FTrackingStability Stability;
};

/** @} */
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
#include "UObject/NoExportTypes.h"

#include "BracerTypes.h"

#include <Antilatency.Bracer.h>

#include "BracerCotask.generated.h"

/**
 * An UE wrapper for the host part of the bracer task (cotask). That task can be executed on the bracer nodes to get touchpad data and execute vibration on the device.
 * Do not instantiate this class directly by calling NewObject<UBracerCotask> method,
 * use UBracerLibrary::StartBracerTask or UBracerCotask::CreateBracerCotask instead.
 */
UCLASS(BlueprintType)
class ANTILATENCYBRACER_API UBracerCotask : public UObject {
    GENERATED_BODY()

public:

    /**
     * Create UBracerCotask instance.
     * @param native The native Antilatency::Bracer::ICotask object.
     * @return The pointer to the created UBracerCotask instance.
     */
    static UBracerCotask* CreateBracerCotask(const Antilatency::Bracer::ICotask& native);

	/**
	 *
	 */
	Antilatency::InterfaceContract::ExceptionCode GetBatteryLevel(float& result) const;

	/**
	 *
	 */
	Antilatency::InterfaceContract::ExceptionCode GetTouchChannelsCount(int32& result) const;

	/**
	 * 
	 */
	Antilatency::InterfaceContract::ExceptionCode GetTouchNativeValue(const int32 channel, int32& result) const;

    /**
     * Get the current touchpad value.
     * @param result The current touchpad value.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode GetTouch(const int32 channel, float& result) const;

    /**
     * Execute vibration on the device.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode ExecuteVibrationSequence(const TArray<FVibration> vibrationSequence) const;

    /**
     * Check if bracer task is finished.
     * @param result True if task finished, otherwise false.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode IsTaskFinished(bool& result) const;

    /**
     * Stop bracer task. Remember to free the target UBracerCotask object after calling this method because it will be not useful at all after that moment.
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
    /** Pointer to the native bracer cotask object */
    mutable Antilatency::Bracer::ICotask _native;

    void Init(Antilatency::Bracer::ICotask native);
};

/** @} */
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
#include "UObject/NoExportTypes.h"

#include "DeviceNetworkTypes.h"
#include "RadioMetricsTypes.h"

#include <Antilatency.RadioMetrics.h>
#include <Antilatency.RadioMetrics.Interop.h>

#include "RadioMetricsCotask.generated.h"

/**
 * An UE wrapper for the host part of the radio metrics task (cotask). That task can be executed on the USB Radio Socket nodes to get radio metrics data.
 * Do not instantiate this class directly by calling NewObject<URadioMetricsCotask> method,
 * use URadioMetricsLibrary::StartRadioMetricsTask or URadioMetricsCotask::CreateRadioMetricsCotask instead.
 */
UCLASS(BlueprintType)
class ANTILATENCYRADIOMETRICS_API URadioMetricsCotask : public UObject {
    GENERATED_BODY()

public:

    /**
     * Create URadioMetricsCotask instance.
     * @param native The native Antilatency::RadioMetrics::ICotask object.
     * @return The pointer to the created URadioMetricsCotask instance.
     */
    static URadioMetricsCotask* CreateRadioMetricsCotask(const Antilatency::RadioMetrics::ICotask& native);

	/**
	 * Get simplified metrics.
	 * @param targetNode A slave radio node to get metrics.
	 * @param result Resulting simplified metrics.
	 * ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
	 */
	Antilatency::InterfaceContract::ExceptionCode GetMetrics(const FAdnNode& targetNode, FRadioMetrics& result) const;

	/**
	 * Get extended metrics.
	 * @param targetNode A slave radio node to get metrics.
	 * @param result Resulting extended metrics.
	 * ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
	 */
	Antilatency::InterfaceContract::ExceptionCode GetExtendedMetrics(const FAdnNode& targetNode, FExtendedMetrics& result) const;

    /**
     * Check if radio metrics task is finished.
     * @param result True if task finished, otherwise false.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode IsTaskFinished(bool& result) const;

    /**
     * Stop radio metrics task. Remember to free the target URadioMetricsCotask object after calling this method because it will be not useful at all after that moment.
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
    /** Pointer to the native radio metrics cotask object */
    mutable Antilatency::RadioMetrics::ICotask _native;

    void Init(Antilatency::RadioMetrics::ICotask native);
};

/** @} */
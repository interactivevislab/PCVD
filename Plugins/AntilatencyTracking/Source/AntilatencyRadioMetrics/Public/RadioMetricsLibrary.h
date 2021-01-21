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

#include "RadioMetricsCotask.h"
#include "DeviceNetwork.h"
#include "DeviceNetworkTypes.h"

#include <Antilatency.RadioMetrics.h>

#include "RadioMetricsLibrary.generated.h"

/** 
 * Provides methods to work with Antilatency Radio Metrics library.
 * Do not instantiate this class directly by calling NewObject<URadioMetricsLibrary> method,
 * use URadioMetricsLibrary::GetLibrary instead.
 */
UCLASS(BlueprintType)
class ANTILATENCYRADIOMETRICS_API URadioMetricsLibrary : public UObject {
    GENERATED_BODY()

public:
    /** @return RadioMetrics library object */
    static URadioMetricsLibrary* GetLibrary();

	/** Start radio metrics task on node. */
    Antilatency::InterfaceContract::ExceptionCode StartRadioMetricsTask(const UDeviceNetwork* network, const FAdnNode& node, URadioMetricsCotask*& result) const;

    /** Check if node supports radio metrics task */
    Antilatency::InterfaceContract::ExceptionCode IsSupported(const UDeviceNetwork* network, const FAdnNode& node, bool& result) const;

    /** Get list of currently connected nodes that supports radio metrics task */
    Antilatency::InterfaceContract::ExceptionCode FindSupportedNodes(const UDeviceNetwork* network, TArray<FAdnNode>& result) const;

    /** @return true if library initialized properly */
    bool IsValid() const;

private:
    /** Pointer to native radio metrics library object */
    mutable Antilatency::RadioMetrics::ILibrary _library;

    Antilatency::RadioMetrics::ICotaskConstructor GetCotaskConstructor() const;
	
    void Init(Antilatency::RadioMetrics::ILibrary& library);
};

/** @} */
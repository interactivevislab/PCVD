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

/** @addtogroup hardwareExtensionInterfaceModule
 *  @{
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "HardwareExtensionInterfaceTypes.h"

#include <Antilatency.HardwareExtensionInterface.h>

#include "AnalogPin.generated.h"

class UHardwareExtensionInterfaceCotask;

/**
 * An UE wrapper for the Antilatency::HardwareExtensionInterface::IAnalogPin.
 * Do not instantiate this class directly by calling NewObject<UAnalogPin> method,
 * use UHardwareExtensionInterfaceCotask::CreateAnalogPin or UAnalogPin::CreateAnalogPin instead.
 */
UCLASS(BlueprintType)
class ANTILATENCYHARDWAREEXTENSIONINTERFACE_API UAnalogPin : public UObject {
    GENERATED_BODY()

public:

    /**
     * Create UAnalogPin instance.
     * @param native The native Antilatency::HardwareExtensionInterface::IAnalogPin object.
	 * @param cotask Pointer to UHardwareExtensionInterfaceCotask object.
     * @return The pointer to the created UAnalogPin instance.
     */
    static UAnalogPin* CreateAnalogPin(const Antilatency::HardwareExtensionInterface::IAnalogPin& native, const UHardwareExtensionInterfaceCotask* cotask);

	/**
	 * Get pin state in analog mode.
	 * @param result Current pin state in analog mode.
	 * ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
	 */
	Antilatency::InterfaceContract::ExceptionCode GetValue(float& result) const;

    /**
     * Check if the wrapper initialized properly and cotask object is alive.
     * @return True if the cotask wrapper initialized properly, otherwise false.
     */
    bool IsValid() const;

private:
    mutable Antilatency::HardwareExtensionInterface::IAnalogPin _native;
	const UHardwareExtensionInterfaceCotask* _cotask;
};

/** @} */
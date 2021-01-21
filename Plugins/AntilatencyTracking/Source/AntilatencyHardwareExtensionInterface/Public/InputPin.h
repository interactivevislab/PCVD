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

#include "InputPin.generated.h"

class UHardwareExtensionInterfaceCotask;


/**
 * An UE wrapper for the Antilatency::HardwareExtensionInterface::IInputPin.
 * Do not instantiate this class directly by calling NewObject<UInputPin> method,
 * use UHardwareExtensionInterfaceCotask::CreateInputPin or UInputPin::CreateInputPin instead.
 */
UCLASS(BlueprintType)
class ANTILATENCYHARDWAREEXTENSIONINTERFACE_API UInputPin : public UObject {
    GENERATED_BODY()

public:

    /**
	 * Create UInputPin instance.
	 * @param native The native Antilatency::HardwareExtensionInterface::IInputPin object.
	 * @param cotask Pointer to UHardwareExtensionInterfaceCotask object.
	 * @return The pointer to the created UAnalogPin instance.
     */
    static UInputPin* CreateInputPin(const Antilatency::HardwareExtensionInterface::IInputPin& native, const UHardwareExtensionInterfaceCotask* cotask);

	/**
	 * Get pin state in input mode.
	 * @param result Current pin state in input mode.
	 * ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
	 */
	Antilatency::InterfaceContract::ExceptionCode GetState(EPinState& result) const;

    /**
	 * Check if the wrapper initialized properly and cotask object is alive.
	 * @return True if the cotask wrapper initialized properly, otherwise false.
     */
    bool IsValid() const;

private:
    mutable Antilatency::HardwareExtensionInterface::IInputPin _native;
	const UHardwareExtensionInterfaceCotask* _cotask;
};

/** @} */
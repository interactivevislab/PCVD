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

#include "OutputPin.generated.h"

class UHardwareExtensionInterfaceCotask;

/**
 * An UE wrapper for the Antilatency::HardwareExtensionInterface::IOutputPin.
 * Do not instantiate this class directly by calling NewObject<UOutputPin> method,
 * use UHardwareExtensionInterfaceCotask::CreateOutputPin or UOutputPin::CreateOutputPin instead.
 */
UCLASS(BlueprintType)
class ANTILATENCYHARDWAREEXTENSIONINTERFACE_API UOutputPin : public UObject {
    GENERATED_BODY()

public:

    /**
	 * Create UOutputPin instance.
	 * @param native The native Antilatency::HardwareExtensionInterface::IOutputPin object.
	 * @param cotask Pointer to UHardwareExtensionInterfaceCotask object.
	 * @return The pointer to the created UOutputPin instance.
     */
    static UOutputPin* CreateOutputPin(const Antilatency::HardwareExtensionInterface::IOutputPin& native, const UHardwareExtensionInterfaceCotask* cotask);

	/**
	 * Get pin state in input mode.
	 * @param result Current pin state in input mode.
	 * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
	 */
	Antilatency::InterfaceContract::ExceptionCode GetState(EPinState& result) const;

	/**
	 * Set pin state in input mode.
	 * @param state Pin state to set.
	 * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
	 */
	Antilatency::InterfaceContract::ExceptionCode SetState(const EPinState state) const;

    /**
	 * Check if the wrapper initialized properly and cotask object is alive.
	 * @return True if the cotask wrapper initialized properly, otherwise false.
     */
    bool IsValid() const;

private:
    mutable Antilatency::HardwareExtensionInterface::IOutputPin _native;
	const UHardwareExtensionInterfaceCotask* _cotask;
};

/** @} */
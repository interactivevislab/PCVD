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

#include "InputPin.h"
#include "OutputPin.h"
#include "AnalogPin.h"
#include "PulseCounterPin.h"
#include "HardwareExtensionInterfaceTypes.h"

#include <Antilatency.HardwareExtensionInterface.h>
#include <Antilatency.HardwareExtensionInterface.Interop.h>

#include "HardwareExtensionInterfaceCotask.generated.h"

/**
 * An UE wrapper for the host part of the hardware extension interface task (cotask).
 * Do not instantiate this class directly by calling NewObject<UHardwareExtensionInterfaceCotask> method,
 * use UHardwareExtensionInterfaceLibrary::StartHardwareExtensionInterfaceTask or UHardwareExtensionInterfaceCotask::CreateHardwareExtensionInterfaceCotask instead.
 */
UCLASS(BlueprintType)
class ANTILATENCYHARDWAREEXTENSIONINTERFACE_API UHardwareExtensionInterfaceCotask : public UObject {
    GENERATED_BODY()

public:

    /**
     * Create UHardwareExtensionInterfaceCotask instance.
     * @param native The native Antilatency::HardwareExtensionInterface::ICotask object.
     * @return The pointer to the created UHardwareExtensionInterfaceCotask instance.
     */
    static UHardwareExtensionInterfaceCotask* CreateHardwareExtensionInterfaceCotask(const Antilatency::HardwareExtensionInterface::ICotask& native);

	/**
	 * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
	 */
	Antilatency::InterfaceContract::ExceptionCode CreateInputPin(const EPins& pin, UInputPin*& result) const;

	/**
	 * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
	 */
	Antilatency::InterfaceContract::ExceptionCode CreateOutputPin(const EPins& pin, const EPinState& initialState, UOutputPin*& result) const;

	/**
	 * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
	 */
	Antilatency::InterfaceContract::ExceptionCode CreateAnalogPin(const EPins& pin, const uint32_t refreshIntervalMs, UAnalogPin*& result) const;

	/**
	 * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
	 */
	Antilatency::InterfaceContract::ExceptionCode CreatePulseCounterPin(const EPins& pin, const uint32_t refreshIntervalMs, UPulseCounterPin*& result) const;

	/**
	 * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
	 */
	Antilatency::InterfaceContract::ExceptionCode Run() const;

    /**
     * Check if task is finished.
     * @param result True if task finished, otherwise false.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode IsTaskFinished(bool& result) const;

    /**
     * Stop task. Remember to free the target UHardwareExtensionInterfaceCotask object after calling this method because it will be not useful at all after that moment.
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
    mutable Antilatency::HardwareExtensionInterface::ICotask _native;
};

/** @} */
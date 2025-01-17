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

/** @addtogroup deviceNetworkModule
 *  @{
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include <Antilatency.DeviceNetwork.h>

#include "DeviceNetworkTypes.generated.h"

/**
 * The UE wrapper for the Antilatency::DeviceNetwork::NodeHandle. Every time device is connected,
 * the unique handle will be applied to it, so, when device disconnects,
 * ENodeStatus for its node becomes Invalid, after reconnection this devices receives new handle.
 */
USTRUCT(BlueprintType, Category = "Antilatency|DeviceNetwork|Library|AdnNode")
struct FAdnNode {
	GENERATED_BODY()

		FAdnNode() : NativeHandleValue(static_cast<int32>(Antilatency::DeviceNetwork::NodeHandle::Null)) {}
	FAdnNode(Antilatency::DeviceNetwork::NodeHandle native) : NativeHandleValue(static_cast<int32>(native)) {}
	FAdnNode(int32 value) : NativeHandleValue(value) {}

	UPROPERTY(BlueprintReadOnly, Category = "Antilatency|DeviceNetwork|Library|AdnNode")
		int32 NativeHandleValue;

	FORCEINLINE bool operator==(const FAdnNode& other) const {
		return NativeHandleValue == other.NativeHandleValue;
	}

	FORCEINLINE bool operator!=(const FAdnNode& other) const {
		return NativeHandleValue != other.NativeHandleValue;
	}

	friend uint32 GetTypeHash(const FAdnNode& Other) {
		return GetTypeHash(Other.NativeHandleValue);
	}

	Antilatency::DeviceNetwork::NodeHandle ToNative() const {
		return static_cast<Antilatency::DeviceNetwork::NodeHandle>(NativeHandleValue);
	}
};

/**
 * USB device identifier.
 */
USTRUCT(BlueprintType, Category = "Antilatency|DeviceNetwork|USB Device Type")
struct FUsbDeviceType {
    GENERATED_BODY()

    FUsbDeviceType() : vid(static_cast<int32>(Antilatency::DeviceNetwork::UsbVendorId::Antilatency)), pid(0x0000) {}
    FUsbDeviceType(Antilatency::DeviceNetwork::UsbDeviceType native) : vid(static_cast<int32>(native.vid)), pid(native.pid) {}

    FORCEINLINE bool operator==(const FUsbDeviceType& other) const {
        return vid == other.vid && pid == other.pid;
    }

    FORCEINLINE bool operator!=(const FUsbDeviceType& other) const {
        return vid != other.vid || pid != other.pid;
    }

    Antilatency::DeviceNetwork::UsbDeviceType ToNative() const {
        Antilatency::DeviceNetwork::UsbDeviceType result;
        result.pid = pid;
        result.vid = static_cast<Antilatency::DeviceNetwork::UsbVendorId>(vid);
        return result;
    }

    /** USB device vendor ID. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Antilatency|DeviceNetwork|USB Device Type")
    int32 vid;

    /** USB device product ID. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Antilatency|DeviceNetwork|USB Device Type")
    int32 pid;

    /** Default USB device identifier for Antilatency devices. */
    static FUsbDeviceType AntilatencyUsbDeviceType() {
        FUsbDeviceType result;
        result.vid = static_cast<int32>(Antilatency::DeviceNetwork::UsbVendorId::Antilatency);
        result.pid = 0x0000;
        return result;
    }

    /** Legacy USB device identifier for Antilatency devices. */
    static FUsbDeviceType AntilatencyUsbDeviceTypeLegacy() {
        FUsbDeviceType result;
        result.vid = static_cast<int32>(Antilatency::DeviceNetwork::UsbVendorId::AntilatencyLegacy);
        result.pid = 0x0000;
        return result;
    }
};

/** Defines different node conditions. */
UENUM(BlueprintType, Category = "Antilatency|DeviceNetwork|Node Status")
enum class ENodeStatus : uint8 {
    /** The node in connected and no task is currently running on it. Any supported task can be started on it. */
    Idle,
    /** The node in connected and a task is currently running on it. Before running any task on such node, you need to stop the current task first. */
    TaskRunning,
    /** The node in not valid, no tasks can be executed on it. */
    Invalid
};

/** @} */
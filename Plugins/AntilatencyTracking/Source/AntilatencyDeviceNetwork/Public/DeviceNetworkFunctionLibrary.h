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
#include "Kismet/BlueprintFunctionLibrary.h"

#include "DeviceNetworkLibrary.h"
#include "DeviceNetwork.h"
#include "DeviceNetworkTypes.h"

#include "DeviceNetworkFunctionLibrary.generated.h"

 /** An additional enum that is used by the blueprint methods to allow user to check if called method has been executed successfully or not. */
UENUM(BlueprintType)
enum class EDeviceNetworkExceptionResult : uint8 {
    /** The method executed successfully. */
    Success = 1 UMETA(DisplayName = "Success"),
    /** The method execution failed with some exception. */
    Fail = 0 UMETA(DisplayName = "Fail")
};


/**
 * Provides Device Network module's methods wrappers for the UE blueprint system.
 */
UCLASS()
class ANTILATENCYDEVICENETWORK_API UDeviceNetworkFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:

    /**
     * Get the native device network library object.
     * @param result The native device network library object.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|DeviceNetwork|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void GetDeviceNetworkLibrary(UDeviceNetworkLibrary*& result, EDeviceNetworkExceptionResult& exception);

    /**
     * Create the device network to work with Antilatency devices.
     * @param deviceNetworkLibrary The pointer to the UDeviceNetworkLibrary object.
     * @param usbDeviceTypes The array of the USB devices identifiers that will be used by network.
     * @param result The pointer to the created UDeviceNetwork instance.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|DeviceNetwork|Network", Meta = (ExpandEnumAsExecs = "exception"))
    static void CreateNetwork(const UDeviceNetworkLibrary* deviceNetworkLibrary, const TArray<FUsbDeviceType>& usbDeviceTypes, UDeviceNetwork*& result, EDeviceNetworkExceptionResult& exception);

    /**
     * Get the Antilatency Device Network library version.
     * @param deviceNetworkLibrary The pointer to the UDeviceNetworkLibrary object.
     * @param result The Antilatency Device Network library version.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|DeviceNetwork|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void GetVersion(const UDeviceNetworkLibrary* deviceNetworkLibrary, FString& result, EDeviceNetworkExceptionResult& exception);

    /** 
     * Set the log verbosity level for Antilatency Device Network library. 
     * @param deviceNetworkLibrary The pointer to the UDeviceNetworkLibrary object.
     * @param level The verbosity level to set.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|DeviceNetwork|Library", Meta = (ExpandEnumAsExecs = "exception"))
    static void SetLogLevel(const UDeviceNetworkLibrary* deviceNetworkLibrary, const EDeviceNetworkLogLevel& level, EDeviceNetworkExceptionResult& exception);

    /**
     * Check if UDeviceNetworkLibrary has been initialized properly (the UDeviceNetworkLibrary is not nullptr and the native Antilatency::DeviceNetwork::ILibrary is not nullptr).
     * @param deviceNetworkLibrary A pointer to the UDeviceNetworkLibrary object.
     * @return True if object is initialized properly, otherwise false.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|DeviceNetwork|Library")
    static bool IsLibraryValid(const UDeviceNetworkLibrary* deviceNetworkLibrary);




    /**
     * Every time any supported device is connected or disconnected, update ID will be incremented. You can use this method to check if there are any changes in ADN.
     * @param network The pointer to the UDeviceNetwork object.
     * @param result Current Device Network update ID.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|DeviceNetwork|Network", Meta = (ExpandEnumAsExecs = "exception"))
    static void GetUpdateId(const UDeviceNetwork* network, int32& result, EDeviceNetworkExceptionResult& exception);

    /**
     * Get USB device types selected to work with this network instance.
     * @param network The pointer to the UDeviceNetwork object.
     * @param result The array of FUsbDeviceType, that describes the list of USB devices which is used by this Device Network instance to work with.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|DeviceNetwork|Network", Meta = (ExpandEnumAsExecs = "exception"))
    static void GetDevicesTypes(const UDeviceNetwork* network, TArray<FUsbDeviceType>& result, EDeviceNetworkExceptionResult& exception);

    /**
     * Get all currently connected nodes.
     * @param network The pointer to the UDeviceNetwork object.
     * @param result The array of currently connected devices.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|DeviceNetwork|Network", Meta = (ExpandEnumAsExecs = "exception"))
    static void GetNodes(const UDeviceNetwork* network, TArray<FAdnNode>& result, EDeviceNetworkExceptionResult& exception);

    /**
     * Get current node status.
     * @param network The pointer to the UDeviceNetwork object.
     * @param node The node to get status.
     * @param result Current node status.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|DeviceNetwork|Network", Meta = (ExpandEnumAsExecs = "exception"))
    static void NodeGetStatus(const UDeviceNetwork* network, const FAdnNode& node, ENodeStatus& result, EDeviceNetworkExceptionResult& exception);

    /**
     * Checks if task is supported by node.
     * @param network The pointer to the UDeviceNetwork object.
     * @param node The node top check the task support.
     * @param interfaceId The guid of task.
     * @param result True if the node supports the task, otherwise false.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|DeviceNetwork|Network", Meta = (ExpandEnumAsExecs = "exception"))
    static void NodeIsTaskSupported(const UDeviceNetwork* network, const FAdnNode& node, const FGuid& interfaceId, bool& result, EDeviceNetworkExceptionResult& exception);

    /**
     * Get the parent node.
     * @param network The pointer to the UDeviceNetwork object.
     * @param node The node to get it's parent.
     * @param result The node's parent. If node is USB node, parent will be Null node.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|DeviceNetwork|Network", Meta = (ExpandEnumAsExecs = "exception"))
    static void NodeGetParent(const UDeviceNetwork* network, const FAdnNode& node, FAdnNode& result, EDeviceNetworkExceptionResult& exception);

    /**
     * The physical address path to the first level device that contains this node in the network tree.
     * @param network The pointer to the UDeviceNetwork object.
     * @param node The node to get physical path.
     * @param result The USB node physical path.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|DeviceNetwork|Network", Meta = (ExpandEnumAsExecs = "exception"))
    static void NodeGetPhysicalPath(const UDeviceNetwork* network, const FAdnNode& node, FString& result, EDeviceNetworkExceptionResult& exception);

    /**
     * Get the node string property value.
     * @param network The pointer to the UDeviceNetwork object.
     * @param node The node to get property from.
     * @param key The property name to get value for.
     * @param result The property value.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|DeviceNetwork|Network", Meta = (ExpandEnumAsExecs = "exception"))
    static void NodeGetStringProperty(const UDeviceNetwork* network, const FAdnNode& node, const FString& key, FString& result, EDeviceNetworkExceptionResult& exception);

    /**
     * Set the node string property value.
     * @param network The pointer to the UDeviceNetwork object.
     * @param node The node to set property on.
     * @param key The property name.
     * @param value The property value to set.
     * @param exception Method execution result.
     */
    UFUNCTION(BlueprintCallable, Category = "Antilatency|DeviceNetwork|Network", Meta = (ExpandEnumAsExecs = "exception"))
    static void NodeSetStringProperty(const UDeviceNetwork* network, const FAdnNode& node, const FString& key, const FString& value, EDeviceNetworkExceptionResult& exception);

    /**
     * Check if the Device Network wrapper initialized properly.
     * @param network The pointer to the UDeviceNetwork object.
     * @return True if the Device Network wrapper initialized properly, otherwise false.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|DeviceNetwork|Network")
    static bool IsNetworkValid(const UDeviceNetwork* network);



	/**
	* Check if two FAdnNodes are equal.
	* @param arg1 The first FAdnNode to compare.
	* @param arg2 The second FAdnNode to compare.
	* @return True if nodes are equal, otherwise false.
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal FAdnNode", CompactNodeTitle = "==", Keywords = "== equal"), Category = "Math")
	static bool EqualEqual_FAdnNodeFAdnNode(const FAdnNode& arg1, const FAdnNode& arg2);

	/**
	 * Check if two FAdnNodes are not equal.
	 * @param arg1 The first FAdnNode to compare.
	 * @param arg2 The second FAdnNode to compare.
	 * @return True if nodes are not equal, otherwise false.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Not Equal FAdnNode", CompactNodeTitle = "!=", Keywords = "!= not equal"), Category = "Math")
	static bool NotEqual_FAdnNodeFAdnNode(const FAdnNode& arg1, const FAdnNode& arg2);
};

/** @} */
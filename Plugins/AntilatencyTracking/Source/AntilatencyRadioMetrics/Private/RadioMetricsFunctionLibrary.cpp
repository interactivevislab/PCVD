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

#include "RadioMetricsFunctionLibrary.h"

void URadioMetricsFunctionLibrary::GetRadioMetricsLibrary(URadioMetricsLibrary *&result, ERadioMetricsExceptionResult &exception) {
    result = URadioMetricsLibrary::GetLibrary();
    exception = static_cast<ERadioMetricsExceptionResult>(result != nullptr);
}

void URadioMetricsFunctionLibrary::StartRadioMetricsTask(const URadioMetricsLibrary *radioMetricsLibrary, const UDeviceNetwork *network, const FAdnNode &node, URadioMetricsCotask *&result, ERadioMetricsExceptionResult &exception)
{
    if (radioMetricsLibrary == nullptr) {
        exception = ERadioMetricsExceptionResult::Fail;
        return;
    }

    auto callResult = radioMetricsLibrary->StartRadioMetricsTask(network, node, result);
    exception = static_cast<ERadioMetricsExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void URadioMetricsFunctionLibrary::IsSupported(const URadioMetricsLibrary *radioMetricsLibrary, const UDeviceNetwork *network, const FAdnNode &node, bool &result, ERadioMetricsExceptionResult &exception) {
    result = false;
    if (radioMetricsLibrary == nullptr || network == nullptr) {
        exception = ERadioMetricsExceptionResult::Fail;
        return;
    }

    auto callResult = radioMetricsLibrary->IsSupported(network, node, result);
    exception = static_cast<ERadioMetricsExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void URadioMetricsFunctionLibrary::FindSupportedNodes(const URadioMetricsLibrary *radioMetricsLibrary, const UDeviceNetwork *network, TArray<FAdnNode> &result, ERadioMetricsExceptionResult &exception) {
    result.Empty();

    if (radioMetricsLibrary == nullptr || network == nullptr) {
        exception = ERadioMetricsExceptionResult::Fail;
        return;
    }

    auto callResult = radioMetricsLibrary->FindSupportedNodes(network, result);
    exception = static_cast<ERadioMetricsExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

bool URadioMetricsFunctionLibrary::IsLibraryValid(const URadioMetricsLibrary *radioMetricsLibrary) {
    if (radioMetricsLibrary == nullptr) {
        return false;
    }

    return radioMetricsLibrary->IsValid();
}

void URadioMetricsFunctionLibrary::IsTaskFinished(const URadioMetricsCotask *radioMetricsCotask, bool &result, ERadioMetricsExceptionResult &exception) {
    if (radioMetricsCotask == nullptr) {
        exception = ERadioMetricsExceptionResult::Fail;
        return;
    }

    auto callResult = radioMetricsCotask->IsTaskFinished(result);
    exception = static_cast<ERadioMetricsExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void URadioMetricsFunctionLibrary::Stop(URadioMetricsCotask *radioMetricsCotask) {
    if (radioMetricsCotask == nullptr) {
        return;
    }

    radioMetricsCotask->Stop();
}

bool URadioMetricsFunctionLibrary::IsRadioMetricsTaskValid(const URadioMetricsCotask *radioMetricsCotask) {
    if (radioMetricsCotask == nullptr) {
        return false;
    }
    
    return radioMetricsCotask->IsValid();
}

void URadioMetricsFunctionLibrary::GetMetrics(const URadioMetricsCotask* radioMetricsCotask, const FAdnNode& targetNode, FRadioMetrics& result, ERadioMetricsExceptionResult& exception) {
	if (radioMetricsCotask == nullptr) {
		exception = ERadioMetricsExceptionResult::Fail;
		return;
	}

	auto callResult = radioMetricsCotask->GetMetrics(targetNode, result);
	exception = static_cast<ERadioMetricsExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void URadioMetricsFunctionLibrary::GetExtendedMetrics(const URadioMetricsCotask* radioMetricsCotask, const FAdnNode& targetNode, FExtendedMetrics& result, ERadioMetricsExceptionResult& exception) {
	if (radioMetricsCotask == nullptr) {
		exception = ERadioMetricsExceptionResult::Fail;
		return;
	}

	auto callResult = radioMetricsCotask->GetExtendedMetrics(targetNode, result);
	exception = static_cast<ERadioMetricsExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}
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

#include "BracerFunctionLibrary.h"

void UBracerFunctionLibrary::GetBracerLibrary(UBracerLibrary *&result, EBracerExceptionResult &exception) {
    result = UBracerLibrary::GetLibrary();
    exception = static_cast<EBracerExceptionResult>(result != nullptr);
}

void UBracerFunctionLibrary::StartBracerTask(const UBracerLibrary *bracerLibrary, const UDeviceNetwork *network, const FAdnNode &node, UBracerCotask *&result, EBracerExceptionResult &exception)
{
    if (bracerLibrary == nullptr) {
        exception = EBracerExceptionResult::Fail;
        return;
    }

    auto callResult = bracerLibrary->StartBracerTask(network, node, result);
    exception = static_cast<EBracerExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UBracerFunctionLibrary::IsSupported(const UBracerLibrary *bracerLibrary, const UDeviceNetwork *network, const FAdnNode &node, bool &result, EBracerExceptionResult &exception) {
    result = false;
    if (bracerLibrary == nullptr || network == nullptr) {
        exception = EBracerExceptionResult::Fail;
        return;
    }

    auto callResult = bracerLibrary->IsSupported(network, node, result);
    exception = static_cast<EBracerExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UBracerFunctionLibrary::FindSupportedNodes(const UBracerLibrary *bracerLibrary, const UDeviceNetwork *network, TArray<FAdnNode> &result, EBracerExceptionResult &exception) {
    result.Empty();

    if (bracerLibrary == nullptr || network == nullptr) {
        exception = EBracerExceptionResult::Fail;
        return;
    }

    auto callResult = bracerLibrary->FindSupportedNodes(network, result);
    exception = static_cast<EBracerExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

bool UBracerFunctionLibrary::IsLibraryValid(const UBracerLibrary *bracerLibrary) {
    if (bracerLibrary == nullptr) {
        return false;
    }

    return bracerLibrary->IsValid();
}


void UBracerFunctionLibrary::GetBatteryLevel(const UBracerCotask* bracerCotask, float& result, EBracerExceptionResult& exception) {
	if (bracerCotask == nullptr) {
		exception = EBracerExceptionResult::Fail;
		return;
	}

	auto callResult = bracerCotask->GetBatteryLevel(result);
	exception = static_cast<EBracerExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void GetTouchChannelsCount(const UBracerCotask* bracerCotask, int32& result, EBracerExceptionResult& exception) {
	if (bracerCotask == nullptr) {
		exception = EBracerExceptionResult::Fail;
		return;
	}

	auto callResult = bracerCotask->GetTouchChannelsCount(result);
	exception = static_cast<EBracerExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UBracerFunctionLibrary::GetTouchNativeValue(const UBracerCotask* bracerCotask, const int32 channel, int32& result, EBracerExceptionResult& exception) {
	if (bracerCotask == nullptr) {
		exception = EBracerExceptionResult::Fail;
		return;
	}

	auto callResult = bracerCotask->GetTouchNativeValue(channel, result);
	exception = static_cast<EBracerExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}


void UBracerFunctionLibrary::GetTouch(const UBracerCotask* bracerCotask, const int32 channel, float& result, EBracerExceptionResult& exception) {
    if (bracerCotask == nullptr) {
        exception = EBracerExceptionResult::Fail;
        return;
    }

    auto callResult = bracerCotask->GetTouch(channel, result);
    exception = static_cast<EBracerExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UBracerFunctionLibrary::ExecuteVibrationSequence(const UBracerCotask* bracerCotask, const TArray<FVibration>& vibrationSequence, EBracerExceptionResult& exception) {
    if (bracerCotask == nullptr) {
        exception = EBracerExceptionResult::Fail;
        return;
    }

    auto callResult = bracerCotask->ExecuteVibrationSequence(vibrationSequence);
    exception = static_cast<EBracerExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UBracerFunctionLibrary::IsTaskFinished(const UBracerCotask *bracerCotask, bool &result, EBracerExceptionResult &exception) {
    if (bracerCotask == nullptr) {
        exception = EBracerExceptionResult::Fail;
        return;
    }

    auto callResult = bracerCotask->IsTaskFinished(result);
    exception = static_cast<EBracerExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UBracerFunctionLibrary::Stop(UBracerCotask *bracerCotask) {
    if (bracerCotask == nullptr) {
        return;
    }

    bracerCotask->Stop();
}

bool UBracerFunctionLibrary::IsBracerTaskValid(const UBracerCotask *bracerCotask) {
    if (bracerCotask == nullptr) {
        return false;
    }
    
    return bracerCotask->IsValid();
}
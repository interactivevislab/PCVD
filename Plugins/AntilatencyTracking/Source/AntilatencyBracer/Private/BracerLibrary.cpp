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

#include "BracerLibrary.h"
#include "IAntilatencyBracerModule.h"
#include "BracerLog.h"

#include <ExceptionCheck.h>

UBracerLibrary *UBracerLibrary::GetLibrary() {
    auto module = IAntilatencyBracerModule::Get();
    auto library = module.GetNativeLibrary();

    if (library == nullptr) {
        return nullptr;
    }

    auto result = NewObject<UBracerLibrary>();
    result->Init(library);
    return result;
}

void UBracerLibrary::Init(Antilatency::Bracer::ILibrary &library) {
    _library = library;
}

bool UBracerLibrary::IsValid() const {
    if (_library == nullptr) {
        BRACER_LOG(Warning, TEXT("Library is null"));
        return false;
    }
    return true;
}

Antilatency::InterfaceContract::ExceptionCode UBracerLibrary::StartBracerTask(const UDeviceNetwork* network, const FAdnNode& node, UBracerCotask*& result) const {
    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }
    auto constructor = GetCotaskConstructor();
    if (constructor == nullptr) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::Bracer::ICotask nativeCotask;
    auto exception = constructor.startTask(network->GetNative(), node.ToNative(), nativeCotask);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);
    if (nativeCotask == nullptr) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    result = UBracerCotask::CreateBracerCotask(nativeCotask);
    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UBracerLibrary::IsSupported(const UDeviceNetwork *network, const FAdnNode &node, bool &result) const {
    result = false;

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    auto cotaskConstructor = GetCotaskConstructor();

    if (cotaskConstructor == nullptr) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::InterfaceContract::LongBool nativeResult;
    auto exception = cotaskConstructor.isSupported(network->GetNative(), node.ToNative(), nativeResult);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);

    result = static_cast<bool>(nativeResult);

    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UBracerLibrary::FindSupportedNodes(const UDeviceNetwork *network, TArray<FAdnNode> &result) const {
    result.Empty();

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    auto constructor = GetCotaskConstructor();
    if (constructor == nullptr) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    std::vector<Antilatency::DeviceNetwork::NodeHandle> nativeResult;
    auto exception = constructor.findSupportedNodes(network->GetNative(), nativeResult);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);

    for (auto node : nativeResult) {
        result.Add(FAdnNode(node));
    }

    return exception;
}

Antilatency::Bracer::ICotaskConstructor UBracerLibrary::GetCotaskConstructor() const {
    if (!IsValid()) {
        return nullptr;
    }
    Antilatency::Bracer::ICotaskConstructor result;
    auto exception = _library.getCotaskConstructor(result);
    ANTILATENCY_EXCEPTION_CHECK(_library, exception);

    return result;
}
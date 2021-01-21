//Copyright 2020, ALT LLC. All Rights Reserved.
//This file is part of Antilatency SDK.
//It is subject to the license terms in the LICENSE file found in the top-level directory
//of this distribution and at http://www.antilatency.com/eula
//You may not use this file except in compliance with the License.
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
#pragma once
#include <Antilatency.InterfaceContract.h>
#include <Antilatency.Math.h>
#include <cstdint>
#include <Antilatency.DeviceNetwork.h>
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4946)
#pragma warning(disable: 4265)
#endif
namespace Antilatency {
	namespace Alt {
		namespace Tracking {
			enum class MarkerIndex : uint32_t {
				MaximumValidMarkerIndex = 0xFFFFFFF0,
				Invalid = 0xFFFFFFFE,
				Unknown = 0xFFFFFFFF
			};
			ANTILATENCY_ENUM_INTEGER_BEHAVIOUR_UNSIGNED(MarkerIndex,uint32_t)
		} //namespace Tracking
	} //namespace Alt
} //namespace Antilatency
namespace Antilatency {
	inline const char* enumToString(const Antilatency::Alt::Tracking::MarkerIndex& x) {
		switch (x) {
			case Antilatency::Alt::Tracking::MarkerIndex::MaximumValidMarkerIndex: return "MaximumValidMarkerIndex";
			case Antilatency::Alt::Tracking::MarkerIndex::Invalid: return "Invalid";
			case Antilatency::Alt::Tracking::MarkerIndex::Unknown: return "Unknown";
		}
		return "";
	}
} //namespace Antilatency

namespace Antilatency {
	namespace Alt {
		namespace Tracking {
			/* copy and paste this to implementer
			Antilatency::InterfaceContract::ExceptionCode isMutable(Antilatency::InterfaceContract::LongBool& result) {
				return Antilatency::InterfaceContract::ExceptionCode::NotImplemented;
			}
			Antilatency::InterfaceContract::ExceptionCode getMarkers(std::vector<Antilatency::Math::float3>& result) {
				return Antilatency::InterfaceContract::ExceptionCode::NotImplemented;
			}
			Antilatency::InterfaceContract::ExceptionCode filterRay(Antilatency::Math::float3 up, Antilatency::Math::float3 ray, Antilatency::InterfaceContract::LongBool& result) {
				return Antilatency::InterfaceContract::ExceptionCode::NotImplemented;
			}
			Antilatency::InterfaceContract::ExceptionCode match(const std::vector<Antilatency::Math::float3>& raysUpSpace, std::vector<Antilatency::Alt::Tracking::MarkerIndex>& markersIndices, Antilatency::Math::floatP3Q& poseOfUpSpace, Antilatency::InterfaceContract::LongBool& result) {
				return Antilatency::InterfaceContract::ExceptionCode::NotImplemented;
			}
			Antilatency::InterfaceContract::ExceptionCode matchByPosition(const std::vector<Antilatency::Math::float3>& rays, Antilatency::Math::float3 origin, std::vector<Antilatency::Alt::Tracking::MarkerIndex>& result) {
				return Antilatency::InterfaceContract::ExceptionCode::NotImplemented;
			}
			*/
			struct IEnvironment : Antilatency::InterfaceContract::IInterface {
				struct VMT : Antilatency::InterfaceContract::IInterface::VMT {
					virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL isMutable(Antilatency::InterfaceContract::LongBool& result) = 0;
					virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getMarkers(Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) = 0;
					virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL filterRay(Antilatency::Math::float3 up, Antilatency::Math::float3 ray, Antilatency::InterfaceContract::LongBool& result) = 0;
					virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL match(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate raysUpSpace, Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate markersIndices, Antilatency::Math::floatP3Q& poseOfUpSpace, Antilatency::InterfaceContract::LongBool& result) = 0;
					virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL matchByPosition(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate rays, Antilatency::Math::float3 origin, Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) = 0;
					static constexpr Antilatency::InterfaceContract::InterfaceID ID() {
						return Antilatency::InterfaceContract::InterfaceID{0xc257c858,0xf296,0x43b7,{0xb6,0xb5,0xc1,0x4b,0x9a,0xfb,0x1a,0x13}};
					}
				private:
					~VMT() = delete;
				};
				IEnvironment() = default;
				IEnvironment(std::nullptr_t) {}
				explicit IEnvironment(VMT* pointer) : Antilatency::InterfaceContract::IInterface(pointer) {}
				template<typename T, typename = typename std::enable_if<std::is_base_of<IEnvironment, T>::value>::type>
				IEnvironment& operator = (const T& other) {
				    Antilatency::InterfaceContract::IInterface::operator=(other);
				    return *this;
				}
				template<class Implementer, class ... TArgs>
				static IEnvironment create(TArgs&&... args) {
				    return *new Implementer(std::forward<TArgs>(args)...);
				}
				void attach(VMT* other) ANTILATENCY_NOEXCEPT {
				    Antilatency::InterfaceContract::IInterface::attach(other);
				}
				VMT* detach() ANTILATENCY_NOEXCEPT {
				    return reinterpret_cast<VMT*>(Antilatency::InterfaceContract::IInterface::detach());
				}
				Antilatency::InterfaceContract::ExceptionCode isMutable(Antilatency::InterfaceContract::LongBool& result) {
					return (reinterpret_cast<VMT*>(this->_object))->isMutable(result);
				}
				Antilatency::InterfaceContract::ExceptionCode getMarkers(std::vector<Antilatency::Math::float3>& result) {
					auto resultMarshaler = Antilatency::InterfaceContract::Details::ArrayOutMarshaler::create(result);
					return (reinterpret_cast<VMT*>(this->_object))->getMarkers(resultMarshaler);
				}
				Antilatency::InterfaceContract::ExceptionCode filterRay(Antilatency::Math::float3 up, Antilatency::Math::float3 ray, Antilatency::InterfaceContract::LongBool& result) {
					return (reinterpret_cast<VMT*>(this->_object))->filterRay(up, ray, result);
				}
				Antilatency::InterfaceContract::ExceptionCode match(const std::vector<Antilatency::Math::float3>& raysUpSpace, std::vector<Antilatency::Alt::Tracking::MarkerIndex>& markersIndices, Antilatency::Math::floatP3Q& poseOfUpSpace, Antilatency::InterfaceContract::LongBool& result) {
					auto raysUpSpaceMarshaler = Antilatency::InterfaceContract::Details::ArrayInMarshaler::create(raysUpSpace);
					auto markersIndicesMarshaler = Antilatency::InterfaceContract::Details::ArrayOutMarshaler::create(markersIndices);
					return (reinterpret_cast<VMT*>(this->_object))->match(raysUpSpaceMarshaler, markersIndicesMarshaler, poseOfUpSpace, result);
				}
				Antilatency::InterfaceContract::ExceptionCode matchByPosition(const std::vector<Antilatency::Math::float3>& rays, Antilatency::Math::float3 origin, std::vector<Antilatency::Alt::Tracking::MarkerIndex>& result) {
					auto raysMarshaler = Antilatency::InterfaceContract::Details::ArrayInMarshaler::create(rays);
					auto resultMarshaler = Antilatency::InterfaceContract::Details::ArrayOutMarshaler::create(result);
					return (reinterpret_cast<VMT*>(this->_object))->matchByPosition(raysMarshaler, origin, resultMarshaler);
				}
			};
		} //namespace Tracking
	} //namespace Alt
} //namespace Antilatency
namespace Antilatency {
	namespace InterfaceContract {
		namespace Details {
			template<typename Implementer, typename LifeTimeController>
			struct InterfaceRemap<Antilatency::Alt::Tracking::IEnvironment, Implementer, LifeTimeController> : Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::InterfaceContract::IInterface, Implementer, LifeTimeController> {
			public:
			    InterfaceRemap() = default;
			    static bool isInterfaceSupported(const Antilatency::InterfaceContract::InterfaceID& id) {
					if (id == Antilatency::Alt::Tracking::IEnvironment::VMT::ID()) {
						return true;
					}
					return Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::InterfaceContract::IInterface, Implementer, LifeTimeController>::isInterfaceSupported(id);
				}
			public:
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL isMutable(Antilatency::InterfaceContract::LongBool& result) {
					auto exceptionCode_ = this->_object->isMutable(result);
					return exceptionCode_;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getMarkers(Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) {
					std::vector<Antilatency::Math::float3> resultMarshaler;
					auto exceptionCode_ = this->_object->getMarkers(resultMarshaler);
					result = resultMarshaler;
					return exceptionCode_;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL filterRay(Antilatency::Math::float3 up, Antilatency::Math::float3 ray, Antilatency::InterfaceContract::LongBool& result) {
					auto exceptionCode_ = this->_object->filterRay(up, ray, result);
					return exceptionCode_;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL match(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate raysUpSpace, Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate markersIndices, Antilatency::Math::floatP3Q& poseOfUpSpace, Antilatency::InterfaceContract::LongBool& result) {
					std::vector<Antilatency::Alt::Tracking::MarkerIndex> markersIndicesMarshaler;
					auto exceptionCode_ = this->_object->match(raysUpSpace, markersIndicesMarshaler, poseOfUpSpace, result);
					markersIndices = markersIndicesMarshaler;
					return exceptionCode_;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL matchByPosition(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate rays, Antilatency::Math::float3 origin, Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) {
					std::vector<Antilatency::Alt::Tracking::MarkerIndex> resultMarshaler;
					auto exceptionCode_ = this->_object->matchByPosition(rays, origin, resultMarshaler);
					result = resultMarshaler;
					return exceptionCode_;
				}
			};
		} //namespace Details
	} //namespace InterfaceContract
} //namespace Antilatency

namespace Antilatency {
	namespace Alt {
		namespace Tracking {
			/// <summary>Part of Antilatency.Alt.Tracking.Stability structure. Since meaning of Stability.value depends on stage, this meaning described here.</summary>
			enum class Stage : int32_t {
				/// <summary>Tracker collect accelerometer data to find upright orientation. No tracking data is valid in this stage. value = 0</summary>
				InertialDataInitialization = 0x0,
				/// <summary>Only rotation is valid in this stage. Rotation around vertical axis may drift. value = 0</summary>
				Tracking3Dof = 0x1,
				/// <summary>Full 6 dof tracking, corrected by optics. Value represents how stable solution is. Since this value depends on many factors, there is no units for it. This value may be used for debug purposes. </summary>
				Tracking6Dof = 0x2,
				/// <summary>Inertial only 6 dof tracking, without optical corrections. Value is a fraction of time left before switch to Tracking3Dof. The value is useful for animation effects to notify the user about the oncoming loss of tracking.</summary>
				TrackingBlind6Dof = 0x3
			};
		} //namespace Tracking
	} //namespace Alt
} //namespace Antilatency
namespace Antilatency {
	inline const char* enumToString(const Antilatency::Alt::Tracking::Stage& x) {
		switch (x) {
			case Antilatency::Alt::Tracking::Stage::InertialDataInitialization: return "InertialDataInitialization";
			case Antilatency::Alt::Tracking::Stage::Tracking3Dof: return "Tracking3Dof";
			case Antilatency::Alt::Tracking::Stage::Tracking6Dof: return "Tracking6Dof";
			case Antilatency::Alt::Tracking::Stage::TrackingBlind6Dof: return "TrackingBlind6Dof";
		}
		return "";
	}
} //namespace Antilatency

namespace Antilatency {
	namespace Alt {
		namespace Tracking {
			/// <summary>Represents stability of tracking</summary>
			struct Stability {
				Antilatency::Alt::Tracking::Stage stage;
				/// <summary>Meaning of value depends on stage. See Antilatency.Alt.Tracking.Stage</summary>
				float value;
			};
		} //namespace Tracking
	} //namespace Alt
} //namespace Antilatency

namespace Antilatency {
	namespace Alt {
		namespace Tracking {
			struct State {
				/// <summary>World space position meters, local to world rotation</summary>
				Antilatency::Math::floatP3Q pose;
				/// <summary>World space, meters per second</summary>
				Antilatency::Math::float3 velocity;
				/// <summary>Local space, radians per second</summary>
				Antilatency::Math::float3 localAngularVelocity;
				/// <summary>Tracking stability</summary>
				Antilatency::Alt::Tracking::Stability stability;
			};
		} //namespace Tracking
	} //namespace Alt
} //namespace Antilatency

namespace Antilatency {
	namespace Alt {
		namespace Tracking {
			/* copy and paste this to implementer
			Antilatency::InterfaceContract::ExceptionCode getExtrapolatedState(Antilatency::Math::floatP3Q placement, float deltaTime, Antilatency::Alt::Tracking::State& result) {
				return Antilatency::InterfaceContract::ExceptionCode::NotImplemented;
			}
			Antilatency::InterfaceContract::ExceptionCode getState(float angularVelocityAvgTimeInSeconds, Antilatency::Alt::Tracking::State& result) {
				return Antilatency::InterfaceContract::ExceptionCode::NotImplemented;
			}
			*/
			struct ITrackingCotask : Antilatency::DeviceNetwork::ICotask {
				struct VMT : Antilatency::DeviceNetwork::ICotask::VMT {
					virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getExtrapolatedState(Antilatency::Math::floatP3Q placement, float deltaTime, Antilatency::Alt::Tracking::State& result) = 0;
					virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getState(float angularVelocityAvgTimeInSeconds, Antilatency::Alt::Tracking::State& result) = 0;
					static constexpr Antilatency::InterfaceContract::InterfaceID ID() {
						return Antilatency::InterfaceContract::InterfaceID{0x7f8b603c,0xfa91,0x4168,{0x92,0xb7,0xaf,0x16,0x44,0xd0,0x87,0xdb}};
					}
				private:
					~VMT() = delete;
				};
				ITrackingCotask() = default;
				ITrackingCotask(std::nullptr_t) {}
				explicit ITrackingCotask(VMT* pointer) : Antilatency::DeviceNetwork::ICotask(pointer) {}
				template<typename T, typename = typename std::enable_if<std::is_base_of<ITrackingCotask, T>::value>::type>
				ITrackingCotask& operator = (const T& other) {
				    Antilatency::DeviceNetwork::ICotask::operator=(other);
				    return *this;
				}
				template<class Implementer, class ... TArgs>
				static ITrackingCotask create(TArgs&&... args) {
				    return *new Implementer(std::forward<TArgs>(args)...);
				}
				void attach(VMT* other) ANTILATENCY_NOEXCEPT {
				    Antilatency::DeviceNetwork::ICotask::attach(other);
				}
				VMT* detach() ANTILATENCY_NOEXCEPT {
				    return reinterpret_cast<VMT*>(Antilatency::DeviceNetwork::ICotask::detach());
				}
				Antilatency::InterfaceContract::ExceptionCode getExtrapolatedState(Antilatency::Math::floatP3Q placement, float deltaTime, Antilatency::Alt::Tracking::State& result) {
					return (reinterpret_cast<VMT*>(this->_object))->getExtrapolatedState(placement, deltaTime, result);
				}
				Antilatency::InterfaceContract::ExceptionCode getState(float angularVelocityAvgTimeInSeconds, Antilatency::Alt::Tracking::State& result) {
					return (reinterpret_cast<VMT*>(this->_object))->getState(angularVelocityAvgTimeInSeconds, result);
				}
			};
		} //namespace Tracking
	} //namespace Alt
} //namespace Antilatency
namespace Antilatency {
	namespace InterfaceContract {
		namespace Details {
			template<typename Implementer, typename LifeTimeController>
			struct InterfaceRemap<Antilatency::Alt::Tracking::ITrackingCotask, Implementer, LifeTimeController> : Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::DeviceNetwork::ICotask, Implementer, LifeTimeController> {
			public:
			    InterfaceRemap() = default;
			    static bool isInterfaceSupported(const Antilatency::InterfaceContract::InterfaceID& id) {
					if (id == Antilatency::Alt::Tracking::ITrackingCotask::VMT::ID()) {
						return true;
					}
					return Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::DeviceNetwork::ICotask, Implementer, LifeTimeController>::isInterfaceSupported(id);
				}
			public:
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getExtrapolatedState(Antilatency::Math::floatP3Q placement, float deltaTime, Antilatency::Alt::Tracking::State& result) {
					auto exceptionCode_ = this->_object->getExtrapolatedState(placement, deltaTime, result);
					return exceptionCode_;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getState(float angularVelocityAvgTimeInSeconds, Antilatency::Alt::Tracking::State& result) {
					auto exceptionCode_ = this->_object->getState(angularVelocityAvgTimeInSeconds, result);
					return exceptionCode_;
				}
			};
		} //namespace Details
	} //namespace InterfaceContract
} //namespace Antilatency

namespace Antilatency {
	namespace Alt {
		namespace Tracking {
			/* copy and paste this to implementer
			Antilatency::InterfaceContract::ExceptionCode startTask(Antilatency::DeviceNetwork::INetwork network, Antilatency::DeviceNetwork::NodeHandle node, Antilatency::Alt::Tracking::IEnvironment environment, Antilatency::Alt::Tracking::ITrackingCotask& result) {
				return Antilatency::InterfaceContract::ExceptionCode::NotImplemented;
			}
			*/
			struct ITrackingCotaskConstructor : Antilatency::DeviceNetwork::ICotaskConstructor {
				struct VMT : Antilatency::DeviceNetwork::ICotaskConstructor::VMT {
					virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL startTask(Antilatency::DeviceNetwork::INetwork::VMT* network, Antilatency::DeviceNetwork::NodeHandle node, Antilatency::Alt::Tracking::IEnvironment::VMT* environment, Antilatency::Alt::Tracking::ITrackingCotask& result) = 0;
					static constexpr Antilatency::InterfaceContract::InterfaceID ID() {
						return Antilatency::InterfaceContract::InterfaceID{0x009ebfe1,0xf85c,0x4638,{0xbe,0x9d,0xaf,0x79,0x90,0xa8,0xcd,0x04}};
					}
				private:
					~VMT() = delete;
				};
				ITrackingCotaskConstructor() = default;
				ITrackingCotaskConstructor(std::nullptr_t) {}
				explicit ITrackingCotaskConstructor(VMT* pointer) : Antilatency::DeviceNetwork::ICotaskConstructor(pointer) {}
				template<typename T, typename = typename std::enable_if<std::is_base_of<ITrackingCotaskConstructor, T>::value>::type>
				ITrackingCotaskConstructor& operator = (const T& other) {
				    Antilatency::DeviceNetwork::ICotaskConstructor::operator=(other);
				    return *this;
				}
				template<class Implementer, class ... TArgs>
				static ITrackingCotaskConstructor create(TArgs&&... args) {
				    return *new Implementer(std::forward<TArgs>(args)...);
				}
				void attach(VMT* other) ANTILATENCY_NOEXCEPT {
				    Antilatency::DeviceNetwork::ICotaskConstructor::attach(other);
				}
				VMT* detach() ANTILATENCY_NOEXCEPT {
				    return reinterpret_cast<VMT*>(Antilatency::DeviceNetwork::ICotaskConstructor::detach());
				}
				Antilatency::InterfaceContract::ExceptionCode startTask(Antilatency::DeviceNetwork::INetwork network, Antilatency::DeviceNetwork::NodeHandle node, Antilatency::Alt::Tracking::IEnvironment environment, Antilatency::Alt::Tracking::ITrackingCotask& result) {
					return (reinterpret_cast<VMT*>(this->_object))->startTask(network.detach(), node, environment.detach(), result);
				}
			};
		} //namespace Tracking
	} //namespace Alt
} //namespace Antilatency
namespace Antilatency {
	namespace InterfaceContract {
		namespace Details {
			template<typename Implementer, typename LifeTimeController>
			struct InterfaceRemap<Antilatency::Alt::Tracking::ITrackingCotaskConstructor, Implementer, LifeTimeController> : Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::DeviceNetwork::ICotaskConstructor, Implementer, LifeTimeController> {
			public:
			    InterfaceRemap() = default;
			    static bool isInterfaceSupported(const Antilatency::InterfaceContract::InterfaceID& id) {
					if (id == Antilatency::Alt::Tracking::ITrackingCotaskConstructor::VMT::ID()) {
						return true;
					}
					return Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::DeviceNetwork::ICotaskConstructor, Implementer, LifeTimeController>::isInterfaceSupported(id);
				}
			public:
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL startTask(Antilatency::DeviceNetwork::INetwork::VMT* network, Antilatency::DeviceNetwork::NodeHandle node, Antilatency::Alt::Tracking::IEnvironment::VMT* environment, Antilatency::Alt::Tracking::ITrackingCotask& result) {
					Antilatency::DeviceNetwork::INetwork networkMarshaler;
					networkMarshaler.attach(network);
					Antilatency::Alt::Tracking::IEnvironment environmentMarshaler;
					environmentMarshaler.attach(environment);
					auto exceptionCode_ = this->_object->startTask(networkMarshaler, node, environmentMarshaler, result);
					return exceptionCode_;
				}
			};
		} //namespace Details
	} //namespace InterfaceContract
} //namespace Antilatency

namespace Antilatency {
	namespace Alt {
		namespace Tracking {
			/* copy and paste this to implementer
			Antilatency::InterfaceContract::ExceptionCode createEnvironment(const std::string& code, Antilatency::Alt::Tracking::IEnvironment& result) {
				return Antilatency::InterfaceContract::ExceptionCode::NotImplemented;
			}
			Antilatency::InterfaceContract::ExceptionCode createPlacement(const std::string& code, Antilatency::Math::floatP3Q& result) {
				return Antilatency::InterfaceContract::ExceptionCode::NotImplemented;
			}
			Antilatency::InterfaceContract::ExceptionCode encodePlacement(Antilatency::Math::float3 position, Antilatency::Math::float3 rotation, std::string& result) {
				return Antilatency::InterfaceContract::ExceptionCode::NotImplemented;
			}
			Antilatency::InterfaceContract::ExceptionCode createTrackingCotaskConstructor(Antilatency::Alt::Tracking::ITrackingCotaskConstructor& result) {
				return Antilatency::InterfaceContract::ExceptionCode::NotImplemented;
			}
			*/
			struct ILibrary : Antilatency::InterfaceContract::IInterface {
				struct VMT : Antilatency::InterfaceContract::IInterface::VMT {
					virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL createEnvironment(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate code, Antilatency::Alt::Tracking::IEnvironment& result) = 0;
					virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL createPlacement(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate code, Antilatency::Math::floatP3Q& result) = 0;
					virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL encodePlacement(Antilatency::Math::float3 position, Antilatency::Math::float3 rotation, Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) = 0;
					virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL createTrackingCotaskConstructor(Antilatency::Alt::Tracking::ITrackingCotaskConstructor& result) = 0;
					static constexpr Antilatency::InterfaceContract::InterfaceID ID() {
						return Antilatency::InterfaceContract::InterfaceID{0x13ac393d,0xa7c5,0x4e51,{0xa6,0xeb,0xfe,0xaa,0x11,0xc3,0xc0,0x49}};
					}
				private:
					~VMT() = delete;
				};
				ILibrary() = default;
				ILibrary(std::nullptr_t) {}
				explicit ILibrary(VMT* pointer) : Antilatency::InterfaceContract::IInterface(pointer) {}
				template<typename T, typename = typename std::enable_if<std::is_base_of<ILibrary, T>::value>::type>
				ILibrary& operator = (const T& other) {
				    Antilatency::InterfaceContract::IInterface::operator=(other);
				    return *this;
				}
				template<class Implementer, class ... TArgs>
				static ILibrary create(TArgs&&... args) {
				    return *new Implementer(std::forward<TArgs>(args)...);
				}
				void attach(VMT* other) ANTILATENCY_NOEXCEPT {
				    Antilatency::InterfaceContract::IInterface::attach(other);
				}
				VMT* detach() ANTILATENCY_NOEXCEPT {
				    return reinterpret_cast<VMT*>(Antilatency::InterfaceContract::IInterface::detach());
				}
				Antilatency::InterfaceContract::ExceptionCode createEnvironment(const std::string& code, Antilatency::Alt::Tracking::IEnvironment& result) {
					auto codeMarshaler = Antilatency::InterfaceContract::Details::ArrayInMarshaler::create(code);
					return (reinterpret_cast<VMT*>(this->_object))->createEnvironment(codeMarshaler, result);
				}
				Antilatency::InterfaceContract::ExceptionCode createPlacement(const std::string& code, Antilatency::Math::floatP3Q& result) {
					auto codeMarshaler = Antilatency::InterfaceContract::Details::ArrayInMarshaler::create(code);
					return (reinterpret_cast<VMT*>(this->_object))->createPlacement(codeMarshaler, result);
				}
				Antilatency::InterfaceContract::ExceptionCode encodePlacement(Antilatency::Math::float3 position, Antilatency::Math::float3 rotation, std::string& result) {
					auto resultMarshaler = Antilatency::InterfaceContract::Details::ArrayOutMarshaler::create(result);
					return (reinterpret_cast<VMT*>(this->_object))->encodePlacement(position, rotation, resultMarshaler);
				}
				Antilatency::InterfaceContract::ExceptionCode createTrackingCotaskConstructor(Antilatency::Alt::Tracking::ITrackingCotaskConstructor& result) {
					return (reinterpret_cast<VMT*>(this->_object))->createTrackingCotaskConstructor(result);
				}
			};
		} //namespace Tracking
	} //namespace Alt
} //namespace Antilatency
namespace Antilatency {
	namespace InterfaceContract {
		namespace Details {
			template<typename Implementer, typename LifeTimeController>
			struct InterfaceRemap<Antilatency::Alt::Tracking::ILibrary, Implementer, LifeTimeController> : Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::InterfaceContract::IInterface, Implementer, LifeTimeController> {
			public:
			    InterfaceRemap() = default;
			    static bool isInterfaceSupported(const Antilatency::InterfaceContract::InterfaceID& id) {
					if (id == Antilatency::Alt::Tracking::ILibrary::VMT::ID()) {
						return true;
					}
					return Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::InterfaceContract::IInterface, Implementer, LifeTimeController>::isInterfaceSupported(id);
				}
			public:
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL createEnvironment(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate code, Antilatency::Alt::Tracking::IEnvironment& result) {
					auto exceptionCode_ = this->_object->createEnvironment(code, result);
					return exceptionCode_;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL createPlacement(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate code, Antilatency::Math::floatP3Q& result) {
					auto exceptionCode_ = this->_object->createPlacement(code, result);
					return exceptionCode_;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL encodePlacement(Antilatency::Math::float3 position, Antilatency::Math::float3 rotation, Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) {
					std::string resultMarshaler;
					auto exceptionCode_ = this->_object->encodePlacement(position, rotation, resultMarshaler);
					result = resultMarshaler;
					return exceptionCode_;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL createTrackingCotaskConstructor(Antilatency::Alt::Tracking::ITrackingCotaskConstructor& result) {
					auto exceptionCode_ = this->_object->createTrackingCotaskConstructor(result);
					return exceptionCode_;
				}
			};
		} //namespace Details
	} //namespace InterfaceContract
} //namespace Antilatency

namespace Antilatency {
	namespace Alt {
		namespace Tracking {
			/* copy and paste this to implementer
			Antilatency::InterfaceContract::ExceptionCode mutate(const std::vector<float>& powers, const std::vector<Antilatency::Math::float3>& rays, float sphereD, const std::vector<Antilatency::Math::float2>& x, const std::vector<Antilatency::Math::float2x3>& xOverPosition, Antilatency::Math::float3 up, Antilatency::InterfaceContract::LongBool& result) {
				return Antilatency::InterfaceContract::ExceptionCode::NotImplemented;
			}
			Antilatency::InterfaceContract::ExceptionCode getUpdateId(int32_t& result) {
				return Antilatency::InterfaceContract::ExceptionCode::NotImplemented;
			}
			*/
			struct IEnvironmentMutable : Antilatency::InterfaceContract::IInterface {
				struct VMT : Antilatency::InterfaceContract::IInterface::VMT {
					virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL mutate(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate powers, Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate rays, float sphereD, Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate x, Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate xOverPosition, Antilatency::Math::float3 up, Antilatency::InterfaceContract::LongBool& result) = 0;
					virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getUpdateId(int32_t& result) = 0;
					static constexpr Antilatency::InterfaceContract::InterfaceID ID() {
						return Antilatency::InterfaceContract::InterfaceID{0xe664544b,0xafd5,0x4723,{0x94,0x9a,0x9a,0x88,0x85,0x26,0xef,0x97}};
					}
				private:
					~VMT() = delete;
				};
				IEnvironmentMutable() = default;
				IEnvironmentMutable(std::nullptr_t) {}
				explicit IEnvironmentMutable(VMT* pointer) : Antilatency::InterfaceContract::IInterface(pointer) {}
				template<typename T, typename = typename std::enable_if<std::is_base_of<IEnvironmentMutable, T>::value>::type>
				IEnvironmentMutable& operator = (const T& other) {
				    Antilatency::InterfaceContract::IInterface::operator=(other);
				    return *this;
				}
				template<class Implementer, class ... TArgs>
				static IEnvironmentMutable create(TArgs&&... args) {
				    return *new Implementer(std::forward<TArgs>(args)...);
				}
				void attach(VMT* other) ANTILATENCY_NOEXCEPT {
				    Antilatency::InterfaceContract::IInterface::attach(other);
				}
				VMT* detach() ANTILATENCY_NOEXCEPT {
				    return reinterpret_cast<VMT*>(Antilatency::InterfaceContract::IInterface::detach());
				}
				Antilatency::InterfaceContract::ExceptionCode mutate(const std::vector<float>& powers, const std::vector<Antilatency::Math::float3>& rays, float sphereD, const std::vector<Antilatency::Math::float2>& x, const std::vector<Antilatency::Math::float2x3>& xOverPosition, Antilatency::Math::float3 up, Antilatency::InterfaceContract::LongBool& result) {
					auto powersMarshaler = Antilatency::InterfaceContract::Details::ArrayInMarshaler::create(powers);
					auto raysMarshaler = Antilatency::InterfaceContract::Details::ArrayInMarshaler::create(rays);
					auto xMarshaler = Antilatency::InterfaceContract::Details::ArrayInMarshaler::create(x);
					auto xOverPositionMarshaler = Antilatency::InterfaceContract::Details::ArrayInMarshaler::create(xOverPosition);
					return (reinterpret_cast<VMT*>(this->_object))->mutate(powersMarshaler, raysMarshaler, sphereD, xMarshaler, xOverPositionMarshaler, up, result);
				}
				Antilatency::InterfaceContract::ExceptionCode getUpdateId(int32_t& result) {
					return (reinterpret_cast<VMT*>(this->_object))->getUpdateId(result);
				}
			};
		} //namespace Tracking
	} //namespace Alt
} //namespace Antilatency
namespace Antilatency {
	namespace InterfaceContract {
		namespace Details {
			template<typename Implementer, typename LifeTimeController>
			struct InterfaceRemap<Antilatency::Alt::Tracking::IEnvironmentMutable, Implementer, LifeTimeController> : Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::InterfaceContract::IInterface, Implementer, LifeTimeController> {
			public:
			    InterfaceRemap() = default;
			    static bool isInterfaceSupported(const Antilatency::InterfaceContract::InterfaceID& id) {
					if (id == Antilatency::Alt::Tracking::IEnvironmentMutable::VMT::ID()) {
						return true;
					}
					return Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::InterfaceContract::IInterface, Implementer, LifeTimeController>::isInterfaceSupported(id);
				}
			public:
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL mutate(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate powers, Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate rays, float sphereD, Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate x, Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate xOverPosition, Antilatency::Math::float3 up, Antilatency::InterfaceContract::LongBool& result) {
					auto exceptionCode_ = this->_object->mutate(powers, rays, sphereD, x, xOverPosition, up, result);
					return exceptionCode_;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getUpdateId(int32_t& result) {
					auto exceptionCode_ = this->_object->getUpdateId(result);
					return exceptionCode_;
				}
			};
		} //namespace Details
	} //namespace InterfaceContract
} //namespace Antilatency

namespace Antilatency {
	namespace Alt {
		namespace Tracking {
			namespace Constants {
				constexpr float DefaultAngularVelocityAvgTime = 0.016f;
			} //namespace Constants
		} //namespace Tracking
	} //namespace Alt
} //namespace Antilatency


#ifdef _MSC_VER
#pragma warning(pop)
#endif

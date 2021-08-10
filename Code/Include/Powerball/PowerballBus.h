
#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace Powerball
{
    class PowerballRequests
    {
    public:
        AZ_RTTI(PowerballRequests, "{3bb8e3b5-4ee7-4009-a629-36699eb77b84}");
        virtual ~PowerballRequests() = default;
        // Put your public methods here
    };
    
    class PowerballBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using PowerballRequestBus = AZ::EBus<PowerballRequests, PowerballBusTraits>;
    using PowerballInterface = AZ::Interface<PowerballRequests>;

} // namespace Powerball

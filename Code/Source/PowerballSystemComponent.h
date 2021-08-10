
#pragma once

#include <AzCore/Component/Component.h>

#include <Powerball/PowerballBus.h>

namespace Powerball
{
    class PowerballSystemComponent
        : public AZ::Component
        , protected PowerballRequestBus::Handler
    {
    public:
        AZ_COMPONENT(PowerballSystemComponent, "{be0d7ffb-546f-4ed3-9062-896a52a34496}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        PowerballSystemComponent();
        ~PowerballSystemComponent();

    protected:
        ////////////////////////////////////////////////////////////////////////
        // PowerballRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    };
}

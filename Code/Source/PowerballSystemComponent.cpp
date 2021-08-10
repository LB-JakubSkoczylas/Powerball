
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/EditContextConstants.inl>

#include "PowerballSystemComponent.h"

namespace Powerball
{
    void PowerballSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<PowerballSystemComponent, AZ::Component>()
                ->Version(0)
                ;

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<PowerballSystemComponent>("Powerball", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System"))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ;
            }
        }
    }

    void PowerballSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC("PowerballService"));
    }

    void PowerballSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC("PowerballService"));
    }

    void PowerballSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void PowerballSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }
    
    PowerballSystemComponent::PowerballSystemComponent()
    {
        if (PowerballInterface::Get() == nullptr)
        {
            PowerballInterface::Register(this);
        }
    }

    PowerballSystemComponent::~PowerballSystemComponent()
    {
        if (PowerballInterface::Get() == this)
        {
            PowerballInterface::Unregister(this);
        }
    }

    void PowerballSystemComponent::Init()
    {
    }

    void PowerballSystemComponent::Activate()
    {
        PowerballRequestBus::Handler::BusConnect();
    }

    void PowerballSystemComponent::Deactivate()
    {
        PowerballRequestBus::Handler::BusDisconnect();
    }
}


#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>

#include "PowerballSystemComponent.h"

namespace Powerball
{
    class PowerballModule
        : public AZ::Module
    {
    public:
        AZ_RTTI(PowerballModule, "{98b5a507-dc74-4170-bdbb-7d8089a1c6ae}", AZ::Module);
        AZ_CLASS_ALLOCATOR(PowerballModule, AZ::SystemAllocator, 0);

        PowerballModule()
            : AZ::Module()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                PowerballSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<PowerballSystemComponent>(),
            };
        }
    };
}// namespace Powerball

AZ_DECLARE_MODULE_CLASS(Gem_Powerball, Powerball::PowerballModule)

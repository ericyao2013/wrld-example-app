// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SenionLabLocationService.h"
#include "InteriorHeightHelpers.h"
#include "EnvironmentFlatteningService.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace SenionLab
    {
        SenionLabLocationService::SenionLabLocationService(Eegeo::Location::ILocationService& defaultLocationService,
                                                           const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                           const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel)
        : m_defaultLocationService(defaultLocationService)
        , m_environmentFlatteningService(environmentFlatteningService)
        , m_interiorInteractionModel(interiorInteractionModel)
        , m_isAuthorized(false)
        , m_latLong(Eegeo::Space::LatLong::FromDegrees(0, 0))
        , m_floorIndex(-1)
        , m_interiorId(Eegeo::Resources::Interiors::InteriorId::NullId())
        {
        }
        
        const bool SenionLabLocationService::GetIsAuthorized() const
        {
            return m_isAuthorized;
        }
        
        bool SenionLabLocationService::IsIndoors()
        {
            return true;
        }
        
        Eegeo::Resources::Interiors::InteriorId SenionLabLocationService::GetInteriorId()
        {
            return m_interiorId.IsValid() ? m_interiorId : m_interiorInteractionModel.GetInteriorModel()->GetId();
        }
        
        bool SenionLabLocationService::GetLocation(Eegeo::Space::LatLong& latLong)
        {
            if(std::abs(m_latLong.GetLatitude()) > 0 || std::abs(m_latLong.GetLongitude()) > 0)
            {
                latLong.SetLatitude(m_latLong.GetLatitude());
                latLong.SetLongitude(m_latLong.GetLongitude());
            }
            else
            {
                m_defaultLocationService.GetLocation(latLong);
            }
            
            return true;
        }
        
        bool SenionLabLocationService::GetAltitude(double& altitude)
        {
            const Eegeo::Resources::Interiors::InteriorsModel* interiorModel = m_interiorInteractionModel.GetInteriorModel();
            if(interiorModel)
            {
                altitude = ExampleApp::Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevelIncludingEnvironmentFlattening(*interiorModel,
                                                                                                                                 m_floorIndex,
                                                                                                                                 m_environmentFlatteningService.GetCurrentScale());
                return true;
            }
            
            return false;
        }
        
        bool SenionLabLocationService::GetFloorIndex(int& floorIndex)
        {
            floorIndex = m_floorIndex;
            return true;
        }
        
        bool SenionLabLocationService::GetHorizontalAccuracy(double& accuracy)
        {
            return false;
        }
        
        bool SenionLabLocationService::GetHeadingDegrees(double& headingDegrees)
        {
            return m_defaultLocationService.GetHeadingDegrees(headingDegrees);
        }
        
        void SenionLabLocationService::StopListening()
        {
        }
        
        void SenionLabLocationService::SetIsAuthorized(bool isAuthorized)
        {
            m_isAuthorized = isAuthorized;
        }
        
        void SenionLabLocationService::SetLocation(Eegeo::Space::LatLong &latLong)
        {
            m_latLong = latLong;
        }
        
        void SenionLabLocationService::SetFloorIndex(int floorIndex)
        {
            m_floorIndex = floorIndex;
        }
        
        void SenionLabLocationService::SetInteriorId(const Eegeo::Resources::Interiors::InteriorId& interiorId)
        {
            m_interiorId = interiorId;
        }
    }
}

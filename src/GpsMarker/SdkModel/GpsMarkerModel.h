// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "ILocationService.h"
#include "VectorMath.h"
#include "BlueSphereModel.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class GpsMarkerModel
            {
            public:
                GpsMarkerModel(Eegeo::Location::ILocationService& locationService,
							   Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                               Eegeo::BlueSphere::BlueSphereModel& blueSphereModel);
                ~GpsMarkerModel();

                bool UpdateGpsPosition(float dt);
                
                const Eegeo::dv3& GetCurrentLocationEcef() const { return m_currentLocationEcef; }
                
                void UpdateHeading(float dt);
                
                void SetEnabled(bool enabled);

                const float GetSphereHeightAboveBase() const;

                bool IsLocationIndoors() const;
                
            private:
                Eegeo::Location::ILocationService& m_locationService;
				Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                Eegeo::BlueSphere::BlueSphereModel& m_blueSphereModel;
                
                Eegeo::dv3 m_currentLocationEcef;
                
                float m_currentHeadingRadians;
                float m_currentHeadingVelocity;

				bool FloorIndexToId(int floorIndex, int& floorId);
			};
        }
    }
}

// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModule.h"
#include "InteriorsExplorerViewModel.h"
#include "InteriorsExplorerModel.h"
#include "InteriorsExitObserver.h"
#include "InteriorsExplorerInputDelegate.h"
#include "InteriorPinModalityObserver.h"
#include "InteriorPinScaleController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorsExplorerModule::InteriorsExplorerModule(Eegeo::Resources::Interiors::InteriorsController& interiorsController,
                                                             Eegeo::Resources::Interiors::Camera::InteriorsCameraController& interiorsCameraController,
                                                             Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                             Eegeo::Resources::Interiors::InteriorSelectionController& interiorSelectionController,
                                                             Eegeo::Resources::Interiors::InteriorsPinsController& interiorsPinsController,
                                                             Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController,
                                                             Eegeo::UI::NativeUIFactories& nativeUIFactories,
                                                             Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                             MapMode::SdkModel::IMapModeModel& mapModeModel,
                                                             ExampleAppMessaging::TMessageBus& messageBus,
                                                             ExampleApp::Metrics::IMetricsService& metricsService)
            {
                m_pModel = Eegeo_NEW(InteriorsExplorerModel)(interiorsController, interiorSelectionModel, mapModeModel, messageBus, metricsService);
                m_pViewModel = Eegeo_NEW(View::InteriorsExplorerViewModel)(false, identityProvider.GetNextIdentity());
                m_pInteriorExitObserver = Eegeo_NEW(InteriorsExitObserver)(interiorsController, interiorSelectionController, globeCameraController, nativeUIFactories);
                m_pInteriorsExplorerInputDelegate = Eegeo_NEW(InteriorsExplorerInputDelegate)(interiorsController, interiorsPinsController, globeCameraController);
                m_pInteriorPinModalityObserver = Eegeo_NEW(InteriorPinModalityObserver)(messageBus);
                m_pInteriorPinScaleController = Eegeo_NEW(InteriorPinScaleController)(interiorsPinsController, messageBus);
            }
            
            InteriorsExplorerModule::~InteriorsExplorerModule()
            {
                Eegeo_DELETE m_pInteriorPinScaleController;
                Eegeo_DELETE m_pInteriorPinModalityObserver;
                Eegeo_DELETE m_pInteriorsExplorerInputDelegate;
                Eegeo_DELETE m_pInteriorExitObserver;
                Eegeo_DELETE m_pModel;
                Eegeo_DELETE m_pViewModel;
            }
            
            View::InteriorsExplorerViewModel& InteriorsExplorerModule::GetInteriorsExplorerViewModel() const
            {
                return *m_pViewModel;
            }
            
            ScreenControl::View::IScreenControlViewModel& InteriorsExplorerModule::GetScreenControlViewModel() const
            {
                return *m_pViewModel;
            }

            IInteriorsExplorerInputDelegate& InteriorsExplorerModule::GetInputDelegate() const
            {
                return *m_pInteriorsExplorerInputDelegate;
            }
        }
    }
}
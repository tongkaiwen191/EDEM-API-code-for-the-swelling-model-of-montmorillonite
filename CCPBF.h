#ifndef CREPLACEPBF_H
#define CREPLACEPBF_H

#include <string>
#pragma warning(disable:4996)

#include "IPluginParticleBodyForceV3_2_0.h"
#include "IParticleManagerApi_1_0.h"

/**
 * This class provides an implementation of IPluginParticleBodyForceV2_2_0
 * That adds and updates a replace flag property to each particle
 * in the system.
 */
class CCPBF : public NApiPbf::IPluginParticleBodyForceV3_2_0
{
public:
    /**
    * Name of replace custom property
    */
	static const std::string VOLADD;
	static const std::string Vnvdeforce;
    static const std::string VOLSTART;
	
    /**
    * Constructor, does nothing
    */
    CCPBF();

    /**
    * Destructor, does nothing
    */
    virtual ~CCPBF();

    /**
    * Returns true to indicate plugin is thread safe
    *
    * Implementation of method from IPluginParticleBodyForceV2_2_0
    */
    virtual bool isThreadSafe();

    /**
    * Returns true to indicate the plugin uses custom properties
    *
    * Implementation of method from IPluginParticleBodyForceV2_2_0
    */
    virtual bool usesCustomProperties();

    /**
    * Implementation of method from IPluginParticleBodyForceV2_2_0
    */
    virtual NApi::ECalculateResult externalForce(
		int 	threadID,
		const NExternalForceTypesV3_0_0::STimeStepData & 	timeStepData,
		const NExternalForceTypesV3_0_0::SParticle & 	particle,
		NApiCore::ICustomPropertyDataApi_1_0 * 	particleCustomProperties,
		NApiCore::ICustomPropertyDataApi_1_0 * 	simulationCustomProperties,
		NExternalForceTypesV3_0_0::SResults & 	results);

    /**
    * Returns 1 to indicate the plugin wishes to register 1 property
    *
    * Implementation of method from IPluginParticleBodyForceV2_2_0
    */
    virtual unsigned int getNumberOfRequiredProperties(
                                const NApi::EPluginPropertyCategory category);

    /**
    * Returns details for our custom properties
    *
    * Implementation of method from IPluginParticleBodyForceV2_2_0
    */
    virtual bool getDetailsForProperty(
                            unsigned int                    propertyIndex,
                            NApi::EPluginPropertyCategory   category,
                            char                            name[NApi::CUSTOM_PROP_MAX_NAME_LENGTH],
                            NApi::EPluginPropertyDataTypes& dataType,
                            unsigned int&                   numberOfElements,
                            NApi::EPluginPropertyUnitTypes& unitType,
                            char                            initValBuff[NApi::BUFF_SIZE]);


    virtual bool starting(NApiCore::IApiManager_1_0& apiManager, int numThreads);

private:
    /** particle manager. */
    NApiCore::IParticleManagerApi_1_0* m_particleMngr;
};

#endif // CREPLACEPBF_H

#include "CCPBF.h"
#include <sstream>
#pragma warning(disable : 4996)

using namespace std;
using namespace NApi;
using namespace NApiCore;
using namespace NApiPbf;

const string CCPBF::VOLADD = "VolumeAdded";
const string CCPBF::VOLSTART = "VolumeAtStart";

CCPBF::CCPBF()
{
	m_particleMngr = nullptr;
}

CCPBF::~CCPBF()
{
    ;
}

bool CCPBF::isThreadSafe()
{
    return true;
}

bool CCPBF::usesCustomProperties()
{
    // Uses custom properties
    return true;
}

bool CCPBF::starting(NApiCore::IApiManager_1_0& apiManager, int numThreads)
{
    m_particleMngr = static_cast<NApiCore::IParticleManagerApi_1_0*>(apiManager.getApi(eParticleManager, 1, 0));
    return true;
}

ECalculateResult CCPBF::externalForce(int 	threadID,
	const NExternalForceTypesV3_0_0::STimeStepData & 	timeStepData,
	const NExternalForceTypesV3_0_0::SParticle & 	particle,
	NApiCore::ICustomPropertyDataApi_1_0 * 	particleCustomProperties,
	NApiCore::ICustomPropertyDataApi_1_0 * 	simulationCustomProperties,
	NExternalForceTypesV3_0_0::SResults & 	results
)
{
	
    const double* m_VolumeAdded  = particleCustomProperties->getValue(VOLADD.c_str());
	const double* m_VolumeOrignal  = particleCustomProperties->getValue(VOLSTART.c_str());

	if (m_VolumeOrignal[0] == 0.0)
	{
		double* m_VolumeOrignalDelta = particleCustomProperties->getDelta(VOLSTART.c_str());
		m_VolumeOrignalDelta[0] += particle.volume;
		double S1 = m_particleMngr->getScale(particle.ID);
		m_VolumeOrignalDelta[1] += pow(S1, 3.0);
	}
	if (m_VolumeAdded[0] > 0.0)
	{
		double* m_VolumeAddedDelta = particleCustomProperties->getDelta(VOLADD.c_str());
		double S2 = (m_VolumeOrignal[0] + m_VolumeAdded[0]) / m_VolumeOrignal[0];
		S2 = S2 * m_VolumeOrignal[1];
		if (S2 != m_VolumeOrignal[1])
		{
			S2 = pow(S2, (1.0 / 3.0));
			m_particleMngr->setScale(particle.ID, S2);
		}
	}







    return eSuccess;
}

unsigned int CCPBF::getNumberOfRequiredProperties(
                                const NApi::EPluginPropertyCategory category)
{
    if (eParticle == category)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

bool CCPBF::getDetailsForProperty(
                         unsigned int                    propertyIndex,
                         NApi::EPluginPropertyCategory   category,
                         char                            name[NApi::CUSTOM_PROP_MAX_NAME_LENGTH],
                         NApi::EPluginPropertyDataTypes& dataType,
                         unsigned int&                   numberOfElements,
                         NApi::EPluginPropertyUnitTypes& unitType,
                         char                            initValBuff[NApi::BUFF_SIZE])
{
    if (0        == propertyIndex &&
        eParticle == category)
    {
        strcpy(name, VOLADD.c_str());
        dataType         = eDouble;
        numberOfElements = 1;
        unitType         = eVolume;
        std::ostringstream oss;
        oss << 0.0;
        strcpy(initValBuff, oss.str().c_str());
        return true;
    }
    if (1        == propertyIndex &&
        eParticle == category)
    {
        strcpy(name, VOLSTART.c_str());
        dataType         = eDouble;
        numberOfElements = 2;
        unitType         = eVolume;
        
        std::ostringstream oss;
        oss << 0.0;
        strcpy(initValBuff, oss.str().c_str());
        return true;
    }
    else
    {
        return false;
    }
}

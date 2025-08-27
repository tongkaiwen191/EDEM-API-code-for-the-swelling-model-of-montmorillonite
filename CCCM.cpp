#include "CCCM.h"
#include <string.h>
#include <sstream>
#include "Helpers.h"
#pragma warning(disable : 4996)

using namespace std;
using namespace NApi;
using namespace NApiCore;
using namespace NApiCm;



const string CCCM::VOLADD = "VolumeAdded";
const string CCCM::PREFS_FILE = "rprefs.txt";
const string CCCM::myVelcoity = "myVelcoity";


CCCM::CCCM()
{
	m_particleMngr = nullptr;
}

CCCM::~CCCM()
{
	;
}
void CCCM::getPreferenceFileName(char prefFileName[FILE_PATH_MAX_LENGTH])
{
	
	strcpy(prefFileName, PREFS_FILE.c_str());
}

bool CCCM::isThreadSafe()
{
	// thread safe
	return true;
}

bool CCCM::usesCustomProperties()
{
	return true;
}
bool CCCM::setup(NApiCore::IApiManager_1_0& apiManager, const char prefFile[], char customMsg[NApi::ERROR_MSG_MAX_LENGTH])
{

	ifstream prefsFile(prefFile);

    if(!prefsFile)
    {
        return false;
    }
    else
    {
        double CriticalVel;
        string str;
        while (prefsFile)
        {
            prefsFile >> str
                      >> CriticalVel;

            string::size_type i (str.find (':'));
            string surfA = str.substr (0, i);
            str.erase (0, i + 1);
            string surfB = str;

            m_vvvv.addgetParticles(surfA,surfB,CriticalVel);
        }
    }

    return true;
}

bool CCCM::starting(NApiCore::IApiManager_1_0& apiManager, int numThreads)
{
	m_particleMngr = static_cast<NApiCore::IParticleManagerApi_1_0*>(apiManager.getApi(eParticleManager, 1, 0));
	return true;
}

void CCCM::stopping(NApiCore::IApiManager_1_0& apiManager)
{
	;
}




ECalculateResult CCCM::calculateForce(
																int          threadId,
																double       time,
																double       timestep,
																int          elem1Id,
																const char   elem1Type[],
																double       elem1Mass,
																double       elem1Density,
																double       elem1Volume,
																unsigned int elem1Surfaces,
																double       elem1MoIX,
																double       elem1MoIY,
																double       elem1MoIZ,
																double       elem1ShearMod,
																double       elem1Poisson,
																double       elem1ContactRadius,
																double       elem1PhysicalRadius,
																double       elem1PosX,
																double       elem1PosY,
																double       elem1PosZ,
																double       elem1ComX,
																double       elem1ComY,
																double       elem1ComZ,
																double       elem1ContactPointVelX,
																double       elem1ContactPointVelY,
																double       elem1ContactPointVelZ,
																double       elem1VelX,
																double       elem1VelY,
																double       elem1VelZ,
																double       elem1AngVelX,
																double       elem1AngVelY,
																double       elem1AngVelZ,
																double       elem1Charge,
																double       elem1WorkFunction,
																const double elem1Orientation[9],
																NApiCore::ICustomPropertyDataApi_1_0* elem1PropData,
																bool         elem2IsSurf,
																int          elem2Id,
																const char   elem2Type[],
																double       elem2Mass,
																double       elem2Density,
																double       elem2Volume,
																unsigned int elem2Surfaces,
																double       elem2MoIX,
																double       elem2MoIY,
																double       elem2MoIZ,
																double       elem2Area,
																double       elem2ShearMod,
																double       elem2Poisson,
																double       elem2ContactRadius,
																double       elem2PhysicalRadius,
																double       elem2PosX,
																double       elem2PosY,
																double       elem2PosZ,
																double       elem2ComX,
																double       elem2ComY,
																double       elem2ComZ,
																double       elem2ContactPointVelX,
																double       elem2ContactPointVelY,
																double       elem2ContactPointVelZ,
																double       elem2VelX,
																double       elem2VelY,
																double       elem2VelZ,
																double       elem2AngVelX,
																double       elem2AngVelY,
																double       elem2AngVelZ,
																double       elem2Charge,
																double       elem2WorkFunction,
																const double elem2Orientation[9],
																NApiCore::ICustomPropertyDataApi_1_0* elem2PropData,
																NApiCore::ICustomPropertyDataApi_1_0* contactPropData,
																NApiCore::ICustomPropertyDataApi_1_0* simulationPropData,
																double       coeffRest,
																double       staticFriction,
																double       rollingFriction,
																double       contactPointX,
																double       contactPointY,
																double       contactPointZ,
																double       normalContactOverlap,
																double       normalPhysicalOverlap,
																double& tangentialPhysicalOverlapX,
																double& tangentialPhysicalOverlapY,
																double& tangentialPhysicalOverlapZ,
																double& calculatedNormalForceX,//法向冲量赋值给法向力
																double& calculatedNormalForceY,
																double& calculatedNormalForceZ,
																double& calculatedUnsymNormalForceX,
																double& calculatedUnsymNormalForceY,
																double& calculatedUnsymNormalForceZ,
																double& calculatedTangentialForceX,//切向冲量赋值给切向力
																double& calculatedTangentialForceY,
																double& calculatedTangentialForceZ,
																double& calculatedUnsymTangentialForceX,
																double& calculatedUnsymTangentialForceY,
																double& calculatedUnsymTangentialForceZ,
																double& calculatedElem1AdditionalTorqueX,
																double& calculatedElem1AdditionalTorqueY,
																double& calculatedElem1AdditionalTorqueZ,
																double& calculatedElem1UnsymAdditionalTorqueX,
																double& calculatedElem1UnsymAdditionalTorqueY,
																double& calculatedElem1UnsymAdditionalTorqueZ,
																double& calculatedElem2AdditionalTorqueX,
																double& calculatedElem2AdditionalTorqueY,
																double& calculatedElem2AdditionalTorqueZ,
																double& calculatedElem2UnsymAdditionalTorqueX,
																double& calculatedElem2UnsymAdditionalTorqueY,
																double& calculatedElem2UnsymAdditionalTorqueZ,
																double& calculatedChargeMovedToElem1) //电荷量)
{
CSimple3DVector relVel = CSimple3DVector(elem1VelX, elem1VelY, elem1VelZ) - CSimple3DVector(elem2VelX, elem2VelY, elem2VelZ);




CSimple3DVector vel1 = CSimple3DVector(elem1VelX, elem1VelY, elem1VelZ);
CSimple3DVector vel2 = CSimple3DVector(elem2VelX, elem2VelY, elem2VelZ);

CSimple3DPoint contactPoint = CSimple3DPoint(contactPointX, contactPointY, contactPointZ);
CSimple3DVector unitCPVect = contactPoint - CSimple3DPoint(elem1PosX, elem1PosY, elem1PosZ);

CSimple3DVector unitCPVectNorm = (CSimple3DPoint(elem1PosX, elem1PosY, elem1PosZ) - CSimple3DPoint(elem2PosX, elem2PosY, elem2PosZ));

unitCPVect.normalise();

//等效质量
double nEquivMass = elem1Mass * elem2Mass /
(elem1Mass + elem2Mass);

calculatedNormalForceX = 0.0;
calculatedNormalForceY = 0.0;
calculatedNormalForceZ = 0.0;
calculatedUnsymNormalForceX = 0.0;
calculatedUnsymNormalForceY = 0.0;
calculatedUnsymNormalForceZ = 0.0;
calculatedTangentialForceX = 0.0;
calculatedTangentialForceY = 0.0;
calculatedTangentialForceZ = 0.0;
calculatedUnsymTangentialForceX = 0.0;
calculatedUnsymTangentialForceY = 0.0;
calculatedUnsymTangentialForceZ = 0.0;
calculatedElem1AdditionalTorqueX = 0.0;
calculatedElem1AdditionalTorqueY = 0.0;
calculatedElem1AdditionalTorqueZ = 0.0;
calculatedElem1UnsymAdditionalTorqueX = 0.0;
calculatedElem1UnsymAdditionalTorqueY = 0.0;
calculatedElem1UnsymAdditionalTorqueZ = 0.0;
calculatedElem2AdditionalTorqueX = 0.0;
calculatedElem2AdditionalTorqueY = 0.0;
calculatedElem2AdditionalTorqueZ = 0.0;
calculatedElem2UnsymAdditionalTorqueX = 0.0;
calculatedElem2UnsymAdditionalTorqueY = 0.0;
calculatedElem2UnsymAdditionalTorqueZ = 0.0;

CSimple3DVector J_n;
CSimple3DVector F_n;

J_n = (unitCPVectNorm * nEquivMass * relVel.length());
//F_n = (unitCPVectNorm * nEquivMass * relVel.length()) / timestep;


calculatedNormalForceX = J_n.dx();
calculatedNormalForceY = J_n.dy();
calculatedNormalForceZ = J_n.dz();
double k0 = 2;
double fw = 0.8;
double thresth = 1000;
double I = 0;
double rx = m_vvvv.getgetParticles(elem1Type, elem2Type);
if ((strcmp(elem2Type, "p1") == 0) && (strcmp(elem1Type, "p2") == 0))
{

	if (elem1Volume >= elem2Volume)
	{

			double I = 10000;

		if (I < thresth) {
			if (rx> elem1PhysicalRadius) {
			
			}
			else {
				rx = elem1PhysicalRadius;
			
			}
			double drx = fw * k0*(rx - elem1PhysicalRadius)*timestep;
			double* m_VolAdd1Delta = elem1PropData->getDelta(VOLADD.c_str());
			m_particleMngr->markForRemoval(elem2Id);
			m_VolAdd1Delta[0] += elem2Volume+abs(drx);
			CSimple3DVector V1 = CSimple3DVector(elem1VelX, elem1VelY, elem1VelZ);
			CSimple3DVector V2 = CSimple3DVector(elem2VelX, elem2VelY, elem2VelZ);
			CSimple3DVector V3 = ((V1 * elem1Mass) + (V2 * elem2Mass)) / (elem1Mass + elem2Mass);
			double v3_x = V3.dx();
			double v3_y = V3.dy();
			double v3_z = V3.dz();
			double vv3 = sqrt(v3_x*v3_x + v3_y * v3_y + v3_z * v3_z);
			double *total_vv3 = elem1PropData->getDelta(myVelcoity.c_str());
			total_vv3[0] += vv3;

		}
	}
	else if (elem1Volume < elem2Volume)
	{

			double I = 2 * elem1PhysicalRadius / (elem2PhysicalRadius * 2 + elem1PhysicalRadius * 2);
		if (I < thresth) {
			if (rx > elem1PhysicalRadius) {

			}
			else {
				rx = elem1PhysicalRadius;

			}
			double drx = fw * k0*(rx - elem1PhysicalRadius)*timestep;
			double* m_VolAdd2Delta = elem2PropData->getDelta(VOLADD.c_str());
			m_particleMngr->markForRemoval(elem1Id);
			m_VolAdd2Delta[0] += elem1Volume+abs(drx);
			CSimple3DVector V1 = CSimple3DVector(elem1VelX, elem1VelY, elem1VelZ);
			CSimple3DVector V2 = CSimple3DVector(elem2VelX, elem2VelY, elem2VelZ);
			CSimple3DVector V3 = ((V1 * elem1Mass) + (V2 * elem2Mass)) / (elem1Mass + elem2Mass);
			double v3_x = V3.dx();
			double v3_y = V3.dy();
			double v3_z = V3.dz();
			double vv3 = sqrt(v3_x*v3_x + v3_y * v3_y + v3_z * v3_z);
			double *total_vv3 = elem2PropData->getDelta(myVelcoity.c_str());
			total_vv3[0] += vv3;

		}
	}




}


    return eSuccess;
}

unsigned int CCCM::getNumberOfRequiredProperties(
                                 const NApi::EPluginPropertyCategory category)
{
    if (eParticle == category)
    {
        return 3;
    }
	else
	{
		return 0;
	}
}

bool CCCM::getDetailsForProperty(
                             unsigned int                    propertyIndex,
                             NApi::EPluginPropertyCategory   category,
                             char                            name[NApi::CUSTOM_PROP_MAX_NAME_LENGTH],
                             NApi::EPluginPropertyDataTypes& dataType,
                             unsigned int&                   numberOfElements,
                             NApi::EPluginPropertyUnitTypes& unitType,
                             char                            initValBuff[NApi::BUFF_SIZE])
{
    if (0 == propertyIndex && eParticle == category)
    {
        strcpy(name, VOLADD.c_str());
        dataType         = eDouble;
        numberOfElements = 1;        
		unitType         = eVolume;
        
        std::ostringstream oss;
        oss << 0;
        strcpy(initValBuff, oss.str().c_str());
        

        return true;
    }

	if (1 == propertyIndex && eParticle == category)
	{
		strcpy(name, myVelcoity.c_str());
		dataType = eDouble;
		numberOfElements = 1;
		unitType =eVelocity ;
		 return true;
	}
    else
    {
        return false;
    }
}
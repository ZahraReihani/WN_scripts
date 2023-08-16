/*
 * uds_usr_datatrans.c
 * datalink get/set calls.
 *
 *  Created on: 12.12.2022
 *  Author: Soha.Wagdy
 */

/* header of standard C - libraries
---------------------------------------------------------------------------*/
    #include <stdio.h>
    #include <string.h>
/* header of project specific types
---------------------------------------------------------------------------*/
    #include "uds_uds.h"
    #include "uds_usr_interface.h"
    #include "uds_usr_datalink.h"
    #include "osal/osalAssert.h"
    #include "gen_define.h"
    #include "iSys/config/bq796xx_iSys_appCfg.h"
    #include "sysutils/productionData.h"
    #include "udsCallbacks/uds_usr_auth/uds_usr_auth.h"
    #include "application/balancing/balancing_manualOverride.h"
    #include "application/powerPath/powerPathRequest.h"
    #include "user/battery/usr_battery_defs.h"

    #include "datalink/storages/interface/storage.h"
    #include "datalink/parameter/parameter.h"
    #include "hvp/datalink/datalink_afe.h"
    #include "datalink/datalink_balancing.h"
    #include "datalink/datalink_battery.h"
    #include "datalink/datalink_errorM.h"
    #include "datalink/datalink_errorAction.h"
    #include "datalink/datalink_observer.h"
    #include "datalink/datalink_systemState.h"
    #include "datalink/datalink_timestamp.h"
    #include "datalink/datalink_xmlConfigVersion.h"
    #include "datalink/datalink_acceleration.h"
    #include "datalink/datalink_adc.h"
    #include "datalink/datalink_batteryCharger.h"
    #include "datalink/datalink_derating.h"
    #include "datalink/datalink_fluidSensor.h"
    #include "datalink/datalink_humidity.h"
    #include "datalink/datalink_powerpath.h"
    #include "datalink/datalink_soc.h"

    #include "common/crc/common_crc.h"
    #include "common/arithmetic/common_minmax.h"
    #include "common/arithmetic/common_sum.h"
    #include "common/arithmetic/common_average.h"

/*---------------------------------------------------------------------------*
 * variable declaration
 *---------------------------------------------------------------------------*/

uds_ReadDataType_t udsReadVar = {0};
bq796xx_iSys_appCfg_t const * pAppCfg;

static RET_T rB00_sysProductionData(uint16_t ID, uint16_t *pDataLen);
static RET_T rB01_softwareVersioning(uint16_t ID, uint16_t *pDataLen);
static RET_T rB02_batteryInfo(uint16_t ID, uint16_t *pDataLen);
static RET_T rB03_sysHistogramData(uint16_t ID, uint16_t *pDataLen);
static RET_T rB04_operatingTime(uint16_t ID, uint16_t *pDataLen);
static RET_T rB05_deviceControl(uint16_t ID, uint16_t *pDataLen);
static RET_T rB06_operatingModes(uint16_t ID, uint16_t *pDataLen);

static RET_T rB0A_batLifetimeData(uint16_t ID, uint16_t *pDataLen);
static RET_T rB0B_packVoltages(uint16_t ID, uint16_t *pDataLen);
static RET_T rB0C_extractSysVoltages(uint16_t ID, uint16_t *pDataLen);
static RET_T rB0D_packTemperatures(uint16_t ID, uint16_t *pDataLen);
static RET_T rB0E_extractTemperatures(uint16_t ID, uint16_t *pDataLen);
static RET_T rB0F_packCurrent(uint16_t ID, uint16_t *pDataLen);

static RET_T rB13_deratingCurrent(uint16_t ID, uint16_t *pDataLen);
static RET_T rB14_powerMaps2s(uint16_t ID, uint16_t *pDataLen);
static RET_T rB15_powerMaps120s(uint16_t ID, uint16_t *pDataLen);
static RET_T rB16_leakyBucket(uint16_t ID, uint16_t *pDataLen);
static RET_T rB17_sox(uint16_t ID, uint16_t *pDataLen);
static RET_T rB18_sensorData(uint16_t ID, uint16_t *pDataLen);

static RET_T rB1D_bmzSpecific(uint16_t ID, uint16_t *pDataLen);
static RET_T rB1E_sysDebugCommands(uint16_t ID, uint16_t *pDataLen);

static RET_T rCF0_modProductionData(uint16_t ID, uint16_t *pDataLen);
static RET_T rD00_moduleInfo(uint16_t ID, uint16_t *pDataLen);
static RET_T rD10_extractModVoltages(uint16_t ID, uint16_t *pDataLen);
static RET_T rD20_moduleVoltStack(uint16_t ID, uint16_t *pDataLen);
static RET_T rD30_cellVoltage(uint16_t ID, uint16_t *pDataLen);
static RET_T rD40_extractModTempr(uint16_t ID, uint16_t *pDataLen);
static RET_T rD50_moduleTemprStack(uint16_t ID, uint16_t *pDataLen);
static RET_T rD60_additionalModuleTempr(uint16_t ID, uint16_t *pDataLen);
static RET_T rD70_cellTemperature(uint16_t ID, uint16_t *pDataLen);
static RET_T rD80_moduleCurrents(uint16_t ID, uint16_t *pDataLen);
static RET_T rD90_moduleBalancing(uint16_t ID, uint16_t *pDataLen);

static RET_T rDB0_moduleSensorData(uint16_t ID, uint16_t *pDataLen);
static RET_T rDC0_moduleEeprom(uint16_t ID, uint16_t *pDataLen);

static RET_T rDE0_bmzModuleSpecific(uint16_t ID, uint16_t *pDataLen);
static RET_T rDF0_modDebugCommands(uint16_t ID, uint16_t *pDataLen);
static RET_T rE00_errorData(uint16_t ID, uint16_t *pDataLen);


static RET_T wB00_sysProductionData(uint16_t ID, uint8_t const * pData, uint16_t dataLen);
static RET_T wB05_deviceControl(uint16_t ID, uint8_t const * pData, uint16_t dataLen);
static RET_T wB1D_bmzSpecific(uint16_t ID, uint8_t const * pData, uint16_t dataLen);
static RET_T wB1E_debugCommands(uint16_t ID, uint8_t const * pData, uint16_t dataLen);

static RET_T wCF0_modProductionData(uint16_t ID, uint8_t const * pData, uint16_t dataLen);
static RET_T wDE0_bmzModuleSpecific(uint16_t ID, uint8_t const * pData, uint16_t dataLen);
static RET_T wDF0_modDebugCommands(uint16_t ID, uint8_t const * pData, uint16_t dataLen);

/*********************************************************************
 * Table to map Write access By DIDs Requests
 *********************************************************************/
const uds_dataWriteTab_t dataWriteFuncTab[] =
{
        /* System level and General Information */
    {UDS_DID_SYS_PRODUCTION_DATA,    wB00_sysProductionData,    progSessionOnly,   allRequiredSecurity},
    {UDS_DID_DEVICE_CONTROL,         wB05_deviceControl,        progSessionOnly,   allRequiredSecurity},
    {UDS_DID_SYS_BMZ_SPECIFIC,       wB1D_bmzSpecific,          requiredSessions,  privSecurityOnly   },
    {UDS_DID_SYS_DEBUG_CMDS,         wB1E_debugCommands,        requiredSessions,  privSecurityOnly   },

    /* Module level and Specific Information */
    {UDS_DID_MOD_PRODUCTION_DATA,    wCF0_modProductionData,    progSessionOnly,   allRequiredSecurity},
    {UDS_DID_MOD_BMZ_SPECIFIC,       wDE0_bmzModuleSpecific,    progSessionOnly,   privSecurityOnly   },
    {UDS_DID_MOD_DEBUG_CMDS,         wDF0_modDebugCommands,     progSessionOnly,   privSecurityOnly   },
};

/*********************************************************************
 * Table to map Read/Write By DIDs Requests
 *********************************************************************/
const uds_dataReadTab_t dataReadFuncTab[] =
{
        /* System level and General Information */
    {UDS_DID_SYS_PRODUCTION_DATA,    rB00_sysProductionData    },
    {UDS_DID_SW_VERSIONING,          rB01_softwareVersioning   },
    {UDS_DID_BATTERY_INFO,           rB02_batteryInfo          },
    {UDS_DID_SYS_EEPROM,             rB03_sysHistogramData     },
    {UDS_DID_OPERATING_TIME,         rB04_operatingTime        },
    {UDS_DID_DEVICE_CONTROL,         rB05_deviceControl        },
    {UDS_DID_OPERATING_MODES,        rB06_operatingModes       },
    {UDS_DID_BATLIFE_DATA,           rB0A_batLifetimeData      },
    {UDS_DID_PACK_VOLTAGES,          rB0B_packVoltages         },
    {UDS_DID_EXTRACT_VOLTAGES,       rB0C_extractSysVoltages   },
    {UDS_DID_PACK_TEMPS,             rB0D_packTemperatures     },
    {UDS_DID_EXTRACT_TEMPS,          rB0E_extractTemperatures  },
    {UDS_DID_PACK_CURRENTS,          rB0F_packCurrent          },
    {UDS_DID_DERATING_CURR,          rB13_deratingCurrent      },
    {UDS_DID_POWER_MAPS_2S,          rB14_powerMaps2s          },
    {UDS_DID_POWER_MAPS_120S,        rB15_powerMaps120s        },
    {UDS_DID_LEAKY_BUCKET,           rB16_leakyBucket          },
    {UDS_DID_SOC_SOH,                rB17_sox                  },
    {UDS_DID_SENSOR_DATA,            rB18_sensorData           },
    {UDS_DID_SYS_BMZ_SPECIFIC,       rB1D_bmzSpecific          },
    {UDS_DID_SYS_DEBUG_CMDS,         rB1E_sysDebugCommands     },

        /* Module level and Specific Information */
    {UDS_DID_MOD_PRODUCTION_DATA,    rCF0_modProductionData    },
    {UDS_DID_MODULE_INFO,            rD00_moduleInfo           },
    {UDS_DID_CELL_VOLTAGE_EXTRACT,   rD10_extractModVoltages   },
    {UDS_DID_CELL_VOLTAGES_STACK,    rD20_moduleVoltStack      },
    {UDS_DID_CELL_VOLTAGE,           rD30_cellVoltage          },
    {UDS_DID_CELL_TEMP_EXTRACT,      rD40_extractModTempr      },
    {UDS_DID_CELL_TEMP_STACK,        rD50_moduleTemprStack     },
    {UDS_DID_ADDITION_MODULE_TEMP,   rD60_additionalModuleTempr},
    {UDS_DID_NTC_CELLTEMP,           rD70_cellTemperature      },
    {UDS_DID_MODULES_CURRENTS,       rD80_moduleCurrents       },
    {UDS_DID_MODULE_BALANCING,       rD90_moduleBalancing      },
    {UDS_DID_MODULE_SENSOR_DATA,     rDB0_moduleSensorData     },
    {UDS_DID_MOD_EEPROM,             rDC0_moduleEeprom         },
    {UDS_DID_MOD_BMZ_SPECIFIC,       rDE0_bmzModuleSpecific    },
    {UDS_DID_MOD_DEBUG_CMDS,         rDF0_modDebugCommands     },
    {UDS_DID_ERROR_DATA,             rE00_errorData            },
};

const uint16_t udsDatalinkReadFunNum = sizeof(dataReadFuncTab)/sizeof(dataReadFuncTab[0]);
const uint16_t udsDatalinkWriteFunNum = sizeof(dataWriteFuncTab)/sizeof(dataWriteFuncTab[0]);
const uint16_t udsDatalinkErrorIdMax = sizeof(udsErrorMappingTab)/sizeof(udsErrorMappingTab[0]);

/*-------------------------------------------------------------------------------------------------------------------*
 *                                           SYSTEM LEVEL DATA
 *-------------------------------------------------------------------------------------------------------------------*/

/*********************************************************************
 * Read System Production Data
 *********************************************************************/
static RET_T rB00_sysProductionData(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal;
    *pDataLen = 4;
    productionData_result_t prodDataGetResult = PRODUCTIONDATA_RESULT_ERROR;

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_SERIALNUMBER_SUPPL:
            prodDataGetResult = productionData_get(PRODUCTIONDATA_ID_SERIALNUMBER, &udsReadVar.uds32BitVar[0]);
            break;
        case UDS_SUB_SERIALNUMBER_WNSTD:
            prodDataGetResult = productionData_get(PRODUCTIONDATA_ID_SERIALNUMBER, &udsReadVar.uds32BitVar[0]); //ToDo: Change to WN serial number when added
            break;
        case UDS_SUB_PRODUCTION_DATE:
            prodDataGetResult = productionData_get(PRODUCTIONDATA_ID_DATE_OF_MANUFACTURE, &udsReadVar.uds32BitVar[0]);
            break;
        case UDS_SUB_MANUFACT_ID:
            prodDataGetResult = productionData_get(PRODUCTIONDATA_ID_VENDOR_ID, &udsReadVar.uds32BitVar[0]);
            break;
        case UDS_SUB_PRODUCT_CODE:
            prodDataGetResult = productionData_get(PRODUCTIONDATA_ID_PRODUCT_CODE, &udsReadVar.uds32BitVar[0]);
            break;
        case UDS_SUB_REVISION_NUMBER:
            prodDataGetResult = productionData_get(PRODUCTIONDATA_ID_REVISION, &udsReadVar.uds32BitVar[0]);
            break;
        case UDS_SUB_ARTICLE_NUMBER:
            prodDataGetResult = productionData_get(PRODUCTIONDATA_ID_ARTICLE_NUMBER, &udsReadVar.uds32BitVar[0]);
            break;
        case UDS_SUB_PLANT_NUMBER:
            prodDataGetResult = productionData_get(PRODUCTIONDATA_ID_PLANTNUMBER, &udsReadVar.uds32BitVar[0]);
            break;
        case UDS_SUB_PROD_LINE_NUMBER:
            prodDataGetResult = productionData_get(PRODUCTIONDATA_ID_PRODLINENUMBER, &udsReadVar.uds32BitVar[0]);
            break;
        default:
            return RET_UDS_NRC_ROOR;
            break;
    }

    if (PRODUCTIONDATA_RESULT_OK != prodDataGetResult)
    {
        retVal = RET_UDS_NRC_FPEORA;
        if(ID == UDS_SUB_MANUFACT_ID)
        {
            udsReadVar.uds32BitVar[0] = 0;
        }
        else if(ID == UDS_SUB_PRODUCT_CODE)
        {
            udsReadVar.uds32BitVar[0] = 5;
        }
        else
        {
            udsReadVar.uds32BitVar[0] = UINT32_MAX;
        }
    }
    else
    {
        retVal = RET_OK;
    }

    return retVal;
}

/*********************************************************************
 * Write System Production Data
 *********************************************************************/
static RET_T wB00_sysProductionData(uint16_t ID, uint8_t const * pData, uint16_t dataLen)
{
    RET_T writeStatus = RET_OK;
    productionData_result_t prodDataGetResult = RET_UDS_NRC_FPEORA;

    if( dataLen > sizeof(uint32_t))
    {
        /* uds incorrectMessageLengthOrInvalidFormat */
        writeStatus = RET_UDS_NRC_IMLOIF;
    }
    else
    {
        uint32_t const value = *(uint32_t const *)pData;

        switch(ID & UDS_MINOR_ID_MASK)
        {
            case UDS_SUB_SERIALNUMBER_SUPPL:
                if(!uds_AuthSysProductionData(PRODUCTIONDATA_ID_SERIALNUMBER, value, &prodDataGetResult))
                {
                    writeStatus = RET_UDS_NRC_SAD;
                }
                break;
            case UDS_SUB_SERIALNUMBER_WNSTD:
                prodDataGetResult = productionData_set(PRODUCTIONDATA_ID_SERIALNUMBER, value);//ToDo: Change to WN serial number when added
                if (PRODUCTIONDATA_RESULT_OK != prodDataGetResult)
                {
                    writeStatus = RET_UDS_NRC_FPEORA;
                }
                break;
            case UDS_SUB_PRODUCTION_DATE:
                if(!uds_AuthSysProductionData(PRODUCTIONDATA_ID_DATE_OF_MANUFACTURE, value, &prodDataGetResult))
                {
                    writeStatus = RET_UDS_NRC_SAD;
                }
                break;
            case UDS_SUB_MANUFACT_ID:
                if(!uds_AuthSysProductionData(PRODUCTIONDATA_ID_VENDOR_ID, value, &prodDataGetResult))
                {
                    writeStatus = RET_UDS_NRC_SAD;
                }
                break;
            case UDS_SUB_PRODUCT_CODE:
                if(!uds_AuthSysProductionData(PRODUCTIONDATA_ID_PRODUCT_CODE, value, &prodDataGetResult))
                {
                    writeStatus = RET_UDS_NRC_SAD;
                }
                break;
            case UDS_SUB_REVISION_NUMBER:
                if(!uds_AuthSysProductionData(PRODUCTIONDATA_ID_REVISION, value, &prodDataGetResult))
                {
                    writeStatus = RET_UDS_NRC_SAD;
                }
                break;
            case UDS_SUB_ARTICLE_NUMBER:
                if(!uds_AuthSysProductionData(PRODUCTIONDATA_ID_ARTICLE_NUMBER, value, &prodDataGetResult))
                {
                    writeStatus = RET_UDS_NRC_SAD;
                }
                break;
            case UDS_SUB_PLANT_NUMBER:
                if(!uds_AuthSysProductionData(PRODUCTIONDATA_ID_PLANTNUMBER, value, &prodDataGetResult))
                {
                    writeStatus = RET_UDS_NRC_SAD;
                }
                break;
            case UDS_SUB_PROD_LINE_NUMBER:
                if(!uds_AuthSysProductionData(PRODUCTIONDATA_ID_PRODLINENUMBER, value, &prodDataGetResult))
                {
                    writeStatus = RET_UDS_NRC_SAD;
                }
                break;
            default:
                return RET_UDS_NRC_ROOR;
                break;
        }
    }

    return writeStatus;
}

/*********************************************************************
 * Read Bootloader/Application Version
 *********************************************************************/
static RET_T rB01_softwareVersioning(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    *pDataLen = 4;
    appConfigBlock_t appConfig = {0};

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_BOOTLOADER_VER:
            udsReadVar.uds32BitVar[0] = bootloader_getBootloaderVersion();
            break;
        case UDS_SUB_APPLICATION_VER:
            appConfig = bootloader_getConfigBlock();
            udsReadVar.uds32BitVar[0] = *(uint32_t const *)&appConfig.swVersion;
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Read Battery Information
 *********************************************************************/
static RET_T rB02_batteryInfo(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_UDS_NRC_SFNS;
    //*pDataLen = 4;

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_CELL_TYPE:
            //ToDo: Set value in udsReadVar when added
            break;
        case UDS_SUB_INSTALLED_ENERGY:
            //ToDo: Set value in udsReadVar when added
            break;
        case UDS_SUB_INSTALLED_CAPACITY:
            //ToDo: Set value in udsReadVar when added
            break;
        case UDS_SUB_STATE_OF_HEALTH:
            //ToDo: Set value in udsReadVar when added
            break;
        case UDS_SUB_TOTAL_ENERGY_THRPUT:
            //ToDo: Set value in udsReadVar when added
            break;
        case UDS_SUB_CONTR_OPEN_LOADCNT:
            //ToDo: Set value in udsReadVar when added
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Read Battery Information
 *********************************************************************/
static RET_T rB03_sysHistogramData(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_UDS_NRC_SFNS;;
    //*pDataLen = 4;

    switch(ID & UDS_MINOR_ID_MASK)
    {
    //ToDo: Add when available
        default:
//            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Read System Tick
 *********************************************************************/
static RET_T rB04_operatingTime(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;

    switch(ID & UDS_MINOR_ID_MASK)
    {

        case UDS_SUB_HAL_TICK:
            udsReadVar.uds32BitVar[0] = dl_timer1ms_getTime();
            *pDataLen = 4;
            break;
        case UDS_SUB_RTC_TIME:
            udsReadVar.uds64BitVar[0] = dl_rtc_getTime();
            *pDataLen = 8;
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * POWERPATH STATE
 *********************************************************************/
static powerpath_state_t powerpath_state(void)
{
    powerpath_state_t co_pps = POWERPATH_NOT_READY;
    powerPathStatus_t const pps = dl_powerPathStatus();
    switch (pps)
    {
        case (POWERPATHSTATUS_DETACHED       ):
            co_pps = POWERPATH_NOT_READY;
            break;
        case (POWERPATHSTATUS_DETACHING      ):
            co_pps = POWERPATH_DETACHING;
            break;
        case (POWERPATHSTATUS_ATTACHING      ):
            co_pps = POWERPATH_ATTACHING;
            break;
        case (POWERPATHSTATUS_MANUAL_OVERRIDE):
            co_pps = POWERPATH_MANUAL_OVERRIDE;
            break;
        case (POWERPATHSTATUS_ATTACHED       ):
        default: /* attached "as default", as it is probably the most dangerous state */
            co_pps = POWERPATH_ATTACHED;
            break;
    }
    return co_pps;
}

/*********************************************************************
 * for requesting system states and relay states
 *********************************************************************/
static RET_T rB05_deviceControl(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    *pDataLen = 1;

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_PLUS_RELAY_STATE:
        case UDS_SUB_MINUS_RELAY_STATE:
        case UDS_SUB_PRE_RELAY_STATE:
            udsReadVar.uds8BitVar[0] = dl_powerRelayStates().relayStates[ID & UDS_MINOR_ID_MASK];
            break;
        case UDS_SUB_OVERALL_RELAY_STATE:
            udsReadVar.uds8BitVar[0] = (uint8_t) powerpath_state();
            break;
        case UDS_SUB_PRECOND_RELAY_STATE:
            udsReadVar.uds8BitVar[0] = dl_powerPathPreconStatus();
            break;
        case UDS_SUB_AFE_STATE:
            udsReadVar.uds8BitVar[0] = dl_afeStatus();
            break;
        case UDS_SUB_SYSTEM_STATE_REQUEST:
            retVal = RET_UDS_NRC_SFNS;
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Write Device States
 *********************************************************************/
static RET_T wB05_deviceControl(uint16_t ID, uint8_t const * pData, uint16_t dataLen)
{
    RET_T writeStatus = RET_OK;

    if( dataLen > sizeof(uint8_t))
    {
        /* uds incorrectMessageLengthOrInvalidFormat */
        writeStatus = RET_UDS_NRC_IMLOIF;
    }
    else
    {
        switch(ID & UDS_MINOR_ID_MASK)
        {
            case UDS_SUB_SYSTEM_STATE_REQUEST:
                switch((uint8_t)(*pData))
                {
                    case 0:
                        systemState_request(SYSTEMSTATE_REQUEST_BOOTLOADER);
                        break;
                    case 1:
                        systemState_request(SYSTEMSTATE_REQUEST_REBOOT);
                        break;
                    default:
                        writeStatus = RET_UDS_NRC_ROOR;
                        break;
                }
                break;
            case UDS_SUB_PLUS_RELAY_STATE:
            case UDS_SUB_MINUS_RELAY_STATE:
            case UDS_SUB_PRE_RELAY_STATE:
            case UDS_SUB_OVERALL_RELAY_STATE:
            case UDS_SUB_PRECOND_RELAY_STATE:
            case UDS_SUB_AFE_STATE:
                writeStatus = RET_UDS_NRC_SFNS;
                break;
            default:
                writeStatus = RET_UDS_NRC_ROOR;
                break;
        }
    }

    return writeStatus;
}

/*********************************************************************
 * Read System States and current highest Error Action
 *********************************************************************/
static RET_T rB06_operatingModes(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    *pDataLen = 1;

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_SYSTEM_STATE:
            udsReadVar.uds8BitVar[0] = (uint8_t) dl_systemState();
            break;
        case UDS_SUB_SYSTEM_TARGET_STATE:
            udsReadVar.uds8BitVar[0] = (uint8_t) dl_systemTargetState();
            break;
        case UDS_SUB_ERROR_ACTION:
            udsReadVar.uds8BitVar[0] = dl_errorAction_get();
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Read Battery Lifetime Data
 *********************************************************************/
static RET_T rB0A_batLifetimeData(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;

    batteryCharger_info_t batteryChargerInfo = dl_batteryCharger_info();

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_RELAY_SWITCHING_UNDER_LOAD: //ToDo: Add for each relay in the future
            udsReadVar.uds32BitVar[0] = dl_getHardDetach();
            *pDataLen = 4;
            break;
        case UDS_SUB_RELAY_TRIP_COUNTER:
            udsReadVar.uds32BitVar[0] = dl_getControlledDetach();
            *pDataLen = 4;
            break;
        case UDS_SUB_BATTERY_LIFETIME_IN_CYCLES:
            udsReadVar.uds16BitVar[0] = dl_batteryCycleCount();
            *pDataLen = 2;
            break;
        case UDS_SUB_BATTERY_CHARGER_STATUS:
            udsReadVar.uds8BitVar[0] = (uint8_t)batteryChargerInfo.chargerOverallStatus;
            udsReadVar.uds8BitVar[1] = (((uint8_t)batteryChargerInfo.chargerStatus[CHARGER_ID_ONBOARD_1])<<0)
                                      |(((uint8_t)batteryChargerInfo.chargerStatus[CHARGER_ID_ONBOARD_2])<<1)
                                      |(((uint8_t)batteryChargerInfo.chargerStatus[CHARGER_ID_ONBOARD_3])<<2)
                                      |(((uint8_t)batteryChargerInfo.chargerStatus[CHARGER_ID_OFFBOARD] )<<3);
            udsReadVar.uds8BitVar[2] = batteryChargerInfo.numberOfConnectedChargers;
            *pDataLen = 1;
            break;
        case UDS_SUB_CHG_DSG_STATE:
            udsReadVar.uds8BitVar[0] = dl_chgDsgStatus();
            *pDataLen = 1;
            break;
        case UDS_SUB_CHG_DSG_PROPOSAL:
            udsReadVar.uds8BitVar[0] = dl_observerPowerPathPropsal();
            *pDataLen = 1;
            break;
        case UDS_SUB_SERVICE_CHG_ENABLED:
            udsReadVar.uds8BitVar[0] = dl_observerServiceChargingEnabled();
            *pDataLen = 1;
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Read voltage in pack
 *********************************************************************/
static RET_T rB0B_packVoltages(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_ALL_VOLT_CHANNELS:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_battery_voltage_mV();
            //udsReadVar.uds32BitVar[1] = (uint32_t)dl_battery_voltage_mV(); //ToDo: add voltage two for cvs when available
            udsReadVar.uds32BitVar[2] = (uint32_t)dl_powerPath_outputVoltage_mV();
            *pDataLen = 12;
            break;
        case UDS_SUB_STACK_VOLTAGE:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_battery_voltage_mV();
            *pDataLen = 4;
            break;
        case UDS_SUB_INTERMEDIATE_VOLTAGE:
            //udsVar.uds32BitVar[0] = (uint32_t)dl_battery_voltage_mV(); //ToDo: add voltage two for cvs when available
            *pDataLen = 4;
            break;
        case UDS_SUB_OUTPUT_VOLTAGE:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_powerPath_outputVoltage_mV();
            *pDataLen = 4;
            break;
        case UDS_SUB_ADC_VOLTAGE:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_VmcuBat_mV();
            *pDataLen = 4;
            break;
        case UDS_SUB_RELAY_FDBK1_VOLTAGE:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_adc_relayFeedbackVoltage1();
            *pDataLen = 4;
            break;
        case UDS_SUB_RELAY_FDBK2_VOLTAGE:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_adc_relayFeedbackVoltage2();
            *pDataLen = 4;
            break;
        case UDS_SUB_RELAY_FDBK3_VOLTAGE:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_adc_relayFeedbackVoltage3();
            *pDataLen = 4;
            break;
        case UDS_SUB_RELAY_FDBK4_VOLTAGE:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_adc_relayFeedbackVoltage4();
            *pDataLen = 4;
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Read voltage Extract
 *********************************************************************/
static RET_T rB0C_extractSysVoltages(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_EXTRACT_MIN_CELLVOLT:
            udsReadVar.uds16BitVar[0] = dl_battery_voltagesExtract().cellVolts.lowestVoltageCellInfo.voltage_mV;
            udsReadVar.uds8BitVar[1]  = dl_battery_voltagesExtract().cellVolts.lowestVoltageCellInfo.cellIdx;
            udsReadVar.uds8BitVar[2]  = dl_battery_voltagesExtract().cellVolts.lowestVoltageCellInfo.moduleIdx_parallel;
            udsReadVar.uds8BitVar[3]  = dl_battery_voltagesExtract().cellVolts.lowestVoltageCellInfo.moduleIdx_serial;
            *pDataLen = 5;
            break;
        case UDS_SUB_EXTRACT_MAX_CELLVOLT:
            udsReadVar.uds16BitVar[0] = dl_battery_voltagesExtract().cellVolts.highestVoltageCellInfo.voltage_mV;
            udsReadVar.uds8BitVar[1]  = dl_battery_voltagesExtract().cellVolts.highestVoltageCellInfo.cellIdx;
            udsReadVar.uds8BitVar[2]  = dl_battery_voltagesExtract().cellVolts.highestVoltageCellInfo.moduleIdx_parallel;
            udsReadVar.uds8BitVar[3]  = dl_battery_voltagesExtract().cellVolts.highestVoltageCellInfo.moduleIdx_serial;
            *pDataLen = 5;
            break;
        case UDS_SUB_EXTRACT_AVG_CELLVOLT:
            udsReadVar.uds16BitVar[0] = dl_battery_voltagesExtract().cellVolts.averagePackCellVoltage_mV;
            *pDataLen = 2;
            break;
        case UDS_SUB_EXTRACT_MAXDIFF_CELLVOLT:
            udsReadVar.uds16BitVar[0] = dl_battery_voltagesExtract().cellVolts.highestVoltageCellInfo.voltage_mV - dl_battery_voltagesExtract().cellVolts.lowestVoltageCellInfo.voltage_mV;
            *pDataLen = 2;
            break;
        case UDS_SUB_EXTRACT_MIN_MODULEVOLT:
            udsReadVar.uds32BitVar[0] = dl_battery_voltagesExtract().moduleVolts.lowestVoltageModuleInfo.moduleVoltage_mV;
            udsReadVar.uds8BitVar[1]  = dl_battery_voltagesExtract().moduleVolts.lowestVoltageModuleInfo.moduleIdx_parallel;
            udsReadVar.uds8BitVar[2]  = dl_battery_voltagesExtract().moduleVolts.lowestVoltageModuleInfo.moduleIdx_serial;
            *pDataLen = 6;
            break;
        case UDS_SUB_EXTRACT_MAX_MODULEVOLT:
            udsReadVar.uds32BitVar[0] = dl_battery_voltagesExtract().moduleVolts.highestVoltageModuleInfo.moduleVoltage_mV;
            udsReadVar.uds8BitVar[1]  = dl_battery_voltagesExtract().moduleVolts.highestVoltageModuleInfo.moduleIdx_parallel;
            udsReadVar.uds8BitVar[2]  = dl_battery_voltagesExtract().moduleVolts.highestVoltageModuleInfo.moduleIdx_serial;
            *pDataLen = 6;
            break;
        case UDS_SUB_EXTRACT_MIN_MODULESTRINGVOLT:
            udsReadVar.uds32BitVar[0] = dl_battery_voltagesExtract().moduleStringPackVolts.lowestVoltageModuleStringInfo.moduleStringVoltage_mV;
            udsReadVar.uds8BitVar[1]  = dl_battery_voltagesExtract().moduleStringPackVolts.lowestVoltageModuleStringInfo.moduleStringIdx_parallel;
            *pDataLen = 5;
            break;
        case UDS_SUB_EXTRACT_MAX_MODULESTRINGVOLT:
            udsReadVar.uds32BitVar[0] = dl_battery_voltagesExtract().moduleStringPackVolts.highestVoltageModuleStringInfo.moduleStringVoltage_mV;
            udsReadVar.uds8BitVar[1]  = dl_battery_voltagesExtract().moduleStringPackVolts.highestVoltageModuleStringInfo.moduleStringIdx_parallel;
            *pDataLen = 5;
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Read voltage in pack
 *********************************************************************/
static RET_T rB0D_packTemperatures(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;

    switch(ID & UDS_MINOR_ID_MASK)
    {
        //ToDo: Add more temperatures in the future when available
        case UDS_SUB_MCU_TEMP:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_mcuTemp_celsius() * 10u;
            *pDataLen = 4;
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Read voltage in pack
 *********************************************************************/
static RET_T rB0E_extractTemperatures(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_EXTRACT_MIN_CELLTEMP:
            udsReadVar.uds16BitVar[0] = (uint16_t)dl_battery_temperaturesExtract().lowestCellTemperatureNtcInfo.temperature_celsiusX10;
            udsReadVar.uds16BitVar[1] = dl_battery_temperaturesExtract().lowestCellTemperatureNtcInfo.ntcIdx;
            udsReadVar.uds16BitVar[2] = dl_battery_temperaturesExtract().lowestCellTemperatureNtcInfo.moduleIdx_parallel;
            udsReadVar.uds16BitVar[3] = dl_battery_temperaturesExtract().lowestCellTemperatureNtcInfo.moduleIdx_serial;
            *pDataLen = 8;
            break;
        case UDS_SUB_EXTRACT_MAX_CELLTEMP:
            udsReadVar.uds16BitVar[0] = (uint16_t)dl_battery_temperaturesExtract().highestCellTemperatureNtcInfo.temperature_celsiusX10;
            udsReadVar.uds16BitVar[1] = dl_battery_temperaturesExtract().highestCellTemperatureNtcInfo.ntcIdx;
            udsReadVar.uds16BitVar[2] = dl_battery_temperaturesExtract().highestCellTemperatureNtcInfo.moduleIdx_parallel;
            udsReadVar.uds16BitVar[3] = dl_battery_temperaturesExtract().highestCellTemperatureNtcInfo.moduleIdx_serial;
            *pDataLen = 8;
            break;
        case UDS_SUB_EXTRACT_MIN_BOARDTEMP:
            udsReadVar.uds16BitVar[0] = (uint16_t)dl_battery_temperaturesExtract().lowestBoardTemperatureNtcInfo.temperature_celsiusX10;
            udsReadVar.uds16BitVar[1] = dl_battery_temperaturesExtract().lowestBoardTemperatureNtcInfo.ntcIdx;
            udsReadVar.uds16BitVar[2] = dl_battery_temperaturesExtract().lowestBoardTemperatureNtcInfo.moduleIdx_parallel;
            udsReadVar.uds16BitVar[3] = dl_battery_temperaturesExtract().lowestBoardTemperatureNtcInfo.moduleIdx_serial;
            *pDataLen = 8;
            break;
        case UDS_SUB_EXTRACT_MAX_BOARDTEMP:
            udsReadVar.uds16BitVar[0] = (uint16_t)dl_battery_temperaturesExtract().highestBoardTemperatureNtcInfo.temperature_celsiusX10;
            udsReadVar.uds16BitVar[1] = dl_battery_temperaturesExtract().highestBoardTemperatureNtcInfo.ntcIdx;
            udsReadVar.uds16BitVar[2] = dl_battery_temperaturesExtract().highestBoardTemperatureNtcInfo.moduleIdx_parallel;
            udsReadVar.uds16BitVar[3] = dl_battery_temperaturesExtract().highestBoardTemperatureNtcInfo.moduleIdx_serial;
            *pDataLen = 8;
            break;
        case UDS_SUB_EXTRACT_AVG_TEMP:
            udsReadVar.uds16BitVar[0] = (uint16_t)dl_battery_temperaturesExtract().averagePackTemperature_celsiusX10;
            *pDataLen = 2;
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Read All module currents in pack
 *********************************************************************/
static void r_moduleCurrents(int32_t * pData)
{
    bq796xx_pack_currents_t const currents = dl_afeCurrents();

    for( uint8_t count = 0; count < USER_BATTERY_DEFS_NUM_BATTERY_MODULES; count++)
    {
        uint8_t parallel = pAppCfg->packConfig.moduleGridPositions[count].parallelCoordinate;
        uint8_t serial = pAppCfg->packConfig.moduleGridPositions[count].serialCoordinate;

        pData[count] = currents.moduleCurrents[parallel][serial].currents_mA[0];
    }
}

/*********************************************************************
 * Read current in pack
 *********************************************************************/
static RET_T rB0F_packCurrent(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    int32_t currArray[USER_BATTERY_DEFS_NUM_BATTERY_MODULES];

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_ALL_CURR_CHANNELS:
            /* Read All current channel in pack (Channel 1 = Main, 2 = Secondary) */
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_battery_current_mA();
            //ToDo: Add second channel reading when available -> udsVar.uds32BitVar[1] = ;
            *pDataLen = 8;
            break;
        case UDS_SUB_MAIN_CURRENT:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_battery_current_mA();
            *pDataLen = 4;
            break;
        case UDS_SUB_SECOND_CURRENT:
            //ToDo: Add second channel reading when available -> udsReadVar.uds32BitVar[0] = ;
            //*pDataLen = 4;
            break;
        case UDS_SUB_ALL_CURR_MODULES:
            r_moduleCurrents(&currArray[0]);
            for( uint8_t count = 0; count < USER_BATTERY_DEFS_NUM_BATTERY_MODULES; count++)
            {
                udsReadVar.uds32BitVar[count] = (uint32_t)currArray[count];
            }
            *pDataLen = USER_BATTERY_DEFS_NUM_BATTERY_MODULES*4;
            break;
        case UDS_SUB_EXTRACT_CURR_MIN:
            r_moduleCurrents(&currArray[0]);
            udsReadVar.uds32BitVar[0] = (uint32_t)common_min_s32(&currArray[0], USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES);
            *pDataLen = 4;
            break;
        case UDS_SUB_EXTRACT_CURR_MAX:
            r_moduleCurrents(&currArray[0]);
            udsReadVar.uds32BitVar[0] = (uint32_t)common_max_s32(&currArray[0], USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES);
            *pDataLen = 4;
            break;
        case UDS_SUB_EXTRACT_CURR_AVG:
            r_moduleCurrents(&currArray[0]);
            udsReadVar.uds32BitVar[0] = (uint32_t)common_avg_s32(&currArray[0], USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES);
            *pDataLen = 4;
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Read derating current data Data
 *********************************************************************/
static RET_T rB13_deratingCurrent(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    *pDataLen = 4;

    switch (ID & UDS_MINOR_ID_MASK)
    {
        case (UDS_SUB_MAXIMUM_CHARGE_CURRENT):
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_charge();
            break;
        case (UDS_SUB_MAXIMUM_DISCHARGE_CURRENT):
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_discharge();
            break;
        case (UDS_SUB_INFO_CHG_LIMIT_BY_USERSOC):
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output().info_chg_domainLimits[DERATING_DOMAIN_SOC];
            break;
        case (UDS_SUB_INFO_CHG_LIMIT_BY_MINTEMP):
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output().info_chg_domainLimits[DERATING_DOMAIN_TEMPSMIN];
            break;
        case (UDS_SUB_INFO_CHG_LIMIT_BY_MAXTEMP):
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output().info_chg_domainLimits[DERATING_DOMAIN_TEMPSMAX];
            break;
        case (UDS_SUB_INFO_CHG_LIMIT_BY_MINVOLT):
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output().info_chg_domainLimits[DERATING_DOMAIN_CELLVOLTSMIN];
            break;
        case (UDS_SUB_INFO_CHG_LIMIT_BY_MAXVOLT):
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output().info_chg_domainLimits[DERATING_DOMAIN_CELLVOLTSMAX];
            break;
        case (UDS_SUB_INFO_DSG_LIMIT_BY_USERSOC):
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output().info_dsg_domainLimits[DERATING_DOMAIN_SOC];
            break;
        case (UDS_SUB_INFO_DSG_LIMIT_BY_MINTEMP):
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output().info_dsg_domainLimits[DERATING_DOMAIN_TEMPSMIN];
            break;
        case (UDS_SUB_INFO_DSG_LIMIT_BY_MAXTEMP):
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output().info_dsg_domainLimits[DERATING_DOMAIN_TEMPSMAX];
            break;
        case (UDS_SUB_INFO_DSG_LIMIT_BY_MINVOLT):
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output().info_dsg_domainLimits[DERATING_DOMAIN_CELLVOLTSMIN];
            break;
        case (UDS_SUB_INFO_DSG_LIMIT_BY_MAXVOLT):
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output().info_dsg_domainLimits[DERATING_DOMAIN_CELLVOLTSMAX];
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Read Power Maps 2s Data
 *********************************************************************/
static RET_T rB14_powerMaps2s(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    *pDataLen = 4;

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_MAXIMUM_CHARGE_CURRENT_POWERMAP_2S:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_charge_powermap_2s();
            break;
        case UDS_SUB_MAXIMUM_DISCHARGE_CURRENT_POWERMAP_2S:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_discharge_powermap_2s();
            break;
        case UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMIN_VOLTSMIN_2s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_chg_domainLimitsFromPowermap2s[DERATING_DOMAIN_POWERMAP_TEMPSMIN_VOLTSMIN_2s];
            break;
        case UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMIN_VOLTSMAX_2s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_chg_domainLimitsFromPowermap2s[DERATING_DOMAIN_POWERMAP_TEMPSMIN_VOLTSMAX_2s];
            break;
        case UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMAX_VOLTSMIN_2s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_chg_domainLimitsFromPowermap2s[DERATING_DOMAIN_POWERMAP_TEMPSMAX_VOLTSMIN_2s];
            break;
        case UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMAX_VOLTSMAX_2s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_chg_domainLimitsFromPowermap2s[DERATING_DOMAIN_POWERMAP_TEMPSMAX_VOLTSMAX_2s];
            break;
        case UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMIN_VOLTSMIN_2s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_dsg_domainLimitsFromPowermap2s[DERATING_DOMAIN_POWERMAP_TEMPSMIN_VOLTSMIN_2s];
            break;
        case UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMIN_VOLTSMAX_2s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_dsg_domainLimitsFromPowermap2s[DERATING_DOMAIN_POWERMAP_TEMPSMIN_VOLTSMAX_2s];
            break;
        case UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMAX_VOLTSMIN_2s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_dsg_domainLimitsFromPowermap2s[DERATING_DOMAIN_POWERMAP_TEMPSMAX_VOLTSMIN_2s];
            break;
        case UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMAX_VOLTSMAX_2s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_dsg_domainLimitsFromPowermap2s[DERATING_DOMAIN_POWERMAP_TEMPSMAX_VOLTSMAX_2s];
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }
    return retVal;
}

/*********************************************************************
 * Read Power Maps 120s Data
 *********************************************************************/
static RET_T rB15_powerMaps120s(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    *pDataLen = 4;

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_MAXIMUM_CHARGE_CURRENT_POWERMAP_120S:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_charge_powermap_120s();
            break;
        case UDS_SUB_MAXIMUM_DISCHARGE_CURRENT_POWERMAP_120S:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_discharge_powermap_120s();
            break;
        case UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMIN_VOLTSMIN_120s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_chg_domainLimitsFromPowermap120s[DERATING_DOMAIN_POWERMAP_TEMPSMIN_VOLTSMIN_120s];
            break;
        case UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMIN_VOLTSMAX_120s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_chg_domainLimitsFromPowermap120s[DERATING_DOMAIN_POWERMAP_TEMPSMIN_VOLTSMAX_120s];
            break;
        case UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMAX_VOLTSMIN_120s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_chg_domainLimitsFromPowermap120s[DERATING_DOMAIN_POWERMAP_TEMPSMAX_VOLTSMIN_120s];
            break;
        case UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMAX_VOLTSMAX_120s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_chg_domainLimitsFromPowermap120s[DERATING_DOMAIN_POWERMAP_TEMPSMAX_VOLTSMAX_120s];
            break;
        case UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMIN_VOLTSMIN_120s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_dsg_domainLimitsFromPowermap120s[DERATING_DOMAIN_POWERMAP_TEMPSMIN_VOLTSMIN_120s];
            break;
        case UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMIN_VOLTSMAX_120s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_dsg_domainLimitsFromPowermap120s[DERATING_DOMAIN_POWERMAP_TEMPSMIN_VOLTSMAX_120s];
            break;
        case UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMAX_VOLTSMIN_120s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_dsg_domainLimitsFromPowermap120s[DERATING_DOMAIN_POWERMAP_TEMPSMAX_VOLTSMIN_120s];
            break;
        case UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMAX_VOLTSMAX_120s:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_derating_output_powermap().info_dsg_domainLimitsFromPowermap120s[DERATING_DOMAIN_POWERMAP_TEMPSMAX_VOLTSMAX_120s];
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }
    return retVal;
}

/*********************************************************************
 * Read Leaky Bucket Data
 *********************************************************************/
static RET_T rB16_leakyBucket(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_UDS_NRC_SFNS;
    //ToDo: Add Leaky Bucket When Available
    return retVal;
}

/*********************************************************************
 * Read SOC and SOH Data
 *********************************************************************/
static RET_T rB17_sox(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    *pDataLen = 2;

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_RAW_SOC:
            udsReadVar.uds16BitVar[0] = dl_rawSoc();
            break;
        case UDS_SUB_USER_SOC:
            udsReadVar.uds16BitVar[0] = dl_userSoc();
            break;
        case UDS_SUB_USER_SOH:
            udsReadVar.uds16BitVar[0] = dl_userSoh();
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Read Sensor Data
 *********************************************************************/
static RET_T rB18_sensorData(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_ACCEL_SENSOR_X:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_getAccelerationData().accelerationX;
            *pDataLen = 4;
            break;
        case UDS_SUB_ACCEL_SENSOR_Y:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_getAccelerationData().accelerationY;
            *pDataLen = 4;
            break;
        case UDS_SUB_ACCEL_SENSOR_Z:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_getAccelerationData().accelerationZ;
            *pDataLen = 4;
            break;
        case UDS_SUB_ACCEL_SENSOR_STAT:
            udsReadVar.uds8BitVar[0] = dl_getAccelerationDataStatus();
            *pDataLen = 1;
            break;
        case UDS_SUB_HUMID_SENSOR_RH:
            udsReadVar.uds8BitVar[0] = dl_humidity_rh();
            *pDataLen = 1;
            break;
        case UDS_SUB_HUMID_SENSOR_TEMP:
            udsReadVar.uds8BitVar[0] = dl_humidity_temp();
            *pDataLen = 1;
            break;
        case UDS_SUB_HUMID_SENSOR_STAT:
            udsReadVar.uds8BitVar[0] = dl_humidity_status();
            *pDataLen = 1;
            break;
        case UDS_SUB_FLUID_SENSOR_STAT:
            udsReadVar.uds32BitVar[0] = dl_fluidSensor_status();
            *pDataLen = 4;
            break;
        case UDS_SUB_FLUID_SENSOR_mV:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_adc_fluidSensor();
            *pDataLen = 4;
            break;
        case UDS_SUB_CVS_SENSOR_ALL:
            udsReadVar.uds32BitVar[0] = (uint32_t)dl_battery_voltage_mV();
            //udsReadVar.uds32BitVar[1] = (uint32_t)dl_battery_voltage_mV(); //ToDo: add voltage two for cvs when available
            udsReadVar.uds32BitVar[2] = (uint32_t)dl_powerPath_outputVoltage_mV();
            udsReadVar.uds32BitVar[3] = (uint32_t)dl_battery_current_mA();
            *pDataLen = 16;
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*-------------------------------------------------------------------------------------------------------------------*
 *                                                    PRIVATE ACCESS
 *-------------------------------------------------------------------------------------------------------------------*/

/*********************************************************************
 * Read BMZ private Authentication State
 *********************************************************************/
static RET_T r_bmzAuthentication(uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;

    udsReadVar.uds8BitVar[0] = (uint8_t)uds_getAuthState();
    *pDataLen = 1;

    return retVal;
}

/*********************************************************************
 * Read BMZ private configuration's Version
 *********************************************************************/
static RET_T r_bmzConfigVersion(uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;

    udsReadVar.uds32BitVar[0] = dl_xmlConfigVersion().uint32;
    *pDataLen = 4;


    return retVal;
}

/*********************************************************************
 * Read BMZ private configurations
 *********************************************************************/
static RET_T r_bmzConfigStorageState(uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;

    dl_parameter_state_t const paramState = dl_parameter_getState(STORAGEM_SELECT_CONFIG);
    dl_parameter_error_t const paramError = dl_parameter_getLastError(STORAGEM_SELECT_CONFIG);

    udsReadVar.uds16BitVar[0] = ((paramError.errnum&0xFF) | ((paramState&0xFF) << 8));
    *pDataLen = 2;

    return retVal;
}

/*********************************************************************
 * Read BMZ private specific data
 *********************************************************************/
static RET_T r_bmzDataStorageState(uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;

    dl_parameter_state_t const paramState = dl_parameter_getState(STORAGEM_SELECT_DATA);
    dl_parameter_error_t const paramError = dl_parameter_getLastError(STORAGEM_SELECT_DATA);

    udsReadVar.uds16BitVar[0] = ((paramError.errnum&0xFF) | ((paramState&0xFF) << 8));
    *pDataLen = 2;

    return retVal;
}

/*********************************************************************
 * Read BMZ private specific data
 *********************************************************************/
static RET_T rB1D_bmzSpecific(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_BMZ_AUTHENTICATE:
            retVal = r_bmzAuthentication(pDataLen);
            break;
        case UDS_SUB_BMZ_CONFIG_VER:
            retVal = r_bmzConfigVersion(pDataLen);
            break;
        case UDS_SUB_BMZ_CONFIGST_STATE:
            retVal = r_bmzConfigStorageState(pDataLen);
            break;
        case UDS_SUB_BMZ_DATAST_STATE:
            retVal = r_bmzDataStorageState(pDataLen);
            break;
        case UDS_SUB_BMZ_SPECIFIC_REQ:
        case UDS_SUB_BMZ_CLEAR_ERROR_BY_IDX:
        case UDS_SUB_BMZ_CLEAR_ERROR_ALL:
            retVal = RET_UDS_NRC_SFNS;
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Request BMZ private Authentication
 *********************************************************************/
static RET_T w_bmzAuthentication(uint32_t const value, uint16_t const dataLen)
{
    RET_T writeStatus = RET_OK;
    uint32_t serialNumber = 0;
    uint32_t calculatedCrc = 0;

    (void)productionData_get(PRODUCTIONDATA_ID_SERIALNUMBER, &serialNumber);

    if( dataLen > sizeof(uint32_t))
    {
        writeStatus = RET_UDS_NRC_IMLOIF;
    }
    else
    {
        calculatedCrc = crc32((uint8_t const *)&serialNumber, sizeof(uint32_t), START_VALUE);
        if(value == calculatedCrc)
        {
            uds_setAuthState(AUTHORIZED);
            writeStatus = RET_OK;
        }
        else
        {
            uds_setAuthState(UNAUTHORIZED);
            writeStatus = RET_UDS_NRC_IK;
        }
    }

    return writeStatus;
}

/*********************************************************************
 * Write BMZ private specific data (erase storage)
 *********************************************************************/
static RET_T w_bmzSpecificRequest(uint32_t const value, uint16_t const dataLen)
{
    if(!(uint8_t)uds_getAuthState())
    {
        return RET_UDS_NRC_SAD;
    }

    if( dataLen > sizeof(uint8_t))
    {
        return RET_UDS_NRC_IMLOIF;
    }

    switch((uint8_t)value)
    {
    case UDS_SUB_CONFIG_ERASE:
        if(DL_STORAGE_RESULT_OK == dl_storages_erase_blocking(STORAGEM_SELECT_CONFIG)){
        }
        break;
    case UDS_SUB_DATA_ERASE:
        if(DL_STORAGE_RESULT_OK == dl_storages_erase_blocking(STORAGEM_SELECT_DATA)){
        }
        break;
    default:
        /* Do Nothing */
        break;
    }

    return RET_OK;
}

/*********************************************************************
 * Write BMZ private specific data (Clear error flag by error index)
 *********************************************************************/
static RET_T w_bmzClearErrorByIdx(uint32_t const value, uint16_t const dataLen)
{
    if(!(uint8_t)uds_getAuthState())
    {
        return RET_UDS_NRC_SAD;
    }

    if( dataLen > sizeof(uint32_t))
    {
        return RET_UDS_NRC_IMLOIF;
    }

    uds_AuthErrorManagerRequest_clearErrorByIdx(value);
    return RET_OK;
}

/*********************************************************************
 * Write BMZ private specific data (Clear all error flags)
 *********************************************************************/
static RET_T w_bmzClearErrorAll(uint32_t const value, uint16_t const dataLen)
{
    if(!(uint8_t)uds_getAuthState())
    {
        return RET_UDS_NRC_SAD;
    }

    if( dataLen > sizeof(uint32_t))
    {
        return RET_UDS_NRC_IMLOIF;
    }

    bool const clearErrorReq = (bool)value;
    if (clearErrorReq == false)
    {
        return RET_UDS_NRC_GR;
    }
    else
    {
        uds_AuthErrorManagerRequest_clearErrorAll();
        return RET_OK;
    }
}

/*********************************************************************
 * Write BMZ private specific data (Clear error flag)
 *********************************************************************/
static RET_T wB1D_bmzSpecific(uint16_t ID, uint8_t const * pData, uint16_t dataLen)
{
    RET_T writeStatus = RET_OK;

    if (dataLen > sizeof(uint32_t))
    {
        /* uds incorrectMessageLengthOrInvalidFormat */
        writeStatus = RET_UDS_NRC_IMLOIF;
    }
    else
    {
        uint32_t const value = *(uint32_t const *)pData;

        switch(ID & UDS_MINOR_ID_MASK)
        {
            case UDS_SUB_BMZ_AUTHENTICATE:
                writeStatus = w_bmzAuthentication(value, dataLen);
                break;
            case UDS_SUB_BMZ_SPECIFIC_REQ:
                writeStatus = w_bmzSpecificRequest(value, dataLen);
                break;
            case UDS_SUB_BMZ_CLEAR_ERROR_BY_IDX:
                writeStatus = w_bmzClearErrorByIdx(value, dataLen);
                break;
            case UDS_SUB_BMZ_CLEAR_ERROR_ALL:
                writeStatus = w_bmzClearErrorAll(value, dataLen);
                break;
            case UDS_SUB_BMZ_CONFIG_VER:
            case UDS_SUB_BMZ_CONFIGST_STATE:
            case UDS_SUB_BMZ_DATAST_STATE:
                writeStatus = RET_UDS_NRC_SFNS;
                break;
            default:
                writeStatus = RET_UDS_NRC_ROOR;
                break;
        }
    }

    return writeStatus;
}

/*********************************************************************
 * Read Debugging Commands Data
 *********************************************************************/
static RET_T rB1E_sysDebugCommands(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_OVERRIDE_BALANCING:
            udsReadVar.uds8BitVar[0] = (uint8_t)dl_balancingManualOverrideState();
            *pDataLen = 1;
            break;
        case UDS_SUB_POWERPATH_STAT_REQ:
        case UDS_SUB_SERVICE_CHARGING:
            retVal = RET_UDS_NRC_SFNS;
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Write Debugging Commands Data
 *********************************************************************/
static RET_T wB1E_debugCommands(uint16_t ID, uint8_t const * pData, uint16_t dataLen)
{
    RET_T writeStatus = RET_OK;

    if( (*pData) > sizeof(bool))
    {
        /* uds incorrectMessageLengthOrInvalidFormat */
        return RET_UDS_NRC_IMLOIF;
    }

    switch(ID & UDS_MINOR_ID_MASK)
    {
        case UDS_SUB_POWERPATH_STAT_REQ:
            powerPathRequest((powerPathRequest_t)(*pData));
            break;
        case UDS_SUB_SERVICE_CHARGING:
            if(!uds_AuthObserverRequest_serviceCharging((bool)(*pData)))
            {
                writeStatus = RET_UDS_NRC_SAD;
            }
            break;
        case UDS_SUB_OVERRIDE_BALANCING:
            balancing_manualOverride_setState((bool)(*pData));
            break;
        default:
            writeStatus = RET_UDS_NRC_ROOR;
            break;
    }

    return writeStatus;
}

/*-------------------------------------------------------------------------------------------------------------------*
 *                                     PRIVATE ACCESS END - SYSTEM LEVEL DATA END
 *-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*
 *                                               MODULE LEVEL DATA
 *-------------------------------------------------------------------------------------------------------------------*/

/*********************************************************************
 * Read Module Production Data
 *********************************************************************/
static RET_T rCF0_modProductionData(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    //*pDataLen = 4;
    productionData_result_t prodDataGetResult = PRODUCTIONDATA_RESULT_ERROR;

    switch(ID & UDS_MINOR_ID_MASK)
    {
    //ToDo: Add when available
        case UDS_SUB_PRODDATA_MOD1:
            break;
        default:
            return RET_UDS_NRC_ROOR;
            break;
    }

    if (PRODUCTIONDATA_RESULT_OK != prodDataGetResult)
    {
        retVal = RET_UDS_NRC_FPEORA;
    }

    return retVal;
}

/*********************************************************************
 * Write Module Production Data
 *********************************************************************/
static RET_T wCF0_modProductionData(uint16_t ID, uint8_t const * pData, uint16_t dataLen)
{
    RET_T writeStatus = RET_OK;
    productionData_result_t prodDataGetResult = PRODUCTIONDATA_RESULT_OK;

    if( dataLen > sizeof(uint32_t))
    {
        /* uds incorrectMessageLengthOrInvalidFormat */
        writeStatus = RET_UDS_NRC_IMLOIF;
    }
    else
    {
        switch(ID & UDS_MINOR_ID_MASK)
        {
        //ToDo: Add when available
            case UDS_SUB_PRODDATA_MOD1:
                break;
            default:
                return RET_UDS_NRC_ROOR;
                break;
        }

        if (PRODUCTIONDATA_RESULT_OK != prodDataGetResult)
        {
            writeStatus = RET_UDS_NRC_FPEORA;
        }
    }

    return writeStatus;
}

/*********************************************************************
 * Read Module Information
 *********************************************************************/
static RET_T rD00_moduleInfo(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_UDS_NRC_SFNS;
    uint8_t moduleId = (ID & 0x00F0) >> 4;
    //uint8_t reqId = ID & UDS_MINOR_ID_MASK;
    //*pDataLen = 4;

    switch(moduleId)
    {
    //ToDo: Add data when available
        default:
//            return RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Read voltage Extracts from Modules
 *********************************************************************/
static RET_T rD10_extractModVoltages(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    uint8_t moduleId = (ID & 0x00F0) >> 4;
    uint8_t reqId = ID & UDS_MINOR_ID_MASK;

    if(moduleId >= USER_BATTERY_DEFS_NUM_BATTERY_MODULES)
    {
        retVal = RET_UDS_NRC_ROOR;
    }
    else
    {
        uint8_t parallel = pAppCfg->packConfig.moduleGridPositions[moduleId].parallelCoordinate;
        uint8_t serial = pAppCfg->packConfig.moduleGridPositions[moduleId].serialCoordinate;
        bq796xx_module_voltages_t const volts = dl_afeCellVolts().moduleVoltages[parallel][serial];

        switch(reqId)
        {
            case UDS_SUB_MOD_EXTRACT_MIN_CELLVOLT:
                udsReadVar.uds16BitVar[0] = common_min_u16(&volts.cellVoltages[0], USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES);
                *pDataLen = 2;
                break;
            case UDS_SUB_MOD_EXTRACT_MAX_CELLVOLT:
                udsReadVar.uds16BitVar[0] = common_max_u16(&volts.cellVoltages[0], USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES);
                *pDataLen = 2;
                break;
            case UDS_SUB_MOD_EXTRACT_AVG_CELLVOLT:
                udsReadVar.uds16BitVar[0] = common_avg_u16(&volts.cellVoltages[0], USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES);
                *pDataLen = 2;
                break;
            case UDS_SUB_MOD_EXTRACT_MAXDIFF_CELLVOLT:
                udsReadVar.uds16BitVar[0] = common_max_u16(&volts.cellVoltages[0], USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES) -
                common_min_u16(&volts.cellVoltages[0], USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES);
                *pDataLen = 2;
                break;
            case UDS_SUB_MOD_EXTRACT_SUM_CELLVOLT:
                udsReadVar.uds32BitVar[0] = common_sum_u16(&volts.cellVoltages[0], USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES);
                *pDataLen = 4;
                break;
            default:
                retVal = RET_UDS_NRC_ROOR;
                break;
        }
    }

    return retVal;
}

/*********************************************************************
 * Read All cell voltages in a certain module
 *********************************************************************/
static RET_T rD20_moduleVoltStack(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    uint8_t moduleId = ID & UDS_MINOR_ID_MASK;

    if(moduleId >= USER_BATTERY_DEFS_NUM_BATTERY_MODULES)
    {
        retVal = RET_UDS_NRC_ROOR;
    }
    else
    {
        uint8_t parallel = pAppCfg->packConfig.moduleGridPositions[moduleId].parallelCoordinate;
        uint8_t serial = pAppCfg->packConfig.moduleGridPositions[moduleId].serialCoordinate;
        bq796xx_module_voltages_t const volts = dl_afeCellVolts().moduleVoltages[parallel][serial];

        for( uint8_t count = 0; count < USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES; count++)
        {
            udsReadVar.uds16BitVar[count] = volts.cellVoltages[count];
        }

        *pDataLen = USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES * 2;
        retVal = RET_OK;
    }

    return retVal;
}

/*********************************************************************
 * Read one cell voltage in a certain module
 *********************************************************************/
static RET_T rD30_cellVoltage(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    *pDataLen = 2;

    uint8_t moduleId = (ID & 0x00F0) >> 4;
    uint8_t cellId = ID & UDS_MINOR_ID_MASK;

    if( (moduleId >= USER_BATTERY_DEFS_NUM_BATTERY_MODULES) || (cellId >= USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES) )
    {
        retVal = RET_UDS_NRC_ROOR;
    }
    else
    {
        uint8_t parallel = pAppCfg->packConfig.moduleGridPositions[moduleId].parallelCoordinate;
        uint8_t serial = pAppCfg->packConfig.moduleGridPositions[moduleId].serialCoordinate;
        bq796xx_module_voltages_t const volts = dl_afeCellVolts().moduleVoltages[parallel][serial];
        udsReadVar.uds16BitVar[0] = volts.cellVoltages[cellId];
    }

    return retVal;
}

/*********************************************************************
 * Read Temperature Extracts from a Module
 *********************************************************************/
static RET_T rD40_extractModTempr(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    uint8_t moduleId = (ID & 0x00F0) >> 4;
    uint8_t reqId = ID & UDS_MINOR_ID_MASK;
    *pDataLen = 2;

    if(moduleId >= USER_BATTERY_DEFS_NUM_BATTERY_MODULES)
    {
        retVal = RET_UDS_NRC_ROOR;
    }
    else
    {
        uint8_t parallel = pAppCfg->packConfig.moduleGridPositions[moduleId].parallelCoordinate;
        uint8_t serial = pAppCfg->packConfig.moduleGridPositions[moduleId].serialCoordinate;
        bq796xx_module_temperatures_t const tempers = dl_afeTemperatures().moduleTemperatures[parallel][serial];

        switch(reqId)
        {
            case UDS_SUB_MOD_EXTRACT_MIN_TEMP:
                udsReadVar.uds16BitVar[0] = (uint16_t)common_min_s16(&tempers.cellNtcValues_celsius_x10[0], USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES);
                break;
            case UDS_SUB_MOD_EXTRACT_MAX_TEMP:
                udsReadVar.uds16BitVar[0] = (uint16_t)common_max_s16(&tempers.cellNtcValues_celsius_x10[0], USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES);
                break;
            case UDS_SUB_MOD_EXTRACT_AVG_TEMP:
                udsReadVar.uds16BitVar[0] = (uint16_t)common_avg_s16(&tempers.cellNtcValues_celsius_x10[0], USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES);
                break;
            case UDS_SUB_MOD_EXTRACT_MAXDIFF_TEMP:
                udsReadVar.uds16BitVar[0] = (uint16_t)(common_max_s16(&tempers.cellNtcValues_celsius_x10[0], USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES) -
                common_min_s16(&tempers.cellNtcValues_celsius_x10[0], USER_BATTERY_DEFS_NUM_BATTERY_CELLS_IN_SERIES));
                break;
            default:
                retVal = RET_UDS_NRC_ROOR;
                break;
        }
    }

    return retVal;
}

/*********************************************************************
 * Read All cell Temperatures in a certain module
 *********************************************************************/
static RET_T rD50_moduleTemprStack(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    uint8_t moduleId = ID & UDS_MINOR_ID_MASK;

    if(moduleId >= USER_BATTERY_DEFS_NUM_BATTERY_MODULES)
    {
        retVal = RET_UDS_NRC_ROOR;
    }
    else
    {
        uint8_t parallel = pAppCfg->packConfig.moduleGridPositions[moduleId].parallelCoordinate;
        uint8_t serial = pAppCfg->packConfig.moduleGridPositions[moduleId].serialCoordinate;
        bq796xx_module_temperatures_t const tempers = dl_afeTemperatures().moduleTemperatures[parallel][serial];

        for( uint8_t count = 0; count < BQ796XX_CELL_NTC_COUNT_PER_MODULE; count++)
        {
            udsReadVar.uds16BitVar[count] = (uint16_t)tempers.cellNtcValues_celsius_x10[count];
        }

        *pDataLen = BQ796XX_CELL_NTC_COUNT_PER_MODULE * 2;
        retVal = RET_OK;
    }

    return retVal;
}

/*********************************************************************
 * Read additional temperature values in a certain module
 *********************************************************************/
static RET_T rD60_additionalModuleTempr(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    uint8_t moduleId = (ID & 0x00F0) >> 4;
    uint8_t subFunction= ID & UDS_MINOR_ID_MASK;

    if(moduleId >= USER_BATTERY_DEFS_NUM_BATTERY_MODULES)
    {
        retVal = RET_UDS_NRC_ROOR;
    }
    else
    {
        uint8_t parallel = pAppCfg->packConfig.moduleGridPositions[moduleId].parallelCoordinate;
        uint8_t serial = pAppCfg->packConfig.moduleGridPositions[moduleId].serialCoordinate;
        bq796xx_module_temperatures_t const tempers = dl_afeTemperatures().moduleTemperatures[parallel][serial];

        switch(subFunction)
        {
        case UDS_SUB_DEVICE_ALL_TEMP:
            for( uint8_t count = 0; count < BQ796XX_DIETEMPCOUNT_PER_MODULE; count++)
            {
                udsReadVar.uds16BitVar[count] = (uint16_t)tempers.dieTemperatures_celsius_x10[count];
            }
            *pDataLen = BQ796XX_DIETEMPCOUNT_PER_MODULE * 2;
            retVal = RET_OK;
            break;
        case UDS_SUB_DEVICE_NTC_TEMP:
        case UDS_SUB_DEVICE_NTC_TEMP+1:
        case UDS_SUB_DEVICE_NTC_TEMP+2:
        case UDS_SUB_DEVICE_NTC_TEMP+3:
            if(subFunction-UDS_SUB_DEVICE_NTC_TEMP < BQ796XX_DIETEMPCOUNT_PER_MODULE)
            {
                udsReadVar.uds16BitVar[0] = (uint16_t)tempers.dieTemperatures_celsius_x10[subFunction-UDS_SUB_DEVICE_NTC_TEMP];
                *pDataLen = 2;
                retVal = RET_OK;
            }
            else
            {
                retVal = RET_UDS_NRC_ROOR;
            }
            break;
        case UDS_SUB_BOARD_ALL_TEMP:
            for( uint8_t count = 0; count < BQ796XX_BOARD_NTC_COUNT_PER_MODULE; count++)
            {
                udsReadVar.uds16BitVar[count] = (uint16_t)tempers.boardNtcValues_celsius_x10[count];
            }
            *pDataLen = BQ796XX_BOARD_NTC_COUNT_PER_MODULE * 2;
            retVal = RET_OK;
            break;
        case UDS_SUB_BOARD_NTC_TEMP:
        case UDS_SUB_BOARD_NTC_TEMP+1:
        case UDS_SUB_BOARD_NTC_TEMP+2:
        case UDS_SUB_BOARD_NTC_TEMP+3:
        case UDS_SUB_BOARD_NTC_TEMP+4:
        case UDS_SUB_BOARD_NTC_TEMP+5:
        case UDS_SUB_BOARD_NTC_TEMP+6:
        case UDS_SUB_BOARD_NTC_TEMP+7:
        case UDS_SUB_BOARD_NTC_TEMP+8:
        case UDS_SUB_BOARD_NTC_TEMP+9:
            if(subFunction-UDS_SUB_BOARD_NTC_TEMP < BQ796XX_BOARD_NTC_COUNT_PER_MODULE)
            {
                udsReadVar.uds16BitVar[0] = (uint16_t)tempers.boardNtcValues_celsius_x10[subFunction-UDS_SUB_BOARD_NTC_TEMP];
                *pDataLen = 2;
                retVal = RET_OK;
            }
            else
            {
                retVal = RET_UDS_NRC_ROOR;
            }
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
        }
    }

    return retVal;
}

/*********************************************************************
 * Read one NTC cell temperature in a certain module
 *********************************************************************/
static RET_T rD70_cellTemperature(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    *pDataLen = 2;

    uint8_t moduleId = (ID & 0x00F0) >> 4;
    uint8_t ntcId = ID & UDS_MINOR_ID_MASK;

    if( (moduleId >= USER_BATTERY_DEFS_NUM_BATTERY_MODULES) || (ntcId >= BQ796XX_CELL_NTC_COUNT_PER_MODULE) )
    {
        retVal = RET_UDS_NRC_ROOR;
    }
    else
    {
        uint8_t parallel = pAppCfg->packConfig.moduleGridPositions[moduleId].parallelCoordinate;
        uint8_t serial = pAppCfg->packConfig.moduleGridPositions[moduleId].serialCoordinate;
        bq796xx_module_temperatures_t const tempers = dl_afeTemperatures().moduleTemperatures[parallel][serial];
        udsReadVar.uds16BitVar[0] = (uint16_t)tempers.cellNtcValues_celsius_x10[ntcId];
    }

    return retVal;
}

/*********************************************************************
 * Read one module currents in pack
 *********************************************************************/
static RET_T rD80_moduleCurrents(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    *pDataLen = 4;
    uint8_t moduleId = ID & UDS_MINOR_ID_MASK;

    if(moduleId >= USER_BATTERY_DEFS_NUM_BATTERY_MODULES)
    {
        retVal = RET_UDS_NRC_ROOR;
    }
    else
    {
        uint8_t parallel = pAppCfg->packConfig.moduleGridPositions[moduleId].parallelCoordinate;
        uint8_t serial = pAppCfg->packConfig.moduleGridPositions[moduleId].serialCoordinate;
        bq796xx_pack_currents_t const currents = dl_afeCurrents();
        udsReadVar.uds32BitVar[0] = (uint32_t)currents.moduleCurrents[parallel][serial].currents_mA[0];
    }
    return retVal;
}

/*********************************************************************
 * Calculate balancing masks to be read
 *********************************************************************/
static uint16_t r_balancingMasks(uint8_t req, uint8_t parallel, uint8_t serial, bool overrideSt, balancingPreConditionFlags_t preCondition)
{
    struct balancingBitMask_t
    {
        uint32_t alignmentDummy;
        uint8_t balancingBitMask_beforePowerLoss[sizeof(uint64_t)];
        uint8_t balancingBitMask_afterPowerLoss[sizeof(uint64_t)];
        uint8_t balancingBitMask_final[sizeof(uint64_t)];
    } bMask = {};

    uint8_t numBytes = ((BALANCING_NUM_CELLS_PER_MODULE/8u)+1u);
    balancingModuleCellEnableMask_t const mask_beforePowerLoss = dl_balancingMask_beforePowerLossLimitation(parallel,serial);
    balancingModuleCellEnableMask_t const mask_afterPowerLoss = dl_balancingMask_afterPowerLossLimitation(parallel,serial);

    for(uint8_t cell = 0; cell < BALANCING_NUM_CELLS_PER_MODULE; cell++)
    {
        uint8_t bitPos = cell % 8u;
        uint8_t bytePos = cell / 8u;
        bMask.balancingBitMask_beforePowerLoss[bytePos] |= ((mask_beforePowerLoss.balancingEnable[cell]) << bitPos);
        bMask.balancingBitMask_afterPowerLoss[bytePos] |= ((mask_afterPowerLoss.balancingEnable[cell]) << bitPos);
        if ((BALANCING_PRECOND_OK == preCondition) || (overrideSt))
        {
            bMask.balancingBitMask_final[bytePos] = bMask.balancingBitMask_afterPowerLoss[bytePos];
        }
    }

    for( uint8_t count = 0; count < numBytes; count++)
    {
        if( req == UDS_SUB_BALANCING_BIT_MASK)
        {
            udsReadVar.uds8BitVar[count] = bMask.balancingBitMask_final[count];
        }
        else if( req == UDS_SUB_BAL_BIT_MASK_BEFORE_POWERLOSS)
        {
            udsReadVar.uds8BitVar[count] = bMask.balancingBitMask_beforePowerLoss[count];
        }
        else if( req == UDS_SUB_BAL_BIT_MASK_AFTER_POWERLOSS)
        {
            udsReadVar.uds8BitVar[count] = bMask.balancingBitMask_afterPowerLoss[count];
        }
        else{ /* Impossible State */ }
    }

    return numBytes;
}

/*********************************************************************
 * Read Module Balancing Values
 *********************************************************************/
static RET_T rD90_moduleBalancing(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    uint8_t subFunction = (ID & 0x00F0) >> 4;
    uint8_t moduleId = ID & UDS_MINOR_ID_MASK;

    if(moduleId >= USER_BATTERY_DEFS_NUM_BATTERY_MODULES)
    {
        retVal = RET_UDS_NRC_ROOR;
    }
    else
    {
        uint8_t parallel = pAppCfg->packConfig.moduleGridPositions[moduleId].parallelCoordinate;
        uint8_t serial = pAppCfg->packConfig.moduleGridPositions[moduleId].serialCoordinate;
        bool const manualOverrideEnabled = dl_balancingManualOverrideState();
        balancingPreConditionFlags_t const preconds = dl_balancingPreConds(parallel,serial);
        bq796xx_module_cellBalancing_states_t const cbstates = dl_afeCellBalancingStates().moduleBalStates[parallel][serial];

        switch(subFunction)
        {
            case  UDS_SUB_MODULE_PRECOND:
                udsReadVar.uds16BitVar[0] = (uint16_t)preconds;
                *pDataLen = 2;
                break;

            case UDS_SUB_MODULE_BAL_STATUS_ALL:
                for( uint8_t count = 0; count < BALANCING_NUM_CELLS_PER_MODULE; count++)
                {
                    udsReadVar.uds8BitVar[count] = cbstates.cellBalState[count];
                }
                *pDataLen = BALANCING_NUM_CELLS_PER_MODULE;
                break;

            case (UDS_SUB_AFE_BAL_STATUS_CELLS0TO7):
            case (UDS_SUB_AFE_BAL_STATUS_CELLS8TO15):
                udsReadVar.uds32BitVar[0] =  ((cbstates.cellBalState[(subFunction-UDS_SUB_AFE_BAL_STATUS_CELLS0TO7)*8u +0]&0xFu)<< 0)
                                            |((cbstates.cellBalState[(subFunction-UDS_SUB_AFE_BAL_STATUS_CELLS0TO7)*8u +1]&0xFu)<< 4)
                                            |((cbstates.cellBalState[(subFunction-UDS_SUB_AFE_BAL_STATUS_CELLS0TO7)*8u +2]&0xFu)<< 8)
                                            |((cbstates.cellBalState[(subFunction-UDS_SUB_AFE_BAL_STATUS_CELLS0TO7)*8u +3]&0xFu)<< 12)
                                            |((cbstates.cellBalState[(subFunction-UDS_SUB_AFE_BAL_STATUS_CELLS0TO7)*8u +4]&0xFu)<< 16)
                                            |((cbstates.cellBalState[(subFunction-UDS_SUB_AFE_BAL_STATUS_CELLS0TO7)*8u +5]&0xFu)<< 20)
                                            |((cbstates.cellBalState[(subFunction-UDS_SUB_AFE_BAL_STATUS_CELLS0TO7)*8u +6]&0xFu)<< 24)
                                            |((cbstates.cellBalState[(subFunction-UDS_SUB_AFE_BAL_STATUS_CELLS0TO7)*8u +7]&0xFu)<< 28);
                *pDataLen = 4;
                break;

            case (UDS_SUB_BALANCING_BIT_MASK):
            case (UDS_SUB_BAL_BIT_MASK_BEFORE_POWERLOSS):
            case (UDS_SUB_BAL_BIT_MASK_AFTER_POWERLOSS):
                *pDataLen = r_balancingMasks(subFunction, parallel, serial, manualOverrideEnabled, preconds);
                break;
            default:
                retVal = RET_UDS_NRC_ROOR;
                break;
        }
    }

    return retVal;
}

/*********************************************************************
 * Read Module Sensor Data
 *********************************************************************/
static RET_T rDB0_moduleSensorData(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_UDS_NRC_SFNS;
    //*pDataLen = 4;

    switch(ID & UDS_MINOR_ID_MASK)
    {
    //ToDo: Add when available
        default:
//            return RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Read Module EEPROM/HISTOGRAM Data
 *********************************************************************/
static RET_T rDC0_moduleEeprom(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_UDS_NRC_SFNS;
    //*pDataLen = 4;

    switch(ID & UDS_MINOR_ID_MASK)
    {
    //ToDo: Add when available
        default:
//            return RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*-------------------------------------------------------------------------------------------------------------------*
 *                                                    PRIVATE ACCESS
 *-------------------------------------------------------------------------------------------------------------------*/

/*********************************************************************
 * Read BMZ private specific data
 *********************************************************************/
static RET_T rDE0_bmzModuleSpecific(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_UDS_NRC_SFNS;
    //*pDataLen = 4;

    switch(ID & UDS_MINOR_ID_MASK)
    {
    //ToDo: Add when available
        default:
//            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Write BMZ private specific data (Clear error flag)
 *********************************************************************/
static RET_T wDE0_bmzModuleSpecific(uint16_t ID, uint8_t const * pData, uint16_t dataLen)
{
    RET_T writeStatus = RET_UDS_NRC_SFNS;

    switch(ID & UDS_MINOR_ID_MASK)
    {
    //ToDo: Add when available
        default:
//            writeStatus = RET_UDS_NRC_ROOR;
            break;
    }

    return writeStatus;
}

/*********************************************************************
 * Read Debugging Commands Data
 *********************************************************************/
static RET_T rDF0_modDebugCommands(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal = RET_OK;
    //*pDataLen = 4;

    switch(ID & UDS_MINOR_ID_MASK)
    {
    //ToDo: Add when available
        case UDS_SUB_SET_BALANCE_MASK:
            retVal = RET_UDS_NRC_SFNS;
            break;
        default:
            retVal = RET_UDS_NRC_ROOR;
            break;
    }

    return retVal;
}

/*********************************************************************
 * Read Debugging Commands Data
 *********************************************************************/
static RET_T wDF0_modDebugCommands(uint16_t ID, uint8_t const * pData, uint16_t dataLen)
{
    RET_T writeStatus = RET_OK;
    uint8_t moduleId = ID & UDS_MINOR_ID_MASK;
    uint8_t subFunId = (ID & 0x00F0) >> 4;

    switch(subFunId)
    {
        case UDS_SUB_SET_BALANCE_MASK:
            if(moduleId >= USER_BATTERY_DEFS_NUM_BATTERY_MODULES)
            {
                writeStatus = RET_UDS_NRC_ROOR;
            }
            /* Check if mask bytes length is not grater than max */
            else if( dataLen > ((BALANCING_NUM_CELLS_PER_MODULE/8u)+1u) )
            {
                writeStatus = RET_UDS_NRC_IMLOIF;
            }
            else
            {
                uint8_t parallel = pAppCfg->packConfig.moduleGridPositions[moduleId].parallelCoordinate;
                uint8_t serial = pAppCfg->packConfig.moduleGridPositions[moduleId].serialCoordinate;
                uint8_t bitPos;
                uint8_t bytePos;

                for( uint8_t count = 0; count < BALANCING_NUM_CELLS_PER_MODULE; count++)
                {
                    bitPos = count % 8u;
                    bytePos = count / 8u;
                    balancing_manualOverride_setCell(parallel,serial, count, ((pData[bytePos]>>bitPos)&1u) );
                }
            }
            break;
        default:
            writeStatus = RET_UDS_NRC_ROOR;
            break;
    }

    return writeStatus;
}

/*-------------------------------------------------------------------------------------------------------------------*
 *                                            PRIVATE ACCESS END
 *-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*
 *                                               ERROR DATA
 *-------------------------------------------------------------------------------------------------------------------*/

/*********************************************************************
 * Read a All active error snapshots
 *********************************************************************/
static RET_T r_errorSnapshot(uint16_t *pDataLen)
{
    RET_T retVal= RET_UDS_NRC_ROOR;
    uint16_t udsRetLength = 0;
    *pDataLen = 0;

    dl_dataStorage_errorM_t errSnapshot = dl_errorM_dataStorage_snapshot();
    for (uint16_t counter = 0; counter < NUM_ERRORCODES; counter++)
    {
        if( (errSnapshot.elements[counter].errorStatus.active) == 1 )
        {
            udsReadVar.uds16BitVar[udsRetLength] = (uint16_t)errSnapshot.elements[counter].errorId;
            udsRetLength++;
            *pDataLen = *pDataLen + 2;
            retVal= RET_OK;
        } else {/* continue */}
    }

    return retVal;
}

/*********************************************************************
 * Read a certain Error Data by Error ID
 *********************************************************************/
static RET_T rE00_errorData(uint16_t ID, uint16_t *pDataLen)
{
    RET_T retVal= RET_UDS_NRC_ROOR;
    errorM_data_element_t ErrVal;
    uint16_t udsErrorId = (ID & 0xFFF0)>>4;
    uint8_t udsDataExtId = ID & UDS_MINOR_ID_MASK;

    if(udsErrorId == 0xE00 )
    {
        retVal = r_errorSnapshot(pDataLen);
    }
    else
    {
        for (uint16_t counter = 0; counter < udsDatalinkErrorIdMax; counter++)
        {
            if( (udsErrorMappingTab[counter].udsErrorId) == udsErrorId )
            {
                ErrVal = dl_errorM_dataStorage_entry(udsErrorMappingTab[counter].usrErrorId);
                retVal= RET_OK;
            } else {/* continue */}
        }

        if(retVal != RET_OK )
        {
            /* Do Nothing */
        }
        else
        {
            switch(udsDataExtId)
            {
            case UDS_SUB_ERROR_ID:
                udsReadVar.uds16BitVar[0] = (uint16_t)ErrVal.errorId;
                *pDataLen = 2;
                break;
            case  UDS_SUB_ERROR_STATUS_ACTIVE:
                udsReadVar.uds8BitVar[0] = ErrVal.errorStatus.active;
                *pDataLen = 1;
                break;
            case  UDS_SUB_ERROR_PADDING_BYTE:
                udsReadVar.uds8BitVar[0] = ErrVal._paddingByte;
                *pDataLen = 1;
                break;
            case  UDS_SUB_ERROR_REPORT_COUNTER:
                udsReadVar.uds32BitVar[0] = ErrVal.errorReportCounter;
                *pDataLen = 4;
                break;
            default:
                retVal = RET_UDS_NRC_ROOR;
                break;
            }
        }
    }

    return retVal;
}

/*-------------------------------------------------------------------------------------------------------------------*
 *                                     ERROR DATA END - MODULE LEVEL DATA END
 *-------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*
 *                                                   INITIALIZATION
 *-------------------------------------------------------------------------------------------------------------------*/

void udsInitUsrDatalink(void)
{
    pAppCfg = bq796xx_iSys_appCfg_get();
}
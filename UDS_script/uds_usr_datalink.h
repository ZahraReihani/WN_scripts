/*************** CONFIDENTIAL – BMZ-GmbH ************/
/**
 * @file            uds_usr_datalink.h
 * @brief           << Type in short description >>
 *                  
 *                  << Type in detailed description of this module >>
 * 
 * Project:         BMZ_SRC
 * @copyright
 *                  BMZ GmbH\n
 *                  Zeche Gustav 1\n
 *                  63791 Karlstein am Main\n
 *                  Tel. +49(0)6188 9956-0\n
 *
 **************************************************/

#ifndef SRC_MIDDLEWARE_CANOPENSTACK_CO_STACK_PROJECT_SOURCES_WN_UDS_USR_DATALINK_UDS_USR_DATALINK_H_
#define SRC_MIDDLEWARE_CANOPENSTACK_CO_STACK_PROJECT_SOURCES_WN_UDS_USR_DATALINK_UDS_USR_DATALINK_H_

    #include <stdint.h>
    #include "co_datatype.h"

    #define UDS_MAJOR_ID_MASK                 0xFFF0
    #define UDS_MINOR_ID_MASK                 0x000F
    #define UDS_MAX_DATATRANS_BYTES           (uint8_t)32
    #define UDS_CHECK_ID(ID)                  ( ((ID&0xF000) == 0xB000) ? ((ID&0xFFF0)>>4) : ((ID&0xFF00)>>4) )

    typedef enum
    {
        UDS_SUB_SERIALNUMBER_SUPPL                         = 0x0,
        UDS_SUB_SERIALNUMBER_WNSTD                         = 0x1,
        UDS_SUB_PRODUCTION_DATE                            = 0x2,
        UDS_SUB_MANUFACT_ID                                = 0x3,
        UDS_SUB_PRODUCT_CODE                               = 0x4,
        UDS_SUB_REVISION_NUMBER                            = 0x5,
        UDS_SUB_ARTICLE_NUMBER                             = 0x6,
        UDS_SUB_PLANT_NUMBER                               = 0x7,
        UDS_SUB_PROD_LINE_NUMBER                           = 0x8,
    }UDS_DID_SYS_PRODUCTION_DATA_0xB00_t;

    typedef enum
    {
        UDS_SUB_BOOTLOADER_VER                             = 0x0,
        UDS_SUB_APPLICATION_VER                            = 0x1,
    }UDS_DID_SW_VERSIONING_0xB01_t;

    typedef enum
    {
        UDS_SUB_INSTALLED_ENERGY                           = 0x0,
        UDS_SUB_INSTALLED_CAPACITY                         = 0x1,
        UDS_SUB_STATE_OF_HEALTH                            = 0x2,
        UDS_SUB_TOTAL_ENERGY_THRPUT                        = 0x3,
        UDS_SUB_CONTR_OPEN_LOADCNT                         = 0x4,
        UDS_SUB_CELL_TYPE                                  = 0x5,
    }UDS_DID_BATTERY_INFO_0xB02_t;

    typedef enum
    {
        UDS_SUB_HAL_TICK                                   = 0x0,
        UDS_SUB_RTC_TIME                                   = 0x1,
    }UDS_DID_OPERATING_TIME_0xB04_t;

    typedef enum
    {
        POWERPATH_NOT_READY                                = 0x0,
        POWERPATH_DETACHING                                = 0x1,
        POWERPATH_ATTACHING                                = 0x2,
        POWERPATH_ATTACHED                                 = 0x3,
        POWERPATH_MANUAL_OVERRIDE                          = 0x4,
    } powerpath_state_t;

    typedef enum
    {
        UDS_SUB_SYSTEM_STATE_REQUEST                       = 0x0,
        UDS_SUB_PLUS_RELAY_STATE                           = 0x1,
        UDS_SUB_MINUS_RELAY_STATE                          = 0x2,
        UDS_SUB_PRE_RELAY_STATE                            = 0x3,
        UDS_SUB_OVERALL_RELAY_STATE                        = 0x4,
        UDS_SUB_PRECOND_RELAY_STATE                        = 0x5,
        UDS_SUB_AFE_STATE                                  = 0x6,
    }UDS_DID_DEVICE_CONTROL_0xB05_t;

    typedef enum
    {
        UDS_SUB_SYSTEM_STATE                               = 0x0,
        UDS_SUB_SYSTEM_TARGET_STATE                        = 0x1,
        UDS_SUB_ERROR_ACTION                               = 0x2,
    }UDS_DID_OPERATING_MODES_0xB06_t;

    typedef enum
    {
        UDS_SUB_RELAY_SWITCHING_UNDER_LOAD                 = 0x0,
        UDS_SUB_RELAY_TRIP_COUNTER                         = 0x1,
        UDS_SUB_BATTERY_LIFETIME_IN_CYCLES                 = 0x2,
        UDS_SUB_BATTERY_CHARGER_STATUS                     = 0x3,
        UDS_SUB_CHG_DSG_STATE                              = 0x4,
        UDS_SUB_CHG_DSG_PROPOSAL                           = 0x5,
        UDS_SUB_SERVICE_CHG_ENABLED                        = 0x6,
    }UDS_DID_BATLIFE_DATA_0xB0A_t;

    typedef enum
    {
        UDS_SUB_ALL_VOLT_CHANNELS                          = 0x0,
        UDS_SUB_STACK_VOLTAGE                              = 0x1,
        UDS_SUB_INTERMEDIATE_VOLTAGE                       = 0x2,
        UDS_SUB_OUTPUT_VOLTAGE                             = 0x3,
        UDS_SUB_ADC_VOLTAGE                                = 0x4,
        UDS_SUB_RELAY_FDBK1_VOLTAGE                        = 0x5,
        UDS_SUB_RELAY_FDBK2_VOLTAGE                        = 0x6,
        UDS_SUB_RELAY_FDBK3_VOLTAGE                        = 0x7,
        UDS_SUB_RELAY_FDBK4_VOLTAGE                        = 0x8,
    }UDS_DID_PACK_VOLTAGES_0xB0B_t;

    typedef enum
    {
        UDS_SUB_EXTRACT_MIN_CELLVOLT                       = 0x0,
        UDS_SUB_EXTRACT_MAX_CELLVOLT                       = 0x1,
        UDS_SUB_EXTRACT_AVG_CELLVOLT                       = 0x2,
        UDS_SUB_EXTRACT_MAXDIFF_CELLVOLT                   = 0x3,
        UDS_SUB_EXTRACT_MIN_MODULEVOLT                     = 0x4,
        UDS_SUB_EXTRACT_MAX_MODULEVOLT                     = 0x5,
        UDS_SUB_EXTRACT_MIN_MODULESTRINGVOLT               = 0x6,
        UDS_SUB_EXTRACT_MAX_MODULESTRINGVOLT               = 0x7,
    }UDS_DID_EXTRACT_VOLTAGES_0xB0C_t;

    typedef enum
    {
        UDS_SUB_MCU_TEMP                                   = 0x0,
    }UDS_DID_PACK_TEMPS_0xB0D_t;

    typedef enum
    {
        UDS_SUB_EXTRACT_MIN_CELLTEMP                       = 0x0,
        UDS_SUB_EXTRACT_MAX_CELLTEMP                       = 0x1,
        UDS_SUB_EXTRACT_MIN_BOARDTEMP                      = 0x2,
        UDS_SUB_EXTRACT_MAX_BOARDTEMP                      = 0x3,
        UDS_SUB_EXTRACT_AVG_TEMP                           = 0x4,
    }UDS_DID_EXTRACT_TEMPS_0xB0E_t;

    typedef enum
    {
        UDS_SUB_ALL_CURR_CHANNELS                          = 0x0,
        UDS_SUB_MAIN_CURRENT                               = 0x1,
        UDS_SUB_SECOND_CURRENT                             = 0x2,
        UDS_SUB_ALL_CURR_MODULES                           = 0x3,
        UDS_SUB_EXTRACT_CURR_MIN                           = 0x4,
        UDS_SUB_EXTRACT_CURR_MAX                           = 0x5,
        UDS_SUB_EXTRACT_CURR_AVG                           = 0x6,
    }UDS_DID_PACK_CURRENTS_0xB0F_t;

    typedef enum
    {
        UDS_SUB_MAXIMUM_CHARGE_CURRENT                     = 0x0,
        UDS_SUB_MAXIMUM_DISCHARGE_CURRENT                  = 0x1,
        UDS_SUB_INFO_CHG_LIMIT_BY_USERSOC                  = 0x2,
        UDS_SUB_INFO_CHG_LIMIT_BY_MINTEMP                  = 0x3,
        UDS_SUB_INFO_CHG_LIMIT_BY_MAXTEMP                  = 0x4,
        UDS_SUB_INFO_CHG_LIMIT_BY_MINVOLT                  = 0x5,
        UDS_SUB_INFO_CHG_LIMIT_BY_MAXVOLT                  = 0x6,
        UDS_SUB_INFO_DSG_LIMIT_BY_USERSOC                  = 0x7,
        UDS_SUB_INFO_DSG_LIMIT_BY_MINTEMP                  = 0x8,
        UDS_SUB_INFO_DSG_LIMIT_BY_MAXTEMP                  = 0x9,
        UDS_SUB_INFO_DSG_LIMIT_BY_MINVOLT                  = 0xA,
        UDS_SUB_INFO_DSG_LIMIT_BY_MAXVOLT                  = 0xB
    }UDS_DID_DERATING_CURR_0xB13_t;

    typedef enum
    {
        UDS_SUB_MAXIMUM_CHARGE_CURRENT_POWERMAP_2S         = 0x0,
        UDS_SUB_MAXIMUM_DISCHARGE_CURRENT_POWERMAP_2S      = 0x1,
        UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMIN_VOLTSMIN_2s     = 0x2,
        UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMIN_VOLTSMAX_2s     = 0x3,
        UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMAX_VOLTSMIN_2s     = 0x4,
        UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMAX_VOLTSMAX_2s     = 0x5,
        UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMIN_VOLTSMIN_2s     = 0x6,
        UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMIN_VOLTSMAX_2s     = 0x7,
        UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMAX_VOLTSMIN_2s     = 0x8,
        UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMAX_VOLTSMAX_2s     = 0x9
    }UDS_DID_POWER_MAPS_2S_0xB14_t;

    typedef enum
    {
        UDS_SUB_MAXIMUM_CHARGE_CURRENT_POWERMAP_120S       = 0x0,
        UDS_SUB_MAXIMUM_DISCHARGE_CURRENT_POWERMAP_120S    = 0x1,
        UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMIN_VOLTSMIN_120s   = 0x2,
        UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMIN_VOLTSMAX_120s   = 0x3,
        UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMAX_VOLTSMIN_120s   = 0x4,
        UDS_SUB_INFO_CHG_LIMIT_BY_TEMPSMAX_VOLTSMAX_120s   = 0x5,
        UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMIN_VOLTSMIN_120s   = 0x6,
        UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMIN_VOLTSMAX_120s   = 0x7,
        UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMAX_VOLTSMIN_120s   = 0x8,
        UDS_SUB_INFO_DSG_LIMIT_BY_TEMPSMAX_VOLTSMAX_120s   = 0x9
    }UDS_DID_POWER_MAPS_120S_0xB15_t;

    typedef enum
    {
        UDS_SUB_RAW_SOC                                    = 0x0,
        UDS_SUB_USER_SOC                                   = 0x1,
        UDS_SUB_USER_SOH                                   = 0x2,
    }UDS_DID_SOC_SOH_0xB17_t;

    typedef enum
    {
        UDS_SUB_ACCEL_SENSOR_X                             = 0x0,
        UDS_SUB_ACCEL_SENSOR_Y                             = 0x1,
        UDS_SUB_ACCEL_SENSOR_Z                             = 0x2,
        UDS_SUB_ACCEL_SENSOR_STAT                          = 0x3,
        UDS_SUB_HUMID_SENSOR_RH                            = 0x7,
        UDS_SUB_HUMID_SENSOR_TEMP                          = 0x8,
        UDS_SUB_HUMID_SENSOR_STAT                          = 0x9,
        UDS_SUB_FLUID_SENSOR_STAT                          = 0xB,
        UDS_SUB_FLUID_SENSOR_mV                            = 0xC,
        UDS_SUB_CVS_SENSOR_ALL                             = 0xF,
    }UDS_DID_SENSOR_DATA_0xB18_t;

    typedef enum
    {
        UDS_SUB_CONFIG_ERASE                               = 0x0,
        UDS_SUB_DATA_ERASE                                 = 0x1,
    }UDS_SUB_BMZ_SPECIFIC_REQ_t;

    typedef enum
    {
        START_VALUE                                        = 0x67977313,
    }UDS_SUB_BMZ_AUTHENTICATE_t;

    typedef enum
    {
        UDS_SUB_BMZ_AUTHENTICATE                           = 0x0,
        UDS_SUB_BMZ_SPECIFIC_REQ                           = 0x1,
        UDS_SUB_BMZ_CONFIG_VER                             = 0x2,
        UDS_SUB_BMZ_CONFIGST_STATE                         = 0x3,
        UDS_SUB_BMZ_DATAST_STATE                           = 0x4,
        UDS_SUB_BMZ_CLEAR_ERROR_BY_IDX                     = 0x5,
        UDS_SUB_BMZ_CLEAR_ERROR_ALL                        = 0x6,
    }UDS_DID_BMZ_SPECIFIC_0xB1D_t;

    typedef enum
    {
        UDS_SUB_POWERPATH_STAT_REQ                         = 0x0,
        UDS_SUB_SERVICE_CHARGING                           = 0x1,
        UDS_SUB_OVERRIDE_BALANCING                         = 0x2,
    }UDS_DID_SYS_DEBUG_CMDS_0xB1E_t;

    /******************************************************************************************************************************************

    ******************************************************************************************************************************************/

    typedef enum
    {
        UDS_SUB_PRODDATA_MOD1                              = 0x0,
        UDS_SUB_PRODDATA_MOD2                              = 0x1,
        UDS_SUB_PRODDATA_MOD3                              = 0x2,
        UDS_SUB_PRODDATA_MOD4                              = 0x3,
        UDS_SUB_PRODDATA_MOD5                              = 0x4,
        UDS_SUB_PRODDATA_MOD6                              = 0x5,
        UDS_SUB_PRODDATA_MOD7                              = 0x6,
        UDS_SUB_PRODDATA_MOD8                              = 0x7,
        UDS_SUB_PRODDATA_MOD9                              = 0x8,
        UDS_SUB_PRODDATA_MOD10                             = 0x9,
        UDS_SUB_PRODDATA_MOD11                             = 0xA,
        UDS_SUB_PRODDATA_MOD12                             = 0xB,
        UDS_SUB_PRODDATA_MOD13                             = 0xC,
        UDS_SUB_PRODDATA_MOD14                             = 0xD,
        UDS_SUB_PRODDATA_MOD15                             = 0xE,
        UDS_SUB_PRODDATA_MOD16                             = 0xF,
    }UDS_DID_MOD_PRODUCTION_DATA_0xCF0_t;

    typedef enum
    {
        UDS_SUB_MOD_EXTRACT_MIN_CELLVOLT                   = 0x0,
        UDS_SUB_MOD_EXTRACT_MAX_CELLVOLT                   = 0x1,
        UDS_SUB_MOD_EXTRACT_AVG_CELLVOLT                   = 0x2,
        UDS_SUB_MOD_EXTRACT_MAXDIFF_CELLVOLT               = 0x3,
        UDS_SUB_MOD_EXTRACT_SUM_CELLVOLT                   = 0x4,
    }UDS_DID_MODULE_EXTRACT_CELL_VOLTAGE_0xD10_t;

    typedef enum
    {
        UDS_SUB_MOD_EXTRACT_MIN_TEMP                       = 0x0,
        UDS_SUB_MOD_EXTRACT_MAX_TEMP                       = 0x1,
        UDS_SUB_MOD_EXTRACT_AVG_TEMP                       = 0x2,
        UDS_SUB_MOD_EXTRACT_MAXDIFF_TEMP                   = 0x3,
    }UDS_DID_MODULE_EXTRACT_TEMPERATURE_0xD40_t;

    typedef enum
    {
        UDS_SUB_DEVICE_ALL_TEMP                            = 0x0,
        UDS_SUB_DEVICE_NTC_TEMP                            = 0x1, // NTCs 1 till 4
        UDS_SUB_BOARD_ALL_TEMP                             = 0x5,
        UDS_SUB_BOARD_NTC_TEMP                             = 0x6, // NTCs 1 till 10
    }UDS_DID_ADDITION_MODULE_TEMP_0xD60_t;

    typedef enum
    {
        UDS_SUB_MODULE_PRECOND                             = 0x0,
        UDS_SUB_MODULE_BAL_STATUS_ALL                      = 0x1,
        UDS_SUB_AFE_BAL_STATUS_CELLS0TO7                   = 0x2,
        UDS_SUB_AFE_BAL_STATUS_CELLS8TO15                  = 0x3,
        UDS_SUB_BALANCING_BIT_MASK                         = 0x4,
        UDS_SUB_BAL_BIT_MASK_BEFORE_POWERLOSS              = 0x5,
        UDS_SUB_BAL_BIT_MASK_AFTER_POWERLOSS               = 0x6,
    }UDS_DID_MODULE_BALANCING_0xD90_t;

    typedef enum
    {
        UDS_SUB_SET_BALANCE_MASK                           = 0x0,
    }UDS_DID_MOD_DEBUG_CMDS_0xDF0_t;

    typedef enum
    {
        UDS_SUB_ERROR_ID                                   = 0x0,
        UDS_SUB_ERROR_STATUS_ACTIVE                        = 0x1,
        UDS_SUB_ERROR_PADDING_BYTE                         = 0x2,
        UDS_SUB_ERROR_REPORT_COUNTER                       = 0x3,
    }UDS_SUB_DATA_PER_ERROR_t;

    typedef enum
    {
        UDS_SUB_DATA_SNAPSHOT_ACTIVE                       = 0x0,
        UDS_SUB_DATA_PER_ERROR                             = 0x1,
    }UDS_DID_ERROR_DATA_0xE00_t;

    typedef enum
    {
        /* System level and General Information */
        UDS_DID_SYS_PRODUCTION_DATA                        = 0xB00,
        UDS_DID_SW_VERSIONING                              = 0xB01,
        UDS_DID_BATTERY_INFO                               = 0xB02,
        UDS_DID_SYS_EEPROM                                 = 0xB03,
        UDS_DID_OPERATING_TIME                             = 0xB04,
        UDS_DID_DEVICE_CONTROL                             = 0xB05,
        UDS_DID_OPERATING_MODES                            = 0xB06,

        UDS_DID_BATLIFE_DATA                               = 0xB0A,
        UDS_DID_PACK_VOLTAGES                              = 0xB0B,
        UDS_DID_EXTRACT_VOLTAGES                           = 0xB0C,
        UDS_DID_PACK_TEMPS                                 = 0xB0D,
        UDS_DID_EXTRACT_TEMPS                              = 0xB0E,
        UDS_DID_PACK_CURRENTS                              = 0xB0F,

        UDS_DID_DERATING_CURR                              = 0xB13,
        UDS_DID_POWER_MAPS_2S                              = 0xB14,
        UDS_DID_POWER_MAPS_120S                            = 0xB15,
        UDS_DID_LEAKY_BUCKET                               = 0xB16,
        UDS_DID_SOC_SOH                                    = 0xB17,
        UDS_DID_SENSOR_DATA                                = 0xB18,

        UDS_DID_SYS_BMZ_SPECIFIC                           = 0xB1D,
        UDS_DID_SYS_DEBUG_CMDS                             = 0xB1E,

        /* Module level and Specific Information */
        UDS_DID_MOD_PRODUCTION_DATA                        = 0xCF0,
        UDS_DID_MODULE_INFO                                = 0xD00,
        UDS_DID_CELL_VOLTAGE_EXTRACT                       = 0xD10,
        UDS_DID_CELL_VOLTAGES_STACK                        = 0xD20,
        UDS_DID_CELL_VOLTAGE                               = 0xD30,
        UDS_DID_CELL_TEMP_EXTRACT                          = 0xD40,
        UDS_DID_CELL_TEMP_STACK                            = 0xD50,
        UDS_DID_ADDITION_MODULE_TEMP                       = 0xD60,
        UDS_DID_NTC_CELLTEMP                               = 0xD70,
        UDS_DID_MODULES_CURRENTS                           = 0xD80,
        UDS_DID_MODULE_BALANCING                           = 0xD90,

        UDS_DID_MODULE_SENSOR_DATA                         = 0xDB0,
        UDS_DID_MOD_EEPROM                                 = 0xDC0,

        UDS_DID_MOD_BMZ_SPECIFIC                           = 0xDE0,
        UDS_DID_MOD_DEBUG_CMDS                             = 0xDF0,
        UDS_DID_ERROR_DATA                                 = 0xE00,
    }udsDids_t;

    typedef RET_T (*udsRead_func_t)(uint16_t Id, uint16_t *pDataLen);
    typedef RET_T (*udsWrite_func_t)(uint16_t Id, uint8_t const * data, uint16_t dataLen);

    typedef struct
    {
        uint16_t index;   /* object ID */
        udsRead_func_t objectReadFunc;
    }uds_dataReadTab_t;

    typedef struct
    {
        uint16_t index;   /* object ID */
        udsWrite_func_t objectWriteFunc;
        const uint8_t* sessionAuth;
        const uint8_t* securityAuth;
    }uds_dataWriteTab_t;

    typedef union{
        uint8_t  uds8BitVar[UDS_MAX_DATATRANS_BYTES];
        uint16_t uds16BitVar[UDS_MAX_DATATRANS_BYTES];
        uint32_t uds32BitVar[UDS_MAX_DATATRANS_BYTES];
        uint64_t uds64BitVar[UDS_MAX_DATATRANS_BYTES];
    }uds_ReadDataType_t;

    typedef struct{
        uint16_t usrErrorId;
        uint16_t udsErrorId;
    }uds_errorMappingTab_t;

    /*********************************************************************
     * Table to map User Error IDs to UDS DIDs Requests
     *********************************************************************/
    static const uds_errorMappingTab_t udsErrorMappingTab[] =
    {
        {0x3216,	0xE01},   /* ERROR_ID_SystemStateTransitionRequestRejected,       */
        {0x3217,	0xE02},   /* ERROR_ID_UnknownErrorIdReported,                     */
        {0x5477,	0xE03},   /* ERROR_ID_Stack_Overflow,                             */
        {0x547A,	0xE04},   /* ERROR_ID_Unspecified_SelfTest_Failure,               */
        {0x6111,	0xE05},   /* ERROR_ID_Software_MsgService_QueueOverflow,          */
        {0x6212,	0xE06},   /* ERROR_ID_Time_Budget_Error,                          */
        {0x6215,	0xE07},   /* ERROR_ID_Memory_Management_Error,                    */
        {0x6216,	0xE08},   /* ERROR_ID_OS_Safety_Critical_Error,                   */
        {0x6217,	0xE09},   /* ERROR_ID_OS_Ressource_Error,                         */
        {0x6315,	0xE0A},   /* ERROR_ID_SystemStateM_TransitionFailed,              */
        {0x6316,	0xE0B},   /* ERROR_ID_SystemStateM_Invalid_Request_Received,      */
        {0x6317,	0xE0C},   /* ERROR_ID_ErrorM_EarlyHealRequestDropped,             */
        {0x6318,	0xE0D},   /* ERROR_ID_ErrorM_EarlyResetAllRequestDropped,         */
        {0x6319,	0xE0E},   /* ERROR_ID_ErrorM_EarlyErrorReportDiscovered,          */
        {0x6410,	0xE0F},   /* ERROR_ID_External_Flash_Init_Failure,                */
        {0x6414,	0xE10},   /* ERROR_ID_EEPROM_Init_Failure,                        */
        {0x6415,	0xE11},   /* ERROR_ID_Storage_Init_Failure,                       */
        {0x6416,	0xE12},   /* ERROR_ID_Parameter_Init_Failure,                     */
        {0x6417,	0xE13},   /* ERROR_ID_Logging_Init_Failure,                       */
        {0x6418,	0xE14},   /* ERROR_ID_Storage_Duplicate_Id_Collision,             */
        {0x6419,	0xE15},   /* ERROR_ID_Storage_Repair_failed,                      */
        {0x6511,	0xE16},   /* ERROR_ID_Wrong_Configuration,                        */
        {0x6601,	0xE17},   /* ERROR_ID_EepromEmu_Error,                            */
        {0x8320,	0xE18},   /* ERROR_ID_HAL_BXCAN_TxAbortError,                     */
        {0x8321,	0xE19},   /* ERROR_ID_HAL_BXCAN_Error,                            */
        {0x2111,	0xE1A},   /* ERROR_ID_CHG_overcurrent_warning,                    */
        {0x2112,	0xE1B},   /* ERROR_ID_CHG_overcurrent_error,                      */
        {0x2311,	0xE1C},   /* ERROR_ID_Short_Circuit,                              */
        {0x2312,	0xE1D},   /* ERROR_ID_DSG_overcurrent_warning,                    */
        {0x2313,	0xE1E},   /* ERROR_ID_DSG_overcurrent_error,                      */
        {0x2411,	0xE1F},   /* ERROR_ID_Current_plausibility_error,                 */
        {0x2412,	0xE20},   /* ERROR_ID_Current_Observer_Timeout,                   */
        {0x3211,	0xE21},   /* ERROR_ID_Overvoltage_battery_module_warning,         */
        {0x3212,	0xE22},   /* ERROR_ID_Undervoltage_battery_module_warning,        */

        {0x3215,	0xE23},   /* ERROR_ID_Voltage_Observer_Timeout,                   */
        {0x3220,	0xE24},   /* ERROR_ID_Overvoltage_battery_pack_warning,           */
        {0x3221,	0xE25},   /* ERROR_ID_Undervoltage_battery_pack_warning,          */
        {0x3410,	0xE26},   /* ERROR_ID_Cell_voltage_plausibility_error,            */
        {0x3411,	0xE27},   /* ERROR_ID_Overvoltage_Cell_warning,                   */
        {0x3412,	0xE28},   /* ERROR_ID_Undervoltage_Cell_warning,                  */
        {0x3413,	0xE29},   /* ERROR_ID_Overvoltage_Cell_error,                     */
        {0x3414,	0xE2A},   /* ERROR_ID_Undervoltage_Cell_error,                    */
        {0x3415,	0xE2B},   /* ERROR_ID_Deep_Discharge_Cell,                        */
        {0x3416,	0xE2C},   /* ERROR_ID_Cell_voltage_difference,                    */
        {0x3417,	0xE2D},   /* ERROR_ID_Cell_defect_overvoltage,                    */
        {0x3418,	0xE2E},   /* ERROR_ID_Chg_Dsg_Violation,                          */
        {0x3419,	0xE2F},   /* ERROR_ID_Emergency_Discharging_charge_Violation,     */
        {0x341A,	0xE30},   /* ERROR_ID_Emergency_Charging_Timeout,                 */
        {0x341B,	0xE31},   /* ERROR_ID_Emergency_Discharging_Timeout,              */
        {0x341C,	0xE32},   /* ERROR_ID_Observer_ChargeDischarge_Violation,         */
        {0x341D,	0xE33},   /* ERROR_ID_Observer_ChargeDischarge_ImplError,         */
        {0x3421,	0xE34},   /* ERROR_ID_Deep_Discharge_Protection_Level_1,          */
        {0x3422,	0xE35},   /* ERROR_ID_Deep_Discharge_Protection_Level_2,          */
        {0x3423,	0xE36},   /* ERROR_ID_Deep_Discharge_Protection_Level_3,          */
        {0x3450,	0xE37},   /* ERROR_ID_Observer_Reserved_DoNothing,                */
        {0x4210,	0xE38},   /* ERROR_ID_BMS_controller_temperature_high,            */
        {0x4211,	0xE39},   /* ERROR_ID_AFE_temperature_high,                       */
        {0x4212,	0xE3A},   /* ERROR_ID_Slave_temperature_high,                     */
        {0x4310,	0xE3B},   /* ERROR_ID_Temperature_difference_too_high,            */
        {0x4311,	0xE3C},   /* ERROR_ID_DSG_overtemperature_warning,                */
        {0x4312,	0xE3D},   /* ERROR_ID_DSG_undertemperature_warning,               */
        {0x4313,	0xE3E},   /* ERROR_ID_CHG_overtemperature_warning,                */
        {0x4314,	0xE3F},   /* ERROR_ID_CHG_undertemperature_warning,               */
        {0x4321,	0xE40},   /* ERROR_ID_DSG_overtemperature_error,                  */
        {0x4322,	0xE41},   /* ERROR_ID_DSG_undertemperature_error,                 */
        {0x4323,	0xE42},   /* ERROR_ID_CHG_overtemperature_error,                  */
        {0x4324,	0xE43},   /* ERROR_ID_CHG_undertemperature_error,                 */
        {0x4325,	0xE44},   /* ERROR_ID_Temperature_Observer_Timeout,               */
        {0x4326,	0xE45},   /* ERROR_ID_Temperature_Permanent_error,                */
        {0x4327,	0xE46},   /* ERROR_ID_Temperature_plausibility_error,             */
        {0x5410,	0xE47},   /* ERROR_ID_PreCharge_Relay_Defect,                     */
        {0x5411,	0xE48},   /* ERROR_ID_Positive_Relay_Defect,                      */
        {0x5412,	0xE49},   /* ERROR_ID_Negative_Relay_Defect,                      */
        {0x5413,	0xE4A},   /* ERROR_ID_Precharge_Timeout,                          */
        {0x5414,	0xE4B},   /* ERROR_ID_Relays_Not_Ready,                           */
        {0x5415,	0xE4C},   /* ERROR_ID_WaitZeroCurrent_Timeout,                    */
        {0x541F,	0xE4D},   /* ERROR_ID_PowerPath_DetachUnderLoad,                  */
        {0x5420,	0xE4E},   /* ERROR_ID_PowerPath_ImplementationError,              */
        {0x5421,	0xE4F},   /* ERROR_ID_PowerPath_DetachInterrupted,                */
        {0x5422,	0xE50},   /* ERROR_ID_PowerPath_AttachInterrupted,                */
        {0x5423,	0xE51},   /* ERROR_ID_PowerPathManualOverride_InvalidRequest,     */
        {0x5424,	0xE52},   /* ERROR_ID_PowerPathManualOverride_ExitUnderLoad,      */
        {0x5425,	0xE53},   /* ERROR_ID_PowerPath_SafetyDetachIntervalTimeout,      */
        {0x5430,	0xE54},   /* ERROR_ID_Relay_DigitalFeedBackInvalid,               */
        {0x5432,	0xE55},   /* ERROR_ID_Interlock_hvil,                             */
        {0x5433,	0xE56},   /* ERROR_ID_Interlock_emcystp,                          */
        {0x5436,	0xE57},   /* ERROR_ID_Isolation_Monitor,                          */
        {0x5437,	0xE58},   /* ERROR_ID_Fluid_Sensor,                               */
        {0x5438,	0xE59},   /* ERROR_ID_Humidity_Sensor,                            */
        {0x5441,	0xE5A},   /* ERROR_ID_Frontend_Error,                             */
        {0x5442,	0xE5B},   /* ERROR_ID_CVS,                                        */
        {0x5443,	0xE5C},   /* ERROR_ID_CVS_INIT_TIMEOUT,                           */
        {0x5461,	0xE5D},   /* ERROR_ID_ADC_Unplausible_Measurement,                */
        {0x5462,	0xE5E},   /* ERROR_ID_ADC_Internal_Error,                         */
        {0x5465,	0xE5F},   /* ERROR_ID_ADC_Measurement_Start_Error,                */
        {0x5466,	0xE60},   /* ERROR_ID_ADC_Init_Error,                             */
        {0x6101,	0xE61},   /* ERROR_ID_DETECTED_RESET_BY_ERRORHANDLING,            */
        {0x6301,	0xE62},   /* ERROR_ID_OPERATIONALSTATE_ASSERT_FAILED,             */
        {0x6302,	0xE63},   /* ERROR_ID_OPERATIONALSTATE_SYSTEMSTATE_VIOLATION,     */
        {0x6303,	0xE64},   /* ERROR_ID_OPERATIONALSTATE_RELAISSTATE_VIOLATION,     */
        {0x6304,	0xE65},   /* ERROR_ID_OPERATIONALSTATE_SYSTEMSTATE_TIMEOUT,       */
        {0x6305,	0xE66},   /* ERROR_ID_OPERATIONALSTATE_RELAISSTATE_TIMEOUT,       */
        {0x6306,	0xE67},   /* ERROR_ID_OPERATIONALSTATE_SYSTARGETSTATE_VIOLATION,  */
        {0x6307,	0xE68},   /* ERROR_ID_OPERATIONALSTATE_RLYTARGETSTATE_VIOLATION,  */
        {0x6308,	0xE69},   /* ERROR_ID_OPERATIONALSTATE_TIMEOUT_TR_DETECTED,       */
        {0x630A,	0xE6A},   /* ERROR_ID_OPERATIONALSTATE_UNKNOWN_SW_REQUEST,        */
        {0x6512,	0xE6B},   /* ERROR_ID_Incompatible_Application_ArticleNumber,     */
        {0x6513,	0xE6C},   /* ERROR_ID_Incompatible_Application_HardwareRevision,  */
        {0x6514,	0xE6D},   /* ERROR_ID_PcbEolTestSW_OtpArticleNumberDiscovered,    */
        {0x6515,	0xE6E},   /* ERROR_ID_PcbEolTestSW_OtpHardwareRevDiscovered,      */
        {0x6700,	0xE6F},   /* ERROR_ID_KMS_Level_Max,                              */
        {0x6701,	0xE70},   /* ERROR_ID_KMS_Level_Not_Approved,                     */
        {0x6811,	0xE71},   /* ERROR_ID_CELLVOLTAGEDELTAMONITORING_DEFECT,          */
        {0x7110,	0xE72},   /* ERROR_ID_DCDC_Bat_Not_Ready,                         */
        {0x7120,	0xE73},   /* ERROR_ID_Unplausible_External_System_Voltage,        */
        {0x7200,	0xE74},   /* ERROR_ID_DCACEmergencyError_StopBattery,             */
        {0x7201,	0xE75},   /* ERROR_ID_DCACEmergencyError_DontCare,                */
        {0x8001,	0xE76},   /* ERROR_ID_DCDCCTRL_FEEDBACKVOLTAGE_OUT_OF_RANGE,      */
        {0x8160,	0xE77},   /* ERROR_ID_CAN_Internal_Error,                         */
        {0x8331,	0xE78},   /* ERROR_ID_MW_BASICCAN_ERROR_IRQ,                      */
        {0x8332,	0xE79},   /* ERROR_ID_MW_BASICCAN_TX_ERROR,                       */
        {0x8333,	0xE7A},   /* ERROR_ID_MW_BASICCAN_IMPL_ERROR,                     */
        {0x8350,	0xE7B},   /* ERROR_ID_MW_AccelerationSensor_CommError,            */
        {0x8351,	0xE7C},   /* ERROR_ID_MW_AccelerationSensor_RunTimeError,         */
        {0x8352,	0xE7D},   /* ERROR_ID_MW_AccelerationSensor_SelftestFailed,       */
        {0x8353,	0xE7E},   /* ERROR_ID_MW_AccelerationSensor_ShockDetected,        */
        {0x9010,	0xE7F},   /* ERROR_ID_Power_15V_Not_Good,                         */
        {0x9011,	0xE80},   /* ERROR_ID_Relay_Test_Timeout,                         */
        {0x9030,	0xE81},   /* ERROR_ID_KL15_ENABLE,                                */
    };

    extern uds_ReadDataType_t udsReadVar;
    extern const uds_dataReadTab_t dataReadFuncTab[];
    extern const uds_dataWriteTab_t dataWriteFuncTab[];
    extern const uint16_t udsDatalinkReadFunNum;
    extern const uint16_t udsDatalinkWriteFunNum;

    void udsInitUsrDatalink(void);

#endif

/**
 * @}
 */

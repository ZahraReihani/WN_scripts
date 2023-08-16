#ifdef ERRORID_MAGIC_ENABLED
    #ifdef USR_ERRORID_INCLUDEGUARD
    #undef USR_ERRORID_INCLUDEGUARD
    #endif
#endif


#ifndef USR_ERRORID_INCLUDEGUARD
#define USR_ERRORID_INCLUDEGUARD

    #ifndef ERRORID_MAGIC_ENABLED
        #define DECLARE_ERROR_ID(name, value_uint16, defaultAction, defaultLog) name = (value_uint16),
        #define DECLARE_EVENT_ID(name, value_uint16, defaultLog) DECLARE_ERROR_ID(name, value_uint16, ERROR_ACTION_NONE, defaultLog)
        #ifdef __cplusplus
        extern "C" {
        #endif /* __cplusplus */

        typedef enum __attribute__((packed)) s_usr_errorId_t /* HVP - required */
        {

    #endif /* ERRORID_MAGIC_ENABLED */


            /********************* HVP Section Begin **********************/
            //Events: System State Manager
            DECLARE_EVENT_ID(EVENT_ID_ReceivedSystemStateRequest,               0x0001, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_SystemStateTransitionTriggered,           0x0002, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_SystemStateTransitionTimeReport_ms,       0x0003, DL_LOGGING_SEL_LOGEVENT)
            //Events: Circular Flash Buffer (logging)
            DECLARE_EVENT_ID(EVENT_ID_CircularFlashBuffer_PageEraseCount,       0x0011, DL_LOGGING_SEL_LOGEVENT)
            //Events: Eeprom Emulation
            DECLARE_EVENT_ID(EVENT_ID_EepromEmu_EraseTriggered,                 0x0021, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_EepromEmu_PageSwapTriggered,              0x0022, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_EepromEmu_PageSwapDone,                   0x0023, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_EepromEmu_PageSwapIssue,                  0x0024, DL_LOGGING_SEL_LOGEVENT)
            //Events: Storage Manager
            DECLARE_EVENT_ID(EVENT_ID_StorageM_WriteBackTriggered,              0x0031, DL_LOGGING_SEL_LOGEVENT)
            //DECLARE_EVENT_ID(EVENT_ID_StorageM_StorageRepairTriggered,          0x0032, DL_LOGGING_SEL_LOGEVENT)
            //DECLARE_EVENT_ID(EVENT_ID_StorageM_StorageCrcMismatch,              0x0033, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_StorageM_EraseTriggered,                  0x0034, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_StorageM_WriteBackLocked,                 0x0035, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_StorageM_WriteBackUnLocked,               0x0036, DL_LOGGING_SEL_LOGEVENT)
            //DECLARE_EVENT_ID(EVENT_ID_StorageM_UserBufferWriteBackDisabled,     0x0037, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_StorageM_ShadowBuffersRevertTriggered,    0x0038, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_StorageM_StorageRevisionUpdateDiscovered, 0x0039, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_StorageM_WriteBackTimeReport_ms,          0x003A, DL_LOGGING_SEL_LOGEVENT)
            //DECLARE_EVENT_ID(EVENT_ID_StorageM_WriteBackNotAllowed,             0x003B, DL_LOGGING_SEL_LOGEVENT)
            //DECLARE_EVENT_ID(EVENT_ID_StorageM_WriteBackFailed,                 0x003C, DL_LOGGING_SEL_LOGEVENT)
//            DECLARE_EVENT_ID(EVENT_ID_StorageM_EraseNotAllowed,                 0x003D, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_StorageM_EraseTimeReport_ms,              0x003E, DL_LOGGING_SEL_LOGEVENT)
            //DECLARE_EVENT_ID(EVENT_ID_StorageM_EraseFailed,                     0x003F, DL_LOGGING_SEL_LOGEVENT)
            //DECLARE_EVENT_ID(EVENT_ID_StorageM_StorageRevisionDowngradeRejected,0x0040, DL_LOGGING_SEL_LOGEVENT)
            //DECLARE_EVENT_ID(EVENT_ID_StorageM_StorageSizeUpdateDiscovered,     0x0041, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_StorageM_WriteBackLock_NotPossible,       0x0042, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_StorageM_WriteBackUnLock_NotPossible,     0x0043, DL_LOGGING_SEL_LOGEVENT)
            //Events: Parameter Manager
            DECLARE_EVENT_ID(EVENT_ID_ParamM_XmlUpdateStarted,                  0x0051, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_ParamM_XmlUpdateCompleted,                0x0052, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_ParamM_XmlUpdateAborted,                  0x0053, DL_LOGGING_SEL_LOGEVENT)
            //Events: App/Cfg Updates
            DECLARE_EVENT_ID(EVENT_ID_AppVersion_UpdateDiscovered,              0x0061, DL_LOGGING_SEL_APP_VERSION_UPDATE_EVENT)
            DECLARE_EVENT_ID(EVENT_ID_ConfigVersionUpdate,                      0x0062, DL_LOGGING_SEL_CFG_VERSION_UPDATE_EVENT)

            DECLARE_EVENT_ID(EVENT_ID_UnknownErrorIdHealingAttempt,             0x0100, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_ErrorCleared,                             0x0101, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_ErrorClearPermanentRejected,              0x0102, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_ErrorResetAllRequested,                   0x0103, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_ErrorM_Init_Resynced_ErrorAction,         0x0104, DL_LOGGING_SEL_LOGEVENT)

            //ERROR_ID_General_Error 0x1000
            //ERROR_ID_Current_Error_General 0x2000
            //ERROR_ID_Overcurrent_Input_General 0x2100
            //ERROR_ID_Overcurrent_Output_General 0x2300
            //ERROR_ID_Current_Measurement_General 0x2400
            //ERROR_ID_Voltage_Error_General 0x3000
            //ERROR_ID_Device_Internal_Voltage_General 0x3200
            DECLARE_ERROR_ID(ERROR_ID_SystemStateTransitionRequestRejected,     0x3216, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_UnknownErrorIdReported,                   0x3217, ERROR_ACTION_SYSTEM_RESET,        DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Cell_General 0x3400
            //ERROR_ID_Temperature_Error_General 0x4000
            //ERROR_ID_Device_Temperature_General 0x4200
            //ERROR_ID_Temperature_Battery_Module_General 0x4300
            //ERROR_ID_Hardware_Error_General_Batterie 0x5000
            //ERROR_ID_BMS_Components_General 0x5400
            //ERROR_ID_Supply 0x5430
            //ERROR_ID_Frontend_AFE 0x5440
            //ERROR_ID_ADC 0x5460
            //ERROR_ID_Microcontroller 0x5470
            DECLARE_ERROR_ID(ERROR_ID_Stack_Overflow,                           0x5477, ERROR_ACTION_SYSTEM_RESET,        DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Unspecified_SelfTest_Failure,             0x547A, ERROR_ACTION_SYSTEM_RESET,        DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Software_Errors_General 0x6000
            DECLARE_ERROR_ID(ERROR_ID_ASSERT_FAILED,                            0x6001, ERROR_ACTION_SYSTEM_RESET,        DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Software_General_General 0x6100
            DECLARE_ERROR_ID(ERROR_ID_Software_MsgService_QueueOverflow,        0x6111, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Operating_System_General 0x6200
            DECLARE_ERROR_ID(ERROR_ID_Time_Budget_Error,                        0x6212, ERROR_ACTION_SYSTEM_RESET,        DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Memory_Management_Error,                  0x6215, ERROR_ACTION_SYSTEM_RESET,        DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_OS_Safety_Critical_Error,                 0x6216, ERROR_ACTION_SYSTEM_RESET,        DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_OS_Ressource_Error,                       0x6217, ERROR_ACTION_SYSTEM_RESET,        DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Application_Software_General 0x6300
            DECLARE_ERROR_ID(ERROR_ID_SystemStateM_TransitionFailed,            0x6315, ERROR_ACTION_SYSTEM_RESET,        DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_SystemStateM_Invalid_Request_Received,    0x6316, ERROR_ACTION_SYSTEM_RESET,        DL_LOGGING_SEL_ERROREVENT)
            //don't reuse id: DECLARE_ERROR_ID(ERROR_ID_ErrorM_EarlyHealRequestDropped,     0x6317, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)
            //don't reuse id: DECLARE_ERROR_ID(ERROR_ID_ErrorM_EarlyResetAllRequestDropped, 0x6318, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)
            //don't reuse id: DECLARE_ERROR_ID(ERROR_ID_ErrorM_EarlyErrorReportDiscovered,  0x6319, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)

            //ERROR_ID_Data_record_General 0x6400
            DECLARE_ERROR_ID(ERROR_ID_External_Flash_Init_Failure,              0x6410, ERROR_ACTION_SYSTEM_RESET,        DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Storage_Init_Failure,                     0x6411, ERROR_ACTION_SYSTEM_RESET,        DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Parameter_Init_Failure,                   0x6412, ERROR_ACTION_SYSTEM_RESET,        DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Logging_Init_Failure,                     0x6413, ERROR_ACTION_SYSTEM_RESET,        DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_EEPROM_Init_Failure,                      0x6414, ERROR_ACTION_REQUEST_ERROR_STATE, DL_LOGGING_SEL_ERROREVENT)

            DECLARE_ERROR_ID(ERROR_ID_Storage_Duplicate_Id_Collision,           0x6430, ERROR_ACTION_SYSTEM_RESET,        DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_StorageM_ShadowBuffersRevert_NotAllowed,  0x6431, ERROR_ACTION_REQUEST_ERROR_STATE, DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_StorageM_ShadowBuffersRevert_Failure,     0x6432, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_StorageM_Init_Failure,                    0x6433, ERROR_ACTION_REQUEST_ERROR_STATE, DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_StorageM_Init_NvmData_Discarded,          0x6434, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_StorageM_WriteBack_Failure,               0x6435, ERROR_ACTION_REQUEST_ERROR_STATE, DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_StorageM_WriteBack_NotAllowed,            0x6436, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_StorageM_Erase_Failure,                   0x6437, ERROR_ACTION_REQUEST_ERROR_STATE, DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_StorageM_Erase_NotAllowed,                0x6438, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_StorageM_StorageSizeUpdateDiscovered,     0x6439, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_StorageM_StorageCrcMismatch,              0x643A, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)

            DECLARE_ERROR_ID(ERROR_ID_Parameter_StartXmlInput_Failure,          0x6440, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Parameter_StartXmlOutput_Failure,         0x6441, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Parameter_PutXmlChunk_Failure,            0x6442, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Parameter_GettXmlChunk_Failure,           0x6443, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)


            //DECLARE_ERROR_ID(ERROR_ID_Storage_Repair_failed,                    0x6419, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Configuration_General 0x6500
            DECLARE_ERROR_ID(ERROR_ID_Wrong_Configuration,                      0x6511, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_EepromEmulation_General 0x6600
            DECLARE_ERROR_ID(ERROR_ID_EepromEmu_Error,                          0x6601, ERROR_ACTION_NONE,                DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Auxilary_modules_General 0x7000
            //ERROR_ID_DCDC_Bat_General 0x7100
            //ERRORID_DCAC_General 0x7200
            //ERROR_ID_Monitoring_General 0x8000
            //ERROR_ID_Communication_General 0x8100
            //ERROR_ID_Protokoll_Error 0x8200
            DECLARE_ERROR_ID(ERROR_ID_HAL_BXCAN_TxAbortError,                   0x8320, ERROR_ACTION_REQUEST_ERROR_STATE, DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_HAL_BXCAN_Error,                          0x8321, ERROR_ACTION_REQUEST_ERROR_STATE, DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_External_Errors 0x9000
            //ERROR_ID_Device_Specific 0xFF00
            /********************* HVP Section End **********************/


            /********************* User Section Begin **********************/
            //Events: Observer
            DECLARE_EVENT_ID(EVENT_ID_PermanentErrorCleared,                    0x0801, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_ObserverErrorSet,                         0x0802, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_ObserverWarningSet,                       0x0803, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_ObserverErrorCleared,                     0x0804, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_ObserverWarningCleared,                   0x0805, DL_LOGGING_SEL_LOGEVENT)
            //Events: KMS
            //Events: bootloader
            DECLARE_EVENT_ID(EVENT_ID_DiscoveredUnexpectedResetCause,           0x0822, DL_LOGGING_SEL_LOGEVENT)
            //Events: Analog FrontEnd
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_BaseDev_FaultSummary,      0x0831, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_FaultSummary,     0x0832, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_BaseDev_Fault_Reg,         0x0833, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_BaseDev_Fault_Sys,         0x0834, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_BaseDev_Fault_Pwr,         0x0835, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_BaseDev_Fault_Comm1,       0x0836, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_BaseDev_Fault_Comm2,       0x0837, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Comm1,      0x0838, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Comm2,      0x0839, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Comm3,      0x083A, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Otp,        0x083B, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Sys,        0x083C, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Prot1,      0x083D, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Prot2,      0x083E, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Ov1,        0x083F, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Ov2,        0x0840, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Uv1,        0x0841, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Uv2,        0x0842, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Ot,         0x0843, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Ut,         0x0844, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_CompGpio,   0x0845, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_CompVccb1,  0x0846, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_CompVccb2,  0x0847, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_CompVcow1,  0x0848, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_CompVcow2,  0x0849, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_CompVbow1,  0x084A, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_CompVbow2,  0x084B, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_CompCbFet1, 0x084C, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_CompCbFet2, 0x084D, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_CompMisc,   0x084E, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Pwr1,       0x084F, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Pwr2,       0x0850, DL_LOGGING_SEL_LOGEVENT)
            DECLARE_EVENT_ID(EVENT_ID_AnalogFrontEnd_StackDev_Fault_Pwr3,       0x0851, DL_LOGGING_SEL_LOGEVENT)

            DECLARE_EVENT_ID(EVENT_ID_J1939_DiagErrorLog_Event,                 0x0881, DL_LOGGING_SEL_J1939_DIAG_ERROR_EVENT)


            //ERROR_ID_General_Error 0x1000
            //ERROR_ID_Current_Error_General 0x2000
            //ERROR_ID_Overcurrent_Input_General 0x2100
            DECLARE_ERROR_ID(ERROR_ID_CHG_overcurrent_warning,                  0x2111, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_CHG_overcurrent_error,                    0x2112, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_CHG_overcurrent_short_interval_error,     0x2113, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_CHG_overcurrent_long_interval_error,      0x2114, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_CHG_overcurrent_continuous_warning,       0x2115, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Overcurrent_Output_General 0x2300
            DECLARE_ERROR_ID(ERROR_ID_Short_Circuit,                            0x2311, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_DSG_overcurrent_warning,                  0x2312, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_DSG_overcurrent_error,                    0x2313, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_DSG_overcurrent_short_interval_error,     0x2314, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_DSG_overcurrent_long_interval_error,      0x2315, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_DSG_overcurrent_continuous_warning,       0x2316, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Current_Measurement_General 0x2400
            DECLARE_ERROR_ID(ERROR_ID_Current_plausibility_error,               0x2411, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Current_Observer_Timeout,                 0x2412, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Voltage_Error_General 0x3000
            //ERROR_ID_Device_Internal_Voltage_General 0x3200
            DECLARE_ERROR_ID(ERROR_ID_Overvoltage_battery_module_warning,       0x3211, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Undervoltage_battery_module_warning,      0x3212, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            //DECLARE_ERROR_ID(ERROR_ID_Overvoltage_battery_module_error,         0x3213, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            //DECLARE_ERROR_ID(ERROR_ID_Undervoltage_battery_module_error,        0x3214, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Voltage_Observer_Timeout,                 0x3215, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Overvoltage_battery_pack_warning,         0x3220, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Undervoltage_battery_pack_warning,        0x3221, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Cell_General 0x3400
            DECLARE_ERROR_ID(ERROR_ID_Cell_voltage_plausibility_error,          0x3410, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Overvoltage_Cell_warning,                 0x3411, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Undervoltage_Cell_warning,                0x3412, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Overvoltage_Cell_error,                   0x3413, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Undervoltage_Cell_error,                  0x3414, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Deep_Discharge_Cell,                      0x3415, ERROR_ACTION_REQUEST_STAY_IN_SHUTDOWN_STATE,  DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Cell_voltage_difference,                  0x3416, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Cell_defect_overvoltage,                  0x3417, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Chg_Dsg_Violation,                        0x3418, ERROR_ACTION_NONE,					  		  DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Emergency_Discharging_charge_Violation,   0x3419, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Emergency_Charging_Timeout,               0x341A, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Emergency_Discharging_Timeout,            0x341B, ERROR_ACTION_NONE,             		          DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Observer_ChargeDischarge_Violation,       0x341C, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Observer_ChargeDischarge_ImplError,       0x341D, ERROR_ACTION_SYSTEM_RESET,                    DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Deep_Discharge_Protection_Level_1,        0x3421, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Deep_Discharge_Protection_Level_2,        0x3422, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Deep_Discharge_Protection_Level_3,        0x3423, ERROR_ACTION_REQUEST_STAY_IN_SHUTDOWN_STATE,  DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Observer_Reserved_DoNothing,              0x3450, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_LOGEVENT)
            //ERROR_ID_Temperature_Error_General 0x4000
            //ERROR_ID_Device_Temperature_General 0x4200
            DECLARE_ERROR_ID(ERROR_ID_BMS_controller_temperature_high,          0x4210, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_AFE_temperature_high,                     0x4211, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Slave_temperature_high,                   0x4212, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Temperature_Battery_Module_General 0x4300
            DECLARE_ERROR_ID(ERROR_ID_Temperature_difference_too_high,          0x4310, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_DSG_overtemperature_warning,              0x4311, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_DSG_undertemperature_warning,             0x4312, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_CHG_overtemperature_warning,              0x4313, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_CHG_undertemperature_warning,             0x4314, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_DSG_overtemperature_error,                0x4321, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_DSG_undertemperature_error,               0x4322, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_CHG_overtemperature_error,                0x4323, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_CHG_undertemperature_error,               0x4324, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Temperature_Observer_Timeout,             0x4325, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Temperature_Permanent_error,              0x4326, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Temperature_plausibility_error,           0x4327, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Hardware_Error_General_Batterie 0x5000
            //ERROR_ID_BMS_Components_General 0x5400
            //DECLARE_ERROR_ID(ERROR_ID_Relays,                                   0x5410, ERROR_ACTION_REQUEST_ERROR_STATE,  DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_PreCharge_Relay_Defect,                   0x5410, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Positive_Relay_Defect,                    0x5411, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Negative_Relay_Defect,                    0x5412, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Precharge_Timeout,                        0x5413, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Relays_Not_Ready,                         0x5414, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_WaitZeroCurrent_Timeout,                  0x5415, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_PowerPath_DetachUnderLoad,                0x541F, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)

            DECLARE_ERROR_ID(ERROR_ID_PowerPath_ImplementationError,            0x5420, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_PowerPath_DetachInterrupted,              0x5421, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_PowerPath_AttachInterrupted,              0x5422, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_PowerPathManualOverride_InvalidRequest,   0x5423, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_LOGEVENT)
            DECLARE_ERROR_ID(ERROR_ID_PowerPathManualOverride_ExitUnderLoad,    0x5424, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_PowerPath_SafetyDetachIntervalTimeout,    0x5425, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_PowerPath_Kl15_Enable_Error,              0x5426, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)


            DECLARE_ERROR_ID(ERROR_ID_Relay_DigitalFeedBackInvalid,             0x5430, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)

            DECLARE_ERROR_ID(ERROR_ID_Interlock_hvil,                           0x5432, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Interlock_emcystp,                        0x5433, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Isolation_Monitor,                        0x5436, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Fluid_Sensor,                             0x5437, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Humidity_Sensor,                          0x5438, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Humidity_Sensor_warning,                  0x5439, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)

            //ERROR_ID_Supply 0x5430
            //ERROR_ID_Frontend_AFE 0x5440
            DECLARE_ERROR_ID(ERROR_ID_Frontend_Error,                           0x5441, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_CVS,                                      0x5442, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_CVS_INIT_TIMEOUT,                         0x5443, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)

            //ERROR_ID_ADC 0x5460
            DECLARE_ERROR_ID(ERROR_ID_ADC_Unplausible_Measurement,              0x5461, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_ADC_Internal_Error,                       0x5462, ERROR_ACTION_SYSTEM_RESET,                    DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_ADC_Measurement_Start_Error,              0x5465, ERROR_ACTION_SYSTEM_RESET,                    DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_ADC_Init_Error,                           0x5466, ERROR_ACTION_SYSTEM_RESET,                    DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Microcontroller 0x5470
            //ERROR_ID_Software_Errors_General 0x6000
            //ERROR_ID_Software_General_General 0x6100
            DECLARE_ERROR_ID(ERROR_ID_DETECTED_RESET_BY_ERRORHANDLING,          0x6101, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Operating_System_General 0x6200
            //ERROR_ID_Application_Software_General 0x6300
            DECLARE_ERROR_ID(ERROR_ID_OPERATIONALSTATE_TIMEOUT_TR_DETECTED,     0x6308, ERROR_ACTION_NONE, /* don't modify! */        DL_LOGGING_SEL_ERROREVENT)


            DECLARE_ERROR_ID(ERROR_ID_OPERATIONALSTATE_UNKNOWN_SW_REQUEST,      0x630A, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Data_record_General 0x6400
            //ERROR_ID_Configuration_General 0x6500
            DECLARE_ERROR_ID(ERROR_ID_Incompatible_Application_ArticleNumber,   0x6512, ERROR_ACTION_SYSTEM_RESET,                    DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Incompatible_Application_HardwareRevision,0x6513, ERROR_ACTION_SYSTEM_RESET,                    DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_PcbEolTestSW_OtpArticleNumberDiscovered,  0x6514, ERROR_ACTION_SYSTEM_RESET,                    DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_PcbEolTestSW_OtpHardwareRevDiscovered,    0x6515, ERROR_ACTION_SYSTEM_RESET,                    DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_EepromEmulation_General 0x6600
            DECLARE_ERROR_ID(ERROR_ID_KMS_Level_Max,                            0x6700, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_KMS_Level_Not_Approved,                   0x6701, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_CELL_DELTA_DIAGNOSIS 0x6800
            DECLARE_ERROR_ID(ERROR_ID_CELLVOLTAGEDELTAMONITORING_DEFECT,        0x6811, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Auxilary_modules_General 0x7000
            //ERROR_ID_DCDC_Bat_General 0x7100
            DECLARE_ERROR_ID(ERROR_ID_DCDC_Bat_Not_Ready,                       0x7110, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Unplausible_External_System_Voltage,      0x7120, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            //ERRORID_DCAC_General 0x7200
            DECLARE_ERROR_ID(ERROR_ID_DCACEmergencyError_StopBattery,           0x7200, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_DCACEmergencyError_DontCare,              0x7201, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Monitoring_General 0x8000
            DECLARE_ERROR_ID(ERROR_ID_DCDCCTRL_FEEDBACKVOLTAGE_OUT_OF_RANGE,    0x8001, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Communication_General 0x8100
            DECLARE_ERROR_ID(ERROR_ID_CAN_Internal_Error,                       0x8160, ERROR_ACTION_NONE,                            DL_LOGGING_SEL_ERROREVENT)
            //ERROR_ID_Protokoll_Error 0x8200

            //DECLARE_ERROR_ID(ERROR_ID_MW_BASICCAN_INIT_ERROR,                   0x8330, ERROR_ACTION_REQUEST_ERROR_STATE,           DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_MW_BASICCAN_ERROR_IRQ,                    0x8331, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_MW_BASICCAN_TX_ERROR,                     0x8332, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_MW_BASICCAN_IMPL_ERROR,                   0x8333, ERROR_ACTION_SYSTEM_RESET,                    DL_LOGGING_SEL_ERROREVENT)

            DECLARE_ERROR_ID(ERROR_ID_MW_AccelerationSensor_CommError,          0x8350, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_MW_AccelerationSensor_RunTimeError,       0x8351, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_MW_AccelerationSensor_SelftestFailed,     0x8352, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_MW_AccelerationSensor_ShockDetected,      0x8353, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)

            //ERROR_ID_External_Errors 0x9000
            DECLARE_ERROR_ID(ERROR_ID_Power_15V_Not_Good,                       0x9010, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_Relay_Test_Timeout,                       0x9011, ERROR_ACTION_REQUEST_ERROR_STATE,             DL_LOGGING_SEL_ERROREVENT)

            //ERROR_ID_SelfTest_Errors 0xa000
            DECLARE_ERROR_ID(ERROR_ID_SelfTest_Config,                          0xa001, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_SelfTest_TM1,                             0xa010, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)
            //DECLARE_ERROR_ID(ERROR_ID_SelfTest_TM1L,                            0xa010, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_SelfTest_TM2,                             0xa011, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_SelfTest_TM3,                             0xa012, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_SelfTest_TM4,                             0xa013, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_SelfTest_TM5,                             0xa014, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_SelfTest_TM6,                             0xa015, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_SelfTest_TM7,                             0xa016, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_SelfTest_TM8,                             0xa017, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_SelfTest_TM9,                             0xa018, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_SelfTest_TM10,                            0xa019, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_SelfTest_TM11,                            0xa01a, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_SelfTest_Flash_Cyclic,                    0xa01b, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_SelfTest_Ram_Cyclic,                      0xa01c, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)
            DECLARE_ERROR_ID(ERROR_ID_SelfTest_Ram_Startup,                     0xa01d, ERROR_ACTION_SYSTEM_RESET,                            DL_LOGGING_SEL_ERROREVENT)

            //ERROR_ID_Device_Specific 0xFF00

    #ifndef ERRORID_MAGIC_ENABLED
        } usr_errorId_t; /* HVP - required */
        #ifdef __cplusplus
        }
        #endif /* __cplusplus */
        #define USR_ERRORID_INCLUDEGUARD
    #endif
#endif
